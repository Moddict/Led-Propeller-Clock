/*
* propeller_clock.c
*
* Created: 8/1/2017 6:48:46 PM
*  Author: DELL
*/


#include <avr/io.h>
#include <electus_at16.h>
void ds3231_write(int reg,int data);
int ds3231_read(int reg);
int main(void)
{
	lcd_init();
	i2c_init();
	
	//ds3231_write(0x0e,0);  // oscillator enable
	//ds3231_write(0x00,0); // register /data/ sec
	//ds3231_write(0x01,0x45); // register /data/min
	//ds3231_write(0x02,0b00001000);//register /data/hour
	lcd_clrscr();
	lcd_write_string("<<< TIME>>>");
	delay(100);
	while(1)
	{
		lcd_clrscr();
		lcd_write_int(ds3231_read(2));
		lcd_write_string(":");
		lcd_write_int(ds3231_read(1));
		
		lcd_write_string(":");
		lcd_write_int(ds3231_read(0));
		lcd_write_string(":");
		delay(1000);
		
	}
}
void ds3231_write(int reg,int data)
{
	i2c_start();/* start the ds3231*/
	i2c_write(0b11010000); /* address of ds3231*/
	i2c_write(reg); /* register value has been passed*/
	i2c_write(data);/* data has been passed*/
	i2c_stop(); /*stop ds3231*/
}
int ds3231_read(int reg)
{
	i2c_start();
	i2c_write(0b11010000); /* to enable (EOSC)*/
	i2c_write(reg); /*register value passed*/
	i2c_start(); 
	i2c_write(0b11010001);/*to read*/
	int r=i2c_read(1); 
	i2c_stop();
	if (reg == 2)
	{
		r = r & 0b00011111;
	}
	r=((r>>4)*10+(r&0b00001111));
	return r;
}
