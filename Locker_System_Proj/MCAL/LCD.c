/*
 * CFile1.c
 *
 * Created: 12/08/2022 04:10:43 م
 *  Author: Zakaria
 */ 
 #include "LCD.h"
 
 void (*timer0_ovf_isr)(void);
 void (*timer0_ctc_isr)(void);
 /*****************************************************************************
 * Function Name: LCD_init
 * Purpose      : Init lcd in 4 bit mode, clear lcd and turn off cursor
 * Parameters   : void
 * Return value : void
 *****************************************************************************/

 void LCD_int(void)
 {
	 INIT_LCD_PIN;
	 LCD_write_command(0x3);
	 _delay_ms(4);
	 LCD_write_command(0x3);
	 _delay_ms(4);
	 LCD_write_command(0x3);
	 _delay_ms(4);
	 
	 LCD_write_command(0x2);
	 LCD_write_command(0x28);
	 LCD_write_command(0x08);
	 LCD_write_command(0x1);
	 LCD_write_command(0x6);
	 LCD_write_command(0xc);
	 _delay_ms(20);
 }
 
 
 
 /*****************************************************************************
 * Function Name: LCD_write_command
 * Purpose      : write command to lcd
 * Parameters   : data: one of LCD commands
 * Return value : void
 *****************************************************************************/
 void LCD_write_command(uint8_t data)
 {
	 RS(0);
	 D7(READBIT(data,7)); // Data bit7  = D7
	 D6(READBIT(data,6)); // Data bit6  = D6
	 D5(READBIT(data,5)); // Data bit5  = D5
	 D4(READBIT(data,4)); // Data bit4  = D4
	 EN(1);
	 _delay_ms(1);
	 EN(0);
	 _delay_ms(1);
	 
	 D7(READBIT(data,3)); // Data bit3  = D7
	 D6(READBIT(data,2)); // Data bit2  = D6
	 D5(READBIT(data,1)); // Data bit1  = D5
	 D4(READBIT(data,0)); // Data bit0  = D4
	 EN(1);
	 _delay_ms(1);
	 EN(0);
	 _delay_ms(1);
	 
 }
 /*****************************************************************************
 * Function Name: LCD_write_data
 * Purpose      : write symbol on lcd
 * Parameters   : data: Ascii value of specific symbol
 * Return value : void
 *****************************************************************************/
 void LCD_write_data(uint8_t data){ // 0x53
	 RS(1);
	 D7(READBIT(data,7)); // Data bit7  = D7
	 D6(READBIT(data,6)); // Data bit6  = D6
	 D5(READBIT(data,5)); // Data bit5  = D5
	 D4(READBIT(data,4)); // Data bit4  = D4
	 EN(1);
	 _delay_ms(1);
	 EN(0);
	 _delay_ms(1);

	 D7(READBIT(data,3)); // Data bit3  = D7
	 D6(READBIT(data,2)); // Data bit2  = D6
	 D5(READBIT(data,1)); // Data bit1  = D5
	 D4(READBIT(data,0)); // Data bit0  = D4
	 EN(1);
	 _delay_ms(1);
	 EN(0);
	 _delay_ms(1);
 }
 
 /*****************************************************************************
 * Function Name: LCD_write_data
 * Purpose      : write a string on lCD
 * Parameters   : *data: array of char
 * Return value : void
 *****************************************************************************/
 void LCD_write_string(char *data)
 {
	 uint8_t i =0;
	 while(data[i] != '\0'){
		 LCD_write_data(data[i]);
		 i++;
	 }
 }
 
  /*****************************************************************************
 * Function Name: LCD_write_data
 * Purpose      : write a number on lCD
 * Parameters   : *data: array of char
 * Return value : void
 *****************************************************************************/
 void LCD_write_number(uint32_t data)
 {
	 uint8_t i=0;
	 uint8_t num_array[10];
	 if(data==0){
		 LCD_write_data('0');
		 return;	
	 }
	 
	 for(i=0; data !=0 ; i++){
		 num_array[i]= (data % 10) + 48;
		 data/=10;
	 }
	 
	 while(i > 0){
		 LCD_write_data(num_array[i-1]);
		 
		 i--;
	 }
		
	 
 }