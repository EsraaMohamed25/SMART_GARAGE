#include "keypad.h"
#if (N_col == 3)

static uint8 KeyPad_4x3_adjustKeyNumber(uint8 button_number);
#endif

uint8 KeyPad_getPressedKey(void)
{
	uint8 col,row;
	while(1)
	{
		for(col=0;col<N_col;col++) /* loop for columns */
		{
			/* each time only one of the column pins will be output and 
			 the rest will be input pins include the row pins */ 
			KEYPAD_PORT_DIR = (0b0010000<<col); 
			
			/* clear the output pin column in this trace and enable the internal 
			 pull up resistors for the rows pins*/ 
			KEYPAD_PORT_OUT = (~(0b0010000<<col));
            checksensor();
			for(row=0;row<N_row;row++) /* loop for rows */
			{
				if(BIT_IS_CLEAR(KEYPAD_PORT_IN,row)) /* if the switch is press in this row */ 
				{
					#if (N_col == 3)
						return KeyPad_4x3_adjustKeyNumber((row*N_col)+col+1);
					#endif
				}
			}
		}
	}	
}

#if (N_col == 3) 

static uint8 KeyPad_4x3_adjustKeyNumber(uint8 button_number)
{
	switch(button_number)
	{
		case 10: return '*'; // ASCII Code of *
				 break;
		case 11: return 0;
				 break;		
		case 12: return '#'; // ASCII Code of #
				 break;
		default: return button_number;								 						
	}
} 


#endif