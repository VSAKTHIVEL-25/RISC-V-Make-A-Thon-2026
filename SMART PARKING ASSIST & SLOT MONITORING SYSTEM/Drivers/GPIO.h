#ifndef GPIO_H
#define GPIO_H
#include <stdint.h>

#define PORT_A 0
#define PORT_B 1
#define PORT_C 2
#define PORT_D 3
#define PORT_E 4
#define PORT_F 5
#define PORT_G 6
#define PORT_H 7
#define PORT_J 8
#define PORT_K 9
#define PORT_L 10

#define INPUTS 0
#define inputs 0
#define OUTPUTS 1
#define outputs 1
#define ANODE 1
#define CATHODE 2






extern volatile uint16_t dr[11];

extern volatile uint16_t out[11];

extern volatile uint16_t inp[11];

void portset(uint8_t PORT, uint8_t type);

uint8_t portwrite(uint8_t PORT, uint8_t state);

uint8_t portread(uint8_t PORT);

void pinset(uint8_t PORT, uint8_t PIN, uint8_t type);

uint8_t pinwrite(uint8_t PORT, uint8_t PIN, uint8_t state);

uint8_t pinread(uint8_t PORT, uint8_t PIN);

void pintoggle(uint8_t PORT, uint8_t PIN);

#endif