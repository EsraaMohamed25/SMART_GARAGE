#define DIO_H_
#define REGISTER_SIZE 8
#define SET_BIT(reg,bit)    reg|=(1<<bit)
#define CLR_BIT(reg,bit)    reg&=(~(1<<bit))
#define TOG_BIT(reg,bit)    reg^=(1<<bit)
#define READ_BIT(reg,bit)    (reg&(1<<bit))>>bit
#define IS_BIT_SET(reg,bit)  (reg&(1<<bit))>>bit
#define IS_BIT_CLR(reg,bit)  !((reg&(1<<bit))>>bit)
#define ROR(reg,num)         reg=(reg<<(REGISTER_SIZE-num))|(reg>>(num))
#define ROL(reg,num)        reg= (reg>>(REGISTER_SIZE-num))|(reg<<(num))
#include "DIO.c"
#include "timer.c"
#include "LCD.c"
#include "keypad.c"
#include "EEPROM_driver.c"
#include "sensors.c"
#define  EEPROM_STATUS_LOCATION 0x20
#define  EEPROM_PASSWORD_LOCATION1 0x21
#define  EEPROM_PASSWORD_LOCATION2 0x22
#define  EEPROM_PASSWORD_LOCATION3 0x23
#define  EEPROM_PASSWORD_LOCATION4 0x24
#define MAX_TRIES 3
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
typedef unsigned char uint8;
char arr[4];
uint8 safemode =1;
char flag=0;
int main(void)
{	
	
	uint8 i=0;
	char tries=MAX_TRIES;
	LCD_vInit();
	if (EEPROM_read(EEPROM_STATUS_LOCATION)==0xFF)
	{
		LCD_vSend_string("set pass:");
			
		for (i=0;i<=3;i++)
		{
			arr[i] = KeyPad_getPressedKey();
			LCD_vSend_char(arr[i]);
			_delay_ms(300);
			LCD_movecursor(1,10+i);
			LCD_vSend_char('*');
			_delay_ms(300);
			EEPROM_write(EEPROM_PASSWORD_LOCATION1+i,arr[i]);
		}
		EEPROM_write(EEPROM_STATUS_LOCATION,0x00);
	}
	while(safemode==1)
	{
	while(flag==0)
	{

		arr[0]=arr[1]=arr[2]=arr[3]=0;
		LCD_clearscreen();
		LCD_vSend_string("check pass:");
		for (i=0;i<=3;i++)
		{
			arr[i]= KeyPad_getPressedKey();
			LCD_vSend_char(arr[i]);
			_delay_ms(300);
			LCD_movecursor(1,12+i);
			LCD_vSend_char('*');
			_delay_ms(300);
		}

		if(EEPROM_read(EEPROM_PASSWORD_LOCATION1)==arr[0] &&  EEPROM_read(EEPROM_PASSWORD_LOCATION2)==arr[1] && EEPROM_read(EEPROM_PASSWORD_LOCATION3)==arr[2] && EEPROM_read(EEPROM_PASSWORD_LOCATION4)==arr[3])
		{
			
			LCD_clearscreen();
			LCD_vSend_string("right password");
			LCD_movecursor(2,1);
			LCD_vSend_string("garage opened");
			timer1_wave_fastPWM_A(1);
			DIO_write('D',7,1);
			_delay_ms(5000);
			while(DIO_u8read('D',0)==1){continue;}
			timer1_wave_fastPWM_A(1.5);
			DIO_write('D',7,0);
		
			flag=0;
		}
		else
		{
			tries=tries-1;
			if (tries>0)
			{
				LCD_clearscreen();
				LCD_vSend_string("wrong password");
				_delay_ms(1000);
				LCD_clearscreen();
				LCD_vSend_string("tries left:");
				LCD_vSend_char(tries+48);
				_delay_ms(1000);

			}
			else
			{
				LCD_clearscreen();
				LCD_vSend_string("wrong password");
				LCD_movecursor(2,1);
				LCD_vSend_string("garage locked");
				DIO_write('D',6,1);
				DIO_write('D',2,1);
				flag=1;
				safemode=0;
			}
		}
	}
while(safemode==0)
{
	if(DIO_u8read('B',3)==1)
	{
		LCD_clearscreen();
		DIO_write('D',2,0);
		DIO_write('D',6,0);
		safemode = 1;
		flag=0;
		tries=MAX_TRIES;
	}
	else
	continue;
}
	}
	
	return 0;
}
