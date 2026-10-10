#ifndef LCD_H
#define LCD_H

#include <stdint.h>

void LCD_Init(void);
void LCD_Display(uint16_t distance_cm, uint8_t occupied);
void LCD_ParkingDisplay(uint16_t distance_cm, uint8_t free_slots);
void LCD_Clear(void);

#endif