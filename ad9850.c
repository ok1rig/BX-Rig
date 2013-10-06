/*
 * ad9850.c
 *
 * Created: 5.10.2013 10:17:30
 *  Author: Tomas
 *
 * FOR DEVICE START-UP IN SERIAL MODE, HARDWIRE PIN 2 AT 0, PIN 3 AT 1, AND PIN 4 AT 1
 */ 
#include <avr/io.h>
#include "ad9850.h"


void dds_clk_pulse(void) {
	DDS_W_CLK_PORT |= (1 << DDS_W_CLK);
	DDS_W_CLK_PORT &= (0 << DDS_W_CLK);	
}

void dds_fq_ud_pulse(void) {
	DDS_FQ_UD_PORT |= (1 << DDS_FQ_UD);
	DDS_FQ_UD_PORT &= (0 << DDS_FQ_UD);	
}

void dds_init(void) {
	//set IO pins to OUT
	DDS_W_CLK_DDR |= (1 << DDS_W_CLK);
	DDS_FQ_UD_DDR |= (1 << DDS_FQ_UD);
	DDS_DATA_DDR |= (1 << DDS_DATA);
	
	// All set to LOW
	DDS_W_CLK_PORT &= (0 << DDS_W_CLK);
	DDS_FQ_UD_PORT &= (0 << DDS_FQ_UD);
	DDS_DATA_PORT &= (0 << DDS_DATA);
	
	dds_clk_pulse();
	dds_fq_ud_pulse();
}


unsigned long int dds_freq2word(long int hz) {	
	return DDS_TUNING_WORD_MAX * hz / DDS_REF_FREQ;
}


void dds_spi_byte(unsigned char d) {	
	for (int loop=1; loop != 8; loop++) {
		if (d & 0x01) 
			DDS_DATA_PORT |= (1 << DDS_DATA);
		else
			DDS_DATA_PORT &= (0 << DDS_DATA);
		d >>= 1;
		dds_clk_pulse();
	}
}

void dds_load(long int tuning_word) {		
	for (int loop=1; loop != 3; loop++) {
		dds_spi_byte(tuning_word & 0xFF);
		tuning_word >>= 8;
	}
	
	dds_spi_byte(0x00);		//control word
	dds_fq_ud_pulse();		//store
}