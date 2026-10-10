#include <stdint.h>
#include "ultrasonic.h"
#include "GPIO.h"

/* ATmega2560 Timer1 registers */
#define TCCR1A_REG (*(volatile uint8_t *)0x80)
#define TCCR1B_REG (*(volatile uint8_t *)0x81)
#define TCNT1L_REG (*(volatile uint8_t *)0x84)
#define TCNT1H_REG (*(volatile uint8_t *)0x85)

/* Timer1: 16 MHz / 8 = 2 MHz */
#define ECHO_TIMEOUT_TICKS 60000U

static uint8_t trig_port;
static uint8_t trig_pin;
static uint8_t echo_port;
static uint8_t echo_pin;

static uint16_t Timer1_Read(void)
{
    uint8_t low;
    uint8_t high;

    low = TCNT1L_REG;
    high = TCNT1H_REG;

    return ((uint16_t)high << 8) | low;
}

static void Timer1_Write(uint16_t value)
{
    TCNT1H_REG = (uint8_t)(value >> 8);
    TCNT1L_REG = (uint8_t)value;
}

static uint8_t WaitForEcho(uint8_t level)
{
    Timer1_Write(0);

    while (pinread(echo_port, echo_pin) != level)
    {
        if (Timer1_Read() >= ECHO_TIMEOUT_TICKS)
        {
            return 0;
        }
    }

    return 1;
}

void Ultrasonic_Init(uint8_t t_port, uint8_t t_pin,
                     uint8_t e_port, uint8_t e_pin)
{
    trig_port = t_port;
    trig_pin = t_pin;
    echo_port = e_port;
    echo_pin = e_pin;

    pinset(trig_port, trig_pin, OUTPUTS);
    pinset(echo_port, echo_pin, INPUTS);

    pinwrite(trig_port, trig_pin, 0);

    /* Normal mode, prescaler = 8 */
    TCCR1A_REG = 0;
    TCCR1B_REG = (1U << 1);

    Timer1_Write(0);
}

uint16_t Ultrasonic_Read(void)
{
    uint16_t pulse_ticks;

    /* Trigger pulse: at least 10 us */
    pinwrite(trig_port, trig_pin, 0);
    Ultrasonic_Delay_ms(1);

    pinwrite(trig_port, trig_pin, 1);
    Timer1_Write(0);

    while (Timer1_Read() < 20U)
    {
        /* 20 ticks = 10 us */
    }

    pinwrite(trig_port, trig_pin, 0);

    /* Wait for ECHO to rise */
    if (!WaitForEcho(1))
    {
        return 0xFFFFU;
    }

    /* Measure the HIGH pulse */
    if (!WaitForEcho(0))
    {
        return 0xFFFFU;
    }

    pulse_ticks = Timer1_Read();

    /* 116 ticks approximately equals 1 cm */
    return pulse_ticks / 116U;
}

void Ultrasonic_Delay_ms(uint16_t ms)
{
    while (ms--)
    {
        Timer1_Write(0);

        while (Timer1_Read() < 2000U)
        {
            /* 2000 ticks = approximately 1 ms */
        }
    }
}