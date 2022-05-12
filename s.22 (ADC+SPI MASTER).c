/*
 * session22__ADC_Master_.c
 *
 * Created: 27-Jan-21 8:16:55 PM
 *  Author: DELL
 */ 


#include <avr/io.h>
void SPI_INT(void);
unsigned char SPI_TRANCIEVER(char data);
int main(void)
{   ADCSRA |=(1<<7); //ADC enable
	ADMUX|=(1<<6); //vcc ref
	ADMUX|=(1<<5); //shifted left
	ADMUX|=(1<<0); //single ended input A1
	ADCSRA |=(3<<0); //8 prescaling
	DDRA&=~(1<<0);//A0 input
	DDRC=0xff;
	SPI_INT();
    while(1)
    {   
		ADCSRA|=(1<<6);//start conv.
	    while ((ADCSRA&(1<<4))==0);
	    int rx=SPI_TRANCIEVER(ADCH);
		PORTC=rx;
        //TODO:: Please write your application code 
    }
}
void SPI_INT(void)
{
	DDRB|=(1<<4);//ss output
	DDRB|=(1<<5);//MOSI output
	DDRB|=(1<<7);//clk outpot
	
	SPCR|=(1<<7);//INT EN
	SPCR|=(1<<5);//LSB
	SPCR|=(1<<4);//MASTER
	SPCR|=(1<<6);//spi EN
	SPCR|=(1<<0);//Prescaler:Fosc/16	
	
	
}
unsigned char SPI_TRANCIEVER(char data)
{
	
	SPDR=data;
	while ((SPSR& (1<<7))==0);
	return (SPDR);
	
}