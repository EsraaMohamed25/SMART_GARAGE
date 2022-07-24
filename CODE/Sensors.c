void checksensor(void)
{
	

//PIR sensor
if(DIO_u8read('D',0)==1)
{

	timer1_wave_fastPWM_A(1);
	DIO_write('D',7,1);
   _delay_ms(5000);
}
else
{
	timer1_wave_fastPWM_A(1.5);
	DIO_write('D',7,0);
	
}
//flame sensor
if(DIO_u8read('D',1)==1)
{
	DIO_write('D',6,1);
	DIO_write('D',2,1);
	
	
}
else
{
	DIO_write('D',2,0);
	DIO_write('D',6,0);
}
if(DIO_u8read('C',0)==0 &&DIO_u8read('C',1)==0 &&DIO_u8read('C',2)==0 &&DIO_u8read('C',3)==0 &&DIO_u8read('C',4)==0 &&DIO_u8read('C',5)==0 &&DIO_u8read('C',6)==0)
{

	DIO_write('D',6,1);
	DIO_write('D',2,1);
}

}