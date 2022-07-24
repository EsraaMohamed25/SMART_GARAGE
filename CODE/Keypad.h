 #ifndef F_CPU
 #define F_CPU 8000000UL //MHz Clock frequency
 #endif

 #define Enable_Global_Interrupt (SREG  |= (1<<7))
 #include <avr/io.h>
 #include <avr/interrupt.h>
 #include <util/delay.h>

typedef unsigned char uint8;


#include "std_macros.h"
#define BIT_IS_CLEAR(REG,BIT) ( !(REG & (1<<BIT)) )
#ifndef KEYPAD_H_
#define KEYPAD_H_

#define N_col 3
#define N_row 4
/* Keypad Port Configurations */
#define KEYPAD_PORT_OUT PORTC
#define KEYPAD_PORT_IN  PINC
#define KEYPAD_PORT_DIR DDRC

uint8 KeyPad_getPressedKey(void);

#endif /* KEYPAD_H_ */