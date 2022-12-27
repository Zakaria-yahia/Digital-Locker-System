/*
 * KEYPAD.c
 *
 * Created: 13/08/2022 09:37:22 
 * Author : Zakaria
 */
#include "KEYPAD.h"
const uint8_t keypad_matrix[] = 
{'7', '8', '9', '\\',
 '4', '5', '6', '*',
 '1', '2', '3', '-',
 'c', '0', '=', '+'
};
// PD0 to PD3 input pull up, PD4 to PD7 output
void KEYPAD_init(void){
	INIT_KEYPAD_PIN;
  
}
uint8_t KEYPAD_read(void){
	K_OUTPUTS=0xff;
	for (uint8_t i=0;i<=3;i++)
	{
		CLRBIT(K_OUTPUTS,K4+i);
		if(K0 == 0) return keypad_matrix[0+i];
		if(K1 == 0) return keypad_matrix[4+i];
		if(K2 == 0) return keypad_matrix[8+i];
		if(K3 == 0) return keypad_matrix[12+i];
		_delay_ms(1);
		SETBIT(K_OUTPUTS,K4+i);
	}
	
	
	
	
	
	return 0;
}