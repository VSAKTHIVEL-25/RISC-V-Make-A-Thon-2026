
#include <stdint.h>
#include "delay.h"
#define TCCR_1A *(volatile uint8_t*)0x80
#define TCCR_1B *(volatile uint8_t*)0x81
#define OCR_1A *(volatile uint8_t*)0x88
#define TIFR_1 *(volatile uint8_t*)0x36
#define TCNT_1 *(volatile uint8_t*)0x84

void delaymill(volatile unsigned int ms)
{
    // Timer1 CTC mode
    TCCR_1A = 0X00;
    TCCR_1B = 0X00;

    TCCR_1B |= (1 << 3);              // CTC mode//WGM12
    TCCR_1B |= (1 << 2) | (1 << 0); // Prescaler 1024//CS12//CS10

    while (ms--)
    {
        TCNT_1 = 0;
        OCR_1A = 15;   // approximately 1 ms

        while (!(TIFR_1 & (1 << 2)))//OCF1
        {
            // Wait for compare match
        }

        TIFR_1 |= (1 << 2); // Clear flag
    }

    TCCR_1B = 0X00; // Stop timer
}
void delaysec(volatile unsigned int sec)
{
    delaymill(sec*1000);
}