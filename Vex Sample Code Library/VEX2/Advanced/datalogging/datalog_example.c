/*---------------------------------------------------------------------------*/
/*        Module:     Datalog_example.c                                      */
/*        Author:     James Pearman                                          */
/*        Created:    12 Nov 2015                                            */
/*        Platform:   Cortex, Vex-IQ, EV3, NXT                               */
/*        RC Version: 4.51                                                   */
/*                                                                           */
/*        Revisions:                                                         */
/*                    1.00  12 Nov 2015 - Initial release                    */
/*                    1.01  22 Jan 2016 - Revised for datalog graph display  */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/*        Description:                                                       */
/*                                                                           */
/*        This sample code demonstrates the use of dataloging commands       */
/*---------------------------------------------------------------------------*/
/*                                                                           */

#if defined(VexIQ) || defined(EV3) || defined(NXT) || defined(VEX2)

// Global variables used by the sample code
int   global_1 = 0;
int   global_2 = 0;
int   global_3 = 0;

// We have 8 possible places to store data, we call each one a datalog series
// This example uses the first four to store values.
#define   DATALOG_SERIES_0    0
#define   DATALOG_SERIES_1    1
#define   DATALOG_SERIES_2    2
#define   DATALOG_SERIES_3    3

/*---------------------------------------------------------------------------*/
task main()
{
    int loops = 0;

    // Clear old data
    datalogClear();

    while(1)
        {
        // datalogAddValue adds one row to the datalog but does not time stamp the value
        datalogAddValue( DATALOG_SERIES_0, loops );

        // Generate some intertesting data
        global_1 = sinDegrees( loops   ) * 500.0;
        global_2 = cosDegrees( loops*2 ) * 500.0;
        global_3 = 500 + (rand() % 50);

        // datalogAddValue when surrounded by datalogDataGroupStart and datalogDataGroupEnd
        // adds several values to one row of the datalog with a common time stamp
        datalogDataGroupStart();
        datalogAddValue( DATALOG_SERIES_1, global_1 );
        datalogAddValue( DATALOG_SERIES_2, global_2 );
        datalogAddValue( DATALOG_SERIES_3, global_3 );
        datalogDataGroupEnd();

        // datalogAddValueWithTimeStamp adds one row that is time stamped
        // the following statement is equivalent to the code
        //
        // datalogDataGroupStart();
        // datalogAddValue( DATALOG_SERIES_3, global_3 );
        // datalogDataGroupEnd();
        //
        datalogAddValueWithTimeStamp( DATALOG_SERIES_3, global_3 );



        // More examples of datalogAddValueWithTimeStamp
        // The small delay is just for demonstration purposes
        wait1Msec(10);
        datalogAddValueWithTimeStamp( DATALOG_SERIES_3, global_3++ );
        wait1Msec(10);
        datalogAddValueWithTimeStamp( DATALOG_SERIES_3, global_3++ );

        // Repeat sequence every 360 loops
        if(loops++ == 360)
          loops = 0;

        // loop delay
        wait1Msec(10);
        }
}

/*---------------------------------------------------------------------------*/
#else
#warning "Invalid platform selected for this sample program"
#endif
