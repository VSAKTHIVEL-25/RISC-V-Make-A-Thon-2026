
#ifndef IR_H
#define IR_H

#include <stdint.h>

void IR_Init(uint8_t PORT, uint8_t PIN);
uint8_t IR_Read(uint8_t PORT, uint8_t PIN);

#endif