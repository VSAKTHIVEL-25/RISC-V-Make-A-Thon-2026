
#include <stdint.h>
#include "pwm.h"

#define DDRE_REG    (*(volatile uint8_t *)0x2D)
#define PORTE_REG   (*(volatile uint8_t *)0x2E)
#define TCCR3A_REG  (*(volatile uint8_t *)0x90)
#define TCCR3B_REG  (*(volatile uint8_t *)0x91)
#define OCR3A_REG   (*(volatile uint16_t *)0x98)

#define PE3_BIT     3
#define WGM30_BIT   0
#define WGM32_BIT   3
#define COM3A1_BIT  7
#define CS31_BIT    1
#define CS30_BIT    0

void pwm_init(void)
{
    DDRE_REG |= (1U << PE3_BIT);

    TCCR3A_REG = 0;
    TCCR3B_REG = 0;

    /* Fast PWM, 8-bit */
    TCCR3A_REG |= (1U << WGM30_BIT);
    TCCR3B_REG |= (1U << WGM32_BIT);

    OCR3A_REG = 0;
    PORTE_REG &= ~(1U << PE3_BIT);
}

void pwm_start(void)
{
    /* Prescaler 64 */
    TCCR3B_REG &= ~((1U << 2) |
                    (1U << CS31_BIT) |
                    (1U << CS30_BIT));

    TCCR3B_REG |= (1U << CS31_BIT) |
                  (1U << CS30_BIT);
}

void pwm_stop(void)
{
    TCCR3A_REG &= ~(1U << COM3A1_BIT);

    TCCR3B_REG &= ~((1U << 2) |
                    (1U << CS31_BIT) |
                    (1U << CS30_BIT));

    PORTE_REG &= ~(1U << PE3_BIT);
}

void pwm_set_duty(uint8_t duty)
{
    if (duty > 100)
        duty = 100;

    if (duty == 0)
    {
        TCCR3A_REG &= ~(1U << COM3A1_BIT);
        PORTE_REG &= ~(1U << PE3_BIT);
        OCR3A_REG = 0;
    }
    else
    {
        OCR3A_REG =
            (uint16_t)(((uint16_t)duty * 255U) / 100U);

        TCCR3A_REG |= (1U << COM3A1_BIT);
    }
}