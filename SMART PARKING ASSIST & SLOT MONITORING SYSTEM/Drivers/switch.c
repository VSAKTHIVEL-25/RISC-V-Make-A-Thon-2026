#include"switch.h"
#include"GPIO.h"
#include<stdint.h>

void switchinit(uint8_t PORT, uint8_t PIN)
{
    pinset(PORT, PIN, INPUTS);
}
uint8_t switchread(uint8_t PORT, uint8_t PIN)
{
    return pinread(PORT, PIN);
}