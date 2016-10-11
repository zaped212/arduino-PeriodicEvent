/*
* Periodic Event Class
* Nathan Reichenberger
*
* Allows the main program to perform periodic events
*  without blocking 
*
*/
#include "PeriodicEvent.h"

#include <Arduino.h>
#include "stdint.h"

#define HOUR_TO_MS( hour )  ( MIN_TO_MS( hour * 60 ) )
#define MIN_TO_MS( min )    ( SEC_TO_MS( min * 60 ) )
#define SEC_TO_MS( sec )    ( sec * 1000 )

PeriodicEvent::PeriodicEvent( periodic_timeval Delay, void( *UserFunct )( void * data ), void* UserData )
{
  this->start_Time = 0;
  this->temp_Time = 0;
  this->UpdateDelay( Delay );
  
  this->user_CB = UserFunct;
  this->user_Data = UserData;

  this->enabled = false;
}

PeriodicEvent::~PeriodicEvent()
{
}

///-------------------------------------------------------------------------------------------------
/// <summary>   Updates the delay described by Delay. </summary>
///
/// <remarks>   Nathan, 2/8/2014. </remarks>
///
/// <param name="Delay">    The delay. </param>
///-------------------------------------------------------------------------------------------------

void PeriodicEvent::UpdateDelay( periodic_timeval Delay )
{
    this->delay_Time = HOUR_TO_MS( Delay.timeval_hour ) +
                       MIN_TO_MS( Delay.timeval_min ) +
                       SEC_TO_MS( Delay.timeval_sec ) +
                       Delay.timeval_ms;
}

// Called in main loop
// or called by periodic interrupt
bool PeriodicEvent::Check()
{
    bool ret = false;
    unsigned long diff_time;

    // verify this periodic event is enabled
    if( !this->enabled )
        {
        return false;
        }

    this->temp_Time = millis();
    diff_time = ( this->temp_Time - this->start_Time );

    if( diff_time >= this->delay_Time )
        {
        // Check to see if there is a function to call
        if( this->user_CB )
        {
            // call the periodic event
            this->user_CB( this->user_Data );
        }
    
        // reset start time
        this->start_Time = this->temp_Time;
        ret = true;
        }

    return ret;
}

void PeriodicEvent::Enable()
{
    this->enabled = true;
    this->start_Time = millis();
}

void PeriodicEvent::Disable()
{
    this->enabled = false;
    this->start_Time = 0;
}

unsigned long PeriodicEvent::Get_Delay_ms()
{
    return this->delay_Time;
}

void PeriodicEvent::Kick()
{
    this->start_Time = millis();
}