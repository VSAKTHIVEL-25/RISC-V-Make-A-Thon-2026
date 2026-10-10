#include <stdint.h>
#ifndef ADC_H
#define ADC_H
#define AD_MUX*(volatile uint8_t*)0x7C
#define ADC_SRB *(volatile uint8_t*)0X7B
#define ADC_SRA *(volatile uint8_t*)0x7A
#define REF_S0 6
#define AD_SC 6
#define ADP_S0 0
#define ADP_S1 1
#define ADP_S2 2
#define AD_EN 7
void ADC_Init(void);
uint16_t ADC_Read(uint8_t channel);
#endif