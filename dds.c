/*
 * dds.c
 *
 * Created: 5.10.2013 10:17:30
 *  Author: Tomas
 *
 * FOR DEVICE START-UP IN SERIAL MODE, HARDWIRE PIN 2 AT 0, PIN 3 AT 1, AND PIN 4 AT 1
 */ 
#include <avr/io.h>
#include "dds.h"


void dds_clk_pulse(void) {
	W_CLK_PORT |= (1 << W_CLK);
	W_CLK_PORT &= (0 << W_CLK);	
}

void dds_fq_ud_pulse(void) {
	FQ_UD_PORT |= (1 << FQ_UD);
	FQ_UD_PORT &= (0 << FQ_UD);	
}

void dds_init(void) {
	//set IO pins to OUT
	W_CLK_DDR |= (1 << W_CLK);
	FQ_UD_DDR |= (1 << FQ_UD);
	DATA_DDR |= (1 << DATA);
	
	// All set to LOW
	W_CLK_PORT &= (0 << W_CLK);
	FQ_UD_PORT &= (0 << FQ_UD);
	DATA_PORT &= (0 << DATA);
	
	dds_clk_pulse();
	dds_fq_ud_pulse();
}


unsigned long int dds_freq2word(long int hz) {	
	return TUNING_WORD_MAX * hz / REF_FREQ;
}


void dds_spi_byte(unsigned char d) {
	int loop;	
	for (loop=1; loop != 8; loop++) {
		if (d & 0x01) 
			DATA_PORT |= (1 << DATA);
		else
			DATA_PORT &= (0 << DATA);
		d >>= 1;
		dds_clk_pulse();
	}
}

void dds_load(long int tuning_word) {
	int loop;
	
	for (loop=1; loop != 3; loop++) {
		dds_spi_byte(tuning_word & 0xFF);
		tuning_word >>= 8;
	}
	
	dds_spi_byte(0x00);		//control word
	dds_fq_ud_pulse();		//store

}