
#include "ADC.h"


void ADC_Init(void)
{
    // Use AVCC as the reference voltage
    AD_MUX = (1 << REF_S0);

    // Enable ADC and set prescaler to 128
    // 16 MHz / 128 = 125 kHz ADC clock
    ADC_SRA = (1 << AD_EN) |
             (1 << ADP_S2) |
             (1 << ADP_S1) |
             (1 << ADP_S0);
}

uint16_t ADC_Read(uint8_t channel)
{
   volatile uint16_t ADC;
    // ATmega2560 has ADC channels 0 to 15
    if (channel > 15)
    {
        return 0;
    }

    // Select ADC channel and keep AVCC reference
    AD_MUX = (AD_MUX & 0xF0) | (channel & 0x0F);

    // Start conversion
    ADC_SRA |= (1 << AD_SC);

    // Wait until conversion is complete
    while (ADC_SRA & (1 << AD_SC))
    {
        // Wait
    }

    // Return 10-bit result: 0 to 1023
    return ADC;
}
