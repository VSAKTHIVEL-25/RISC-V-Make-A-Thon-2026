#ifndef switch_H
#define switch_H
#include<stdint.h>

void switchinit(uint8_t PORT, uint8_t PIN);

uint8_t switchread(uint8_t PORT, uint8_t PIN);

#endif
