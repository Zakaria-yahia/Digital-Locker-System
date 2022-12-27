/*
 * Locker_System_Proj.c
 *
 * Created: 24/08/2022 07:59:10 م
 * Author : Zakaria yahia
 * 
 */ 

#include "EEPROM.h"
#include "LCD.h"
#include "KEYPAD.h"
#include "TIMER0.h"

uint8_t locker_state;


static void ctc_isr(void);

void Get_char(uint8_t*);
void Default_Password(void);
void change_Password(void);
void Get_Password(uint8_t*);
void Check_Password(uint8_t*);
void Home_Back(void);
int main(void)
{
	
	
	
	LCD_int();
	locker_state = EEPROM_read(9);
	KEYPAD_init();
	SETBIT(DDRC,0);
	uint8_t pass[10];
	
    
	
    while (1) 
    {
		
		
		if (EEPROM_read(8) != 1)
		{
			Default_Password();
		}
		LCD_write_command(0xc0);
		
		 if(locker_state !=1){
			
			Get_char(pass);
		}
		
		 if (locker_state==1)
		{
			Get_Password(pass);
			Check_Password(pass);
			
		}
		
		
		
		
		
	}
}

void Get_char(uint8_t *pass)
{
	uint8_t x=0;
	x= KEYPAD_read();
	LCD_write_command(0x01);
	LCD_write_command(0x80);
	LCD_write_string("Door is open ");
	LCD_write_command(0xc0);
	LCD_write_string("Press * close");
	_delay_ms(2000);
	LCD_write_command(0x01);
	LCD_write_command(0x80);
	LCD_write_string("/ Change Password");
	LCD_write_command(0xc0);
	LCD_write_string("- key to Reset");
	_delay_ms(1000);
	while (x == KEYPAD_read());
	
	if (KEYPAD_read()=='\\')
	{
		
		change_Password();
	}
	else if (KEYPAD_read()=='*')
	{
		SETBIT(PORTC,0);
		_delay_ms(100);
		CLRBIT(PORTC,0);
		
		LCD_write_command(0x01);
		LCD_write_command(0x80);
		LCD_write_string("Door is closed");
		_delay_ms(1000);
		
		EEPROM_write(9,1);
		locker_state =EEPROM_read(9);
		
		}else if (KEYPAD_read()=='-'){
		SETBIT(PORTC,0);
		_delay_ms(100);
		CLRBIT(PORTC,0);
		Get_Password(pass);
		Check_Password(pass);
	}
}
void Get_Password(uint8_t* pass)
{
	  
	uint8_t i=0;

	if(locker_state== 1)
	{
		
		uint8_t x=0;
		
			LCD_write_command(0x01);
			LCD_write_command(0x80);
			LCD_write_string("Enter Password:");
			LCD_write_command(0xc0);
		
		
		i=0;
		while (i !=4)
		{
			x= KEYPAD_read();
			while(x=='c'){Home_Back();}
			if(x !=0)
			{
				pass[i]= x;
				
				LCD_write_data('*');
				
				SETBIT(PORTC,0);
				_delay_ms(100);
				CLRBIT(PORTC,0);
				i++;
				while(x == KEYPAD_read());
				_delay_ms(1);
				
			}
		}
		
	}
	else
	{
		LCD_write_command(0x01);
		LCD_write_command(0x80);
		LCD_write_string("Reset");
		LCD_write_command(0xc0);
		LCD_write_string("Enter Command:");
		_delay_ms(1000);
		LCD_write_command(0x01);
		LCD_write_command(0x80);
		LCD_write_string("Enter Command:");
		LCD_write_command(0xc0);
		i=0;
		uint8_t x=0;
		while (i!=10)
		{
			x= KEYPAD_read();
			while(x=='c'){Home_Back();}
		if(x !=0)
		{
			pass[i]= x;
			
			LCD_write_data('*');
			
			SETBIT(PORTC,0);
			_delay_ms(100);
			CLRBIT(PORTC,0);
			i++;
			while(x == KEYPAD_read());
			_delay_ms(1);
			
		}
		}
		
		
	}
}

void Check_Password(uint8_t *pass)
{
	uint8_t i=0;
	uint8_t reset[10]={'0','0','0','0','0','0','0','0','0','0'};
	if (locker_state==1)
	{
		
		while(i<4)
		{
			if (pass[i] ==EEPROM_read(i))
			{
				i++;
			}
			else{
				break;
			}
			
			
		}
		if (i==4)
		{
			LCD_write_command(0x01);
			LCD_write_command(0x80);
			LCD_write_string("Correct");
			EEPROM_write(9,0);
			locker_state=0;
			_delay_ms(1000);
		}else
		{
			LCD_write_command(0x01);
			LCD_write_command(0x80);
			LCD_write_string("Wrong");
			LCD_write_command(0xc0);
			LCD_write_string("Try Again");
			_delay_ms(1000);
		}
	}
	else{
		
		while(i<10)
		{
			if (pass[i] ==reset[i])
			{
				i++;
			}
			else{
				break;
			}
			
			
		}
		if (i==10)
		{
			Default_Password();
			LCD_write_command(0x01);
			LCD_write_command(0x80);
			LCD_write_string("Reset is Done");
			_delay_ms(1000);
		}else
		{
			LCD_write_command(0x01);
			LCD_write_command(0x80);
			LCD_write_string("Wrong");
			LCD_write_command(0xc0);
			LCD_write_string("Try Again");
			_delay_ms(1000);
		}
		
	}
}
	

 void change_Password(void)
 {
	 uint8_t new_pass[5];
	 LCD_write_command(0x01);
	 LCD_write_string("Enter a new password");
	 timer0_ctc_isr = ctc_isr;
	 TIMER0_CTC_init(187);
	 SETBIT(PORTC,0);
	 
	 
	 
	 uint8_t i=0;
	 uint8_t x=0;
	x = KEYPAD_read();
	
    while(x == KEYPAD_read());
	LCD_write_command(0xc0);
	 while (i!=5)
	 {
		 
		 x = KEYPAD_read();
		 while(x=='c'){Home_Back();}
		 if(x !=0)
		 {
			 new_pass[i]=x;
			 LCD_write_data('*');
			 SETBIT(PORTC,0);
			 _delay_ms(100);
			 CLRBIT(PORTC,0);
			 i++;
			 while(x == KEYPAD_read());
			 _delay_ms(1);
			
		 }
	 }
	 if (new_pass[4]=='\\')
	 {
		 for(uint8_t p=0; p<4; p++)
		 {
			 EEPROM_write(p,new_pass[p]);
		 }
		 
		 LCD_write_command(0x01);
		 LCD_write_command(0x80);
		 LCD_write_string("Save Password");
		 LCD_write_command(0xc0);
		 LCD_write_string("Done..!");
		 _delay_ms(2000);
	 }else{
		  LCD_write_command(0x01);
		  LCD_write_command(0x80);
		  LCD_write_string("Save Password");
		  LCD_write_command(0xc0);
		  LCD_write_string("Failed...!");
		  _delay_ms(4000);
	 }
	 
	 
 }
 void Home_Back(void)
 {
	 main();
 }
 
 void Default_Password(void)
 {
	 for(uint8_t i=0; i<4; i++)
	 {
		 EEPROM_write(i,'0');
		 EEPROM_write(8,1);
	 }
 }
 static void ctc_isr(void){
	 static uint32_t count = 0;
	 count++;
	 if(count == 249){
		 CLRBIT(PORTC,0);
		 
		 count = 0;
	 }
 }
 
 
