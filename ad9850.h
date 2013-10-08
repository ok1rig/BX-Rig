/*
 * ad9850.h
 *
 * Created: 5.10.2013 10:18:58
 *  Author: Tomas
 */ 

#define DDS_W_CLK		PORTD5
#define DDS_W_CLK_DDR	DDRD
#define DDS_W_CLK_PORT	DDRD

#define DDS_FQ_UD		PORTD6
#define DDS_FQ_UD_DDR	DDRD
#define DDS_FQ_UD_PORT	PORTD

#define DDS_DATA		PORTD7
#define DDS_DATA_DDR	DDRD
#define DDS_DATA_PORT	PORTD

#define DDS_REF_FREQ	125000000UL
#define DDS_TUNING_WORD_MAX (1ULL << 32)

void dds_init(void);
void dds_load(long int tuning_word);
unsigned long int dds_freq2word(long int hz);

