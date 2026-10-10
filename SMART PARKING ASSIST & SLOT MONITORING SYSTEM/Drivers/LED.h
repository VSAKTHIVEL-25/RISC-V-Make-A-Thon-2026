#ifndef LED_H
#define LED_H
#include<stdint.h>
void ledinit(uint8_t PORT,uint8_t PIN);
void ledon(uint8_t PORT, uint8_t PIN);

void ledoff(uint8_t PORT, uint8_t PIN);
#endif
