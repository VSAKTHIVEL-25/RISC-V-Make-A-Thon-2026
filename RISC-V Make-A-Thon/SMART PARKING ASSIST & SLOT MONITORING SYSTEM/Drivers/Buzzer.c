
#include <stdint.h>
#include "Buzzer.h"
#include "pwm.h"
#include "ultrasonic.h"

void Buzzer_Init(void)
{
    pwm_init();
    pwm_start();
    pwm_set_duty(0);
}

void Buzzer_Alert(uint16_t distance_cm)
{
    uint16_t pause_ms;

    if (distance_cm == 0xFFFFU || distance_cm == 0 ||
        distance_cm > 100)
    {
        pwm_set_duty(0);
        return;
    }

    if (distance_cm <= 25)
    {
        /* Very close: continuous PWM */
        pwm_set_duty(50);
        return;
    }

    if (distance_cm <= 50)
        pause_ms = 100;
    else
        pause_ms = 300;

    pwm_set_duty(50);
    Ultrasonic_Delay_ms(100);

    pwm_set_duty(0);
    Ultrasonic_Delay_ms(pause_ms);
}