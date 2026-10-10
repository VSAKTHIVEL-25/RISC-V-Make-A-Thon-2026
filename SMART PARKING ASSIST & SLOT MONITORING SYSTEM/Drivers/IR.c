
#include "IR.h"
#include "GPIO.h"

void IR_Init(uint8_t PORT, uint8_t PIN)
{
    pinset(PORT, PIN, INPUTS);
}

uint8_t IR_Read(uint8_t PORT, uint8_t PIN)
{
    return pinread(PORT, PIN);
}
