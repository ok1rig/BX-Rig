/*
 * BX_Rig.c
 *
 * Created: 5.10.2013 9:43:20
 *  Author: Tomas
 */ 


#include <avr/io.h>
#include "ad9850.h"

int main(void)
{
	unsigned long int x;
	
	dds_init();
	x = dds_freq2word(7000001);
	x += 0; 
}