/*
 * KEYPAD.h
  *
  * Created: 13/08/2022 09:37:22
  * Author : Zakaria
  */


#ifndef KEYPAD_H_
#define KEYPAD_H_
#include "std_macros.h"

#define INIT_KEYPAD_PIN 	                   \
							DDRD = 0b11110000; \
							PORTD = 0b1111;
#define K0 READBIT(PIND,0)
#define K1 READBIT(PIND,1)
#define K2 READBIT(PIND,2)
#define K3 READBIT(PIND,3)
#define K4 4
#define K5 5
#define K6 6
#define K7 7
#define K_OUTPUTS  PORTD

void KEYPAD_init(void);
uint8_t KEYPAD_read(void);



#endif /* KEYPAD_H_ */