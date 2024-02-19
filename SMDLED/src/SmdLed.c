#include "SmdLed.h"

void SmdLed_Init(void)
{
    static unsigned char i=0;
    POWER_LED       = HIGH; ACK_LED         = HIGH; COMM_LED        = HIGH; FAULT_LED	    = HIGH;
    VOLT_MON_CH1    = HIGH; VOLT_MON_CH2    = HIGH; VOLT_MON_CH3    = HIGH; VOLT_MON_CH4    = HIGH;
    CURR_MON_CH1    = HIGH; CURR_MON_CH2    = HIGH; CURR_MON_CH3    = HIGH; CURR_MON_CH4    = HIGH;
    for(i=0; i<=6; i++)
    {
        POWER_LED       ^= HIGH; ACK_LED         ^= HIGH; COMM_LED        ^= HIGH; FAULT_LED	 ^= HIGH;
	VOLT_MON_CH1    = LOW; 
	CURR_MON_CH4    = LOW;
	if(i == 2)
	{
		CURR_MON_CH3    = LOW;
		VOLT_MON_CH3    = LOW; 
	}
	if(i == 4)
	{
		CURR_MON_CH2    = LOW;
		VOLT_MON_CH2    = LOW; 
	}
	if(i == 6)
	{
		CURR_MON_CH1    = LOW;
		VOLT_MON_CH4    = LOW;
	}
	Delay_Ms(500);
	WatchDog_Restart();
    }
    __nop();
}
