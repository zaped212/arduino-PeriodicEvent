/*
* Periodic Event Class
* Nathan Reichenberger
*
* Allows the main program to perform periodic events
*  without blocking 
*
*/

#ifndef __PERIODIC_EVENT_H__
#define  __PERIODIC_EVENT_H__

#include <Arduino.h>
#include "stdint.h"

typedef struct
    {
    uint16_t    timeval_hour;
    uint16_t    timeval_min;
    uint16_t    timeval_sec;
    uint16_t    timeval_ms;
    } periodic_timeval;

class PeriodicEvent
{
  public:
    //constructors
    PeriodicEvent( periodic_timeval Delay, void( *Funct )( void * data ), void* UserData );

    //destructor
    ~PeriodicEvent();

    //functions
    bool Check();
	void Enable();
	void Disable();
    void UpdateDelay( periodic_timeval Delay );
    void Kick();

    unsigned long    Get_Delay_ms();

  private:
	bool		enabled;
    
    unsigned long	temp_Time;
    unsigned long	start_Time;
    unsigned long	delay_Time;

    void(*user_CB )( void * data );
    void *          user_Data;
};
#endif