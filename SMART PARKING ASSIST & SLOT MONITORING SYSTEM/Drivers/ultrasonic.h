
#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include <stdint.h>

void Ultrasonic_Init(uint8_t trig_port, uint8_t trig_pin,
                     uint8_t echo_port, uint8_t echo_pin);

uint16_t Ultrasonic_Read(void);

void Ultrasonic_Delay_ms(uint16_t ms);

#endif