#include "PeriodicEvent.h"

/* Constant PIN defines */
#define PIN_STATUS_LED          ( 13 )

/* Constant periodic event delays */
#define STATUS_DELAY_MS         ( 250 )

/* Function definitions */
void Flash_LED( void * userdata );

/* Variables */
static PeriodicEvent        Flash_Status_LED( { 0, 0, 0, STATUS_DELAY_MS }, Flash_LED, (void*)PIN_STATUS_LED );

/* Functions */
void setup()
    {
    /* Initialize periodic events */
    Flash_Status_LED.Enable();
    } /* setup() */

void loop()
    {
	/* Check periodic events */
    Flash_Status_LED.Check();
	
	/* Do something else here */
    } /* loop() */

void Flash_LED( void * userdata )
    {
    static bool Initialized = false;
    static bool State = HIGH;

    if( !Initialized )
        {
        Initialized = true;
        pinMode( (int)userdata, OUTPUT );
        }

    State = !State;
    digitalWrite( (int)userdata, State );
    } /* Flash_LED() */