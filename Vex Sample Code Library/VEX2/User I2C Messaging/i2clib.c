/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        Module:     i2clib.c                                               */
/*        Author:     James Pearman                                          */
/*        Created:    19 Oct 2015                                            */
/*                                                                           */
/*        Revisions:  V0.1                                                   */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        Description:                                                       */
/*        Wrapper for the low level cortex i2c messaging calls               */
/*---------------------------------------------------------------------------*/
/*                                                                           */

#pragma systemfile

// Replacements for the I2C intrinsics
#if defined(VEX2)

// Simplified status for higher layer code
typedef enum _i2cStatus {
    kMessageTooLong = 0,
    kMessageSuccess,
    kMessageSending,
    kMessageError
} i2cStatus;

// If many IMEs are installed this may beed to be increased
#define DEFAULT_I2C_TIMEOUT   10        /// Default timeout

#define MAX_I2C_MESSAGE       32        /// Do not change !

/*---------------------------------------------------------------------------*/
/** @brief  Send an I2C user message                                         */
/** @param[in] address  Device I2C address                                   */
/** @param[in] buf  Transmit data - 32 bytes maximum                         */
/** @param[in] buflen  Transmit buffer length                                */
/** @param[in] replylen  Bytes to read following the transmit message        */
/** @returns   Status                                                        */
/*---------------------------------------------------------------------------*/
i2cStatus
i2cWriteData( char address, char *buf, int buflen, int replylen = 0 )
{
    static  bool init = true;
    i2cStatus   status = kMessageSuccess;
    char    txbuf[34];

    // 32 bytes max buffer is determined by the firmware
    if( buflen > MAX_I2C_MESSAGE )
        return( kMessageTooLong );

    // We need to send one message to disable IME polling
    // Or enable termination
    if( init ) {
        // Dummy message
        txbuf[0] = 1;
        txbuf[1] = 0;
        txbuf[2] = 0;
        sendI2CMsg( txbuf, 0 );

        // We must wait for the I2C state machine to timeout
        // or the disable termination message to be sent to an IME
        wait1Msec(100);
        init = false;
    }

    // Loop waiting for last message to be sent
    int timeout = DEFAULT_I2C_TIMEOUT;
    while( nI2CStatus != i2cStatusDone && timeout > 0) {
        timeout--;
        wait1Msec(1);
    }

    // We waited too long for the message to be sent
    if(timeout == 0) {
        // Check and see if we are stuck on Start Bit or Address send
        if( nI2CStatus == i2cStatusStart || nI2CStatus == i2cStatusAddress )
            status = kMessageError;
        else
            status = kMessageSending;
    }

    // Setup message, first byte is data length, second is address
    txbuf[0] = buflen;
    txbuf[1] = address;

    // Copy transmit data
    for(int i=0;i<buflen;i++)
        txbuf[i+2] = buf[i];

    // Transmit
    sendI2CMsg( txbuf, replylen );

    // look at status, sort of meaningless
    // The message will either be sent or block waiting for ACK
    // There is no timeout on the low level code we can use
    if( nI2CStatus == i2cStatusStart )
        status = kMessageError;

    return( status );
}

/*---------------------------------------------------------------------------*/
/** @brief  Read data from an I2C device                                     */
/** @param[in] address  Device I2C address                                   */
/** @param[in] buf  Transmit data - 32 bytes maximum                         */
/** @param[in] buflen  Transmit buffer length                                */
/** @param[in] rxbuf Received data - 32 bytes maximum                        */
/** @param[in] replylen  Number of bytes to read                             */
/** @returns   Status                                                        */
/*---------------------------------------------------------------------------*/
i2cStatus
i2cReadData( char address, char *buf, int buflen, char *rxbuf, int replylen )
{
    if( buflen > MAX_I2C_MESSAGE )
        return( kMessageTooLong );

    // Send message (if necessary)
    int     timeout = DEFAULT_I2C_TIMEOUT;
    if( i2cWriteData( address, buf, buflen, replylen ) == kMessageSuccess ) {
        // Now wait for reply data
        // If the sensor is disconnected this will block for several mS
        while( nI2CBytesReady < replylen && timeout != 0 ) {
            timeout--;
            wait1Msec(1);
        }

        // Reply arrived ?
        if(timeout > 0)
            readI2CReply( rxbuf, replylen );
    }

    // Return status
    if( timeout > 0 && nI2CStatus == i2cStatusDone )
        return( kMessageSuccess );
    else
        return( kMessageError );
}
#else
#error "This Library needs the VEX cortex"
#endif
