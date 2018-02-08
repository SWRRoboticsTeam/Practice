/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        Module:     Port expander demo.c                                   */
/*        Author:     James Pearman                                          */
/*        Created:    21 Oct 2015                                            */
/*                                                                           */
/*        Revisions:  V0.1                                                   */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        Description:                                                       */
/*        Demonstration code for communicating with a MAX7311 port expander. */
/*                                                                           */
/*        4 Leds and 12 switches are connected to the port expander as       */
/*        follows.                                                           */
/*                                                                           */
/*             MAX7311                                                       */
/*            +-----------------+                                            */
/*            |              SDA|<-- From cortex                             */
/*            |              SCL|<-- From cortex                             */
/*            |                 |                                            */
/*            |                 |                                            */
/*  Switch -->|IO0           IO8|<-- Switch                                  */
/*  Switch -->|IO1           IO9|<-- Switch                                  */
/*  Switch -->|IO2          IO10|<-- Switch                                  */
/*  Switch -->|IO3          IO11|<-- Switch                                  */
/*     LED <--|IO4          IO12|<-- Switch                                  */
/*     LED <--|IO5          IO13|<-- Switch                                  */
/*     LED <--|IO6          IO14|<-- Switch                                  */
/*     LED <--|IO7          IO15|<-- Switch                                  */
/*            |                 |                                            */
/*            +-----------------+                                            */
/*                                                                           */
/*---------------------------------------------------------------------------*/
/*                                                                           */

// Port expander datasheet here
// https://www.maximintegrated.com/en/products/interface/controllers-expanders/MAX7311.html

// Include the I2C messaging utility functions
#include "i2clib.c"

// The I2C address of the port expander used in the demo
#define PORT_EXP_ADDR   0x4C

/*---------------------------------------------------------------------------*/
/* Configure the port expander                                               */
/*---------------------------------------------------------------------------*/
void
PortExpanderSetup()
{
    // 4 bit output, 12 bit input
    char buf[] = { 0x06, 0x0F, 0xFF };
    i2cWriteData( PORT_EXP_ADDR, buf, 3 );
}

/*---------------------------------------------------------------------------*/
/*  Set leds on the port expander                                            */
/*  We have 4 leds connected to IO bits 7-4                                  */
/*---------------------------------------------------------------------------*/
bool
PortExpanderLedSet( char data )
{
    // two bytes sent to port expander starting at register 2
    char buf[] = { 0x02, 0xFF, 0xFF };

    buf[1] = ~data;

    if( i2cWriteData( PORT_EXP_ADDR, buf, 3 ) != kMessageSuccess )
        return( false );

    return( true );
}

/*---------------------------------------------------------------------------*/
/*  Read Switches on port expander                                           */
/*---------------------------------------------------------------------------*/
unsigned short
PortExpanderSwitchGet( char *rxbuf )
{
    unsigned short switches;

    // Read two bytes starting at address 0
    char txbuf[] = { 0x00 };
    if( i2cReadData( PORT_EXP_ADDR, txbuf, 1, rxbuf, 2 ) == kMessageSuccess )
      switches = rxbuf[1] << 8 | rxbuf[0];

    return(switches);
}

/*---------------------------------------------------------------------------*/
/*  Demo code                                                                */
/*---------------------------------------------------------------------------*/
task main()
{
    char led_data = 0x10;
    char rxdata[16];
    char str[32];
    unsigned short switches;

    bLCDBacklight = true;
    clearLCDLine(0);
    clearLCDLine(1);

    // Setup port expander
    PortExpanderSetup();

    while(1)
        {
        // Set port expander leds
        PortExpanderLedSet( led_data );
        // Run a pretty pattern on the leds
        led_data <<= 1;
        if(!led_data)
            led_data = 0x10;

        // Poll switches
        switches = PortExpanderSwitchGet( rxdata );

        // Display switch data on LCD
        sprintf(str, "%04X", switches );
        displayLCDString(0, 0, str);

        // Don't overload the i2c messaging
        wait1Msec(50);
        }
}
