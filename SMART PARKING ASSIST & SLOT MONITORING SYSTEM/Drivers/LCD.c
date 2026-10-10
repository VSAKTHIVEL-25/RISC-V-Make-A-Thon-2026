
#include <stdint.h>
#include "GPIO.h"
#include "LCD.h"

/* LCD data pins: PA4 to PA7 */
#define LCD_DATA_PORT PORT_A
#define LCD_RS_PORT   PORT_C
#define LCD_RS_PIN    0
#define LCD_EN_PIN    1

static void LCD_ShortDelay(void)
{
    volatile uint16_t i;

    for (i = 0; i < 100; i++)
    {
        /* Short settling delay */
    }
}

static void LCD_LongDelay(void)
{
    volatile uint16_t i;

    for (i = 0; i < 60000U; i++)
    {
        /* Power-on and command settling delay */
    }
}

static void LCD_Enable(void)
{
    pinwrite(LCD_RS_PORT, LCD_EN_PIN, 1);
    LCD_ShortDelay();

    pinwrite(LCD_RS_PORT, LCD_EN_PIN, 0);
    LCD_ShortDelay();
}

static void LCD_SendNibble(uint8_t nibble)
{
    pinwrite(LCD_DATA_PORT, 4, (nibble >> 0) & 1);
    pinwrite(LCD_DATA_PORT, 5, (nibble >> 1) & 1);
    pinwrite(LCD_DATA_PORT, 6, (nibble >> 2) & 1);
    pinwrite(LCD_DATA_PORT, 7, (nibble >> 3) & 1);

    LCD_Enable();
}

static void LCD_Command(uint8_t command)
{
    pinwrite(LCD_RS_PORT, LCD_RS_PIN, 0);

    LCD_SendNibble(command >> 4);
    LCD_SendNibble(command & 0x0F);

    if (command == 0x01 || command == 0x02)
        LCD_LongDelay();
    else
        LCD_ShortDelay();
}

static void LCD_Data(uint8_t data)
{
    pinwrite(LCD_RS_PORT, LCD_RS_PIN, 1);

    LCD_SendNibble(data >> 4);
    LCD_SendNibble(data & 0x0F);

    LCD_ShortDelay();
}

static void LCD_String(const char *text)
{
    while (*text)
    {
        LCD_Data((uint8_t)*text);
        text++;
    }
}

static void LCD_Number(uint16_t number)
{
    char digits[5];
    uint8_t i = 0;

    if (number == 0)
    {
        LCD_Data('0');
        return;
    }

    while (number > 0 && i < 5)
    {
        digits[i++] = (char)('0' + number % 10);
        number /= 10;
    }

    while (i > 0)
    {
        LCD_Data((uint8_t)digits[--i]);
    }
}

void LCD_Clear(void)
{
    LCD_Command(0x01);
}

void LCD_Init(void)
{
    pinset(LCD_DATA_PORT, 4, OUTPUTS);
    pinset(LCD_DATA_PORT, 5, OUTPUTS);
    pinset(LCD_DATA_PORT, 6, OUTPUTS);
    pinset(LCD_DATA_PORT, 7, OUTPUTS);

    pinset(LCD_RS_PORT, LCD_RS_PIN, OUTPUTS);
    pinset(LCD_RS_PORT, LCD_EN_PIN, OUTPUTS);

    pinwrite(LCD_RS_PORT, LCD_RS_PIN, 0);
    pinwrite(LCD_RS_PORT, LCD_EN_PIN, 0);

    LCD_LongDelay();

    /* Initialize LCD in 4-bit mode */
    LCD_SendNibble(0x03);
    LCD_LongDelay();

    LCD_SendNibble(0x03);
    LCD_ShortDelay();

    LCD_SendNibble(0x03);
    LCD_ShortDelay();

    LCD_SendNibble(0x02);

    LCD_Command(0x28);  /* 4-bit, 2-line, 5x8 font */
    LCD_Command(0x0C);  /* Display ON, cursor OFF */
    LCD_Command(0x06);  /* Increment cursor */
    LCD_Command(0x01);  /* Clear display */
}

void LCD_Display(uint16_t distance_cm, uint8_t occupied)
{
    LCD_Command(0x80);
    LCD_String("Distance: ");

    if (distance_cm == 0xFFFFU)
    {
        LCD_String("-- cm     ");
    }
    else
    {
        LCD_Number(distance_cm);
        LCD_String(" cm     ");
    }

    LCD_Command(0xC0);

    if (occupied)
        LCD_String("Status: OCCUPIED");
    else
        LCD_String("Status: FREE    ");
}
void LCD_ParkingDisplay(uint16_t distance_cm, uint8_t free_slots)
{
    /* First row: parking slot status */
    LCD_Command(0x80);

    if (free_slots == 0)
        LCD_String("Slots: OCCUPIED ");
    else if (free_slots == 1)
        LCD_String("Slots: 1 FREE   ");
    else
        LCD_String("Slots: 2 FREE   ");

    /* Second row: ultrasonic distance */
    LCD_Command(0xC0);
    LCD_String("Distance: ");

    if (distance_cm == 0xFFFFU)
    {
        LCD_String("-- cm ");
    }
    else
    {
        LCD_Number(distance_cm);
        LCD_String(" cm ");
    }

    /* Pad remaining columns to avoid stale characters */
    LCD_String("   ");
}