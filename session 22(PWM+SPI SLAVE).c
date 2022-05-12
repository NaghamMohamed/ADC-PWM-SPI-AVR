/*
 * session_22_PWM_SPI_SLAVE_.c
 *
 * Created: 27-Jan-21 8:54:15 PM
 *  Author: DELL
 */ 


#include <avr/io.h>
void SPI_slave_init (void)
{
	DDRB=(1<<6);           //MISO as OUTPUT
	SPCR=(1<<6);          //Enable SPI
}

unsigned char spi_tranceiver (unsigned char data)
{
	SPDR = data;//Load data into the buffer
	while((SPSR & (1<<7))==0); //Wait until transmission complete
	return(SPDR); //Return received data
}
int main(void)
{   TCCR0|=(1<<3);//pwm mode
	TCCR0|=(1<<6);//pwm mode
	TCCR0|=(1<<0);//no prescaler
	TCCR0|=(3<<4);//non-inv
	DDRB|=(1<<3);//output
	DDRC=0xff;
	SPI_slave_init();
    while(1)
    {   int rx= spi_tranceiver(0x33);
		 OCR0=rx;
		 PORTC=rx;
		 
        //TODO:: Please write your application code 
    }
}