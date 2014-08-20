/*
 * i2c_basic.c
 *
 * Created: 7/14/2014 5:04:45 PM
 *  Author: mini me
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "USI_TWI_Master.h"
#include <util/delay.h>

#define SLAVE_ADDR 0x04

#define MESSAGEBUF_SIZE       4
#define TWI_CMD_MASTER_WRITE 0x10
#define TWI_CMD_MASTER_READ  0x20

#define TWI_GEN_CALL         0x00

int main(void)
{
	cli();
    volatile unsigned char messageBuf[MESSAGEBUF_SIZE];
	volatile unsigned char temp = 0, myCounter = 43;
	
	
	USI_TWI_Master_Initialise();
	sei();
	
	for(;;)
    {


		messageBuf[0] = (SLAVE_ADDR<<TWI_ADR_BITS) | (FALSE<<TWI_READ_BIT);
		messageBuf[1] = myCounter;
		if(temp == 0) {
		
			temp = USI_TWI_Start_Transceiver_With_Data( messageBuf, 3);
		}
		
		else {
			messageBuf[2] = 255;
			temp = USI_TWI_Start_Transceiver_With_Data( messageBuf, 3);
		}
		myCounter++;
		if(myCounter >= 100) {myCounter = 1;}
		_delay_ms( 50 );
		//TODO:: Please write your application code 
    }
	
	return 0;
}
