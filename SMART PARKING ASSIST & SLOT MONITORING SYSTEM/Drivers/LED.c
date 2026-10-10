#include"LED.h"
#include"GPIO.h"
#include<stdint.h>
void ledinit(uint8_t PORT,uint8_t PIN)
{
  pinset(PORT, PIN, OUTPUTS);
}
void ledon(uint8_t PORT, uint8_t PIN)
{
  pinwrite(PORT, PIN, 1);
}
void ledoff(uint8_t PORT, uint8_t PIN)
{
  pinwrite(PORT, PIN, 0);
}