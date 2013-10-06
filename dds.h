/*
 * dds.h
 *
 * Created: 5.10.2013 10:18:58
 *  Author: Tomas
 */ 

#define W_CLK		PORTD5
#define W_CLK_DDR	DDRD
#define W_CLK_PORT	DDRD

#define FQ_UD		PORTD6
#define FQ_UD_DDR	DDRD
#define FQ_UD_PORT	PORTD

#define DATA		PORTD7
#define DATA_DDR	DDRD
#define DATA_PORT	PORTD

#define REF_FREQ	125000000
#define TUNING_WORD_MAX 2 ^ 32


void dds_init(void);
void dds_load(long int tuning_word);
unsigned long int dds_freq2word(long int hz);

