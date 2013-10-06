/*
 * hd44780.c
 *
 * Created: 6.10.2013 18:40:21
 *  Author: Tomas
 */ 

#include <avr/io.h>
#include "hd44780.h"

void lcd_init(void) {
	DATA_DDR |= (1 << DATA);
}