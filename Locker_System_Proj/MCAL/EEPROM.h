/*
 * EEPROM.h
 *
 * Created: 12/08/2022 06:19:12 م
 *  Author: Zakaria 
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_

#include "std_macros.h"

uint8_t EEPROM_read(uint16_t location);

void EEPROM_write(uint16_t location, uint8_t data);




#endif /* EEPROM_H_ */