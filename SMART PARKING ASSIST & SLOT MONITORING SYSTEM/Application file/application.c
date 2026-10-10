#include <stdint.h>

#include "GPIO.h"
#include "IR.h"
#include "ultrasonic.h"
#include "Sevensegment.h"
#include "LED.h"
#include "PWM.h"
#include "Buzzer.h"
#include "LCD.h"

/* HC-SR04 */
#define TRIG_PORT PORT_E
#define TRIG_PIN  4

#define ECHO_PORT PORT_E
#define ECHO_PIN  5

/* Two parking slot IR sensors */
#define IR1_PORT PORT_F
#define IR1_PIN  0   /* A0 */

#define IR2_PORT PORT_F
#define IR2_PIN  1   /* A1 */

/* Distance indicator LEDs */
#define LED_A2_PORT PORT_F
#define LED_A2_PIN  2

#define LED_A3_PORT PORT_F
#define LED_A3_PIN  3

#define LED_A4_PORT PORT_F
#define LED_A4_PIN  4

#define LED_A5_PORT PORT_F
#define LED_A5_PIN  5

/* Seven-segment display */
#define SEGMENT_PORT PORT_K

/*
 * Set to 1 if IR detects an object with LOW output.
 * Set to 0 if IR detects an object with HIGH output.
 */
#define IR_ACTIVE_LOW 1

/*
 * Your requested display encoding:
 * 0 free slots -> display 0
 * 1 free slot  -> display 1
 * 2 free slots -> display 0
 *
 * This assumes a common-cathode display.
 * Use ANODE instead if your display is common-anode.
 */
#define SEGMENT_TYPE CATHODE

static uint8_t IR_ObjectDetected(uint8_t pin)
{
    uint8_t value = IR_Read(PORT_F, pin);

#if IR_ACTIVE_LOW
    return (value == 0);
#else
    return (value != 0);
#endif
}

static void ParkingLEDs_Init(void)
{
    ledinit(LED_A2_PORT, LED_A2_PIN);
    ledinit(LED_A3_PORT, LED_A3_PIN);
    ledinit(LED_A4_PORT, LED_A4_PIN);
    ledinit(LED_A5_PORT, LED_A5_PIN);
}

static void ParkingLEDs_Update(uint16_t distance_cm)
{
    /* Turn every distance LED off first */
    ledoff(LED_A2_PORT, LED_A2_PIN);
    ledoff(LED_A3_PORT, LED_A3_PIN);
    ledoff(LED_A4_PORT, LED_A4_PIN);
    ledoff(LED_A5_PORT, LED_A5_PIN);

    if (distance_cm == 0xFFFFU || distance_cm == 0)
    {
        return;
    }

    if (distance_cm > 30)
    {
        ledon(LED_A2_PORT, LED_A2_PIN);
    }
    else if (distance_cm > 15 && distance_cm <= 30)
    {
        ledon(LED_A3_PORT, LED_A3_PIN);
    }
    else if (distance_cm >= 5 && distance_cm <= 15)
    {
        ledon(LED_A4_PORT, LED_A4_PIN);
    }
    else if (distance_cm < 5)
    {
        ledon(LED_A5_PORT, LED_A5_PIN);
    }

    /* 5 cm to less than 10 cm: all LEDs remain off */
}

int main(void)
{
    uint16_t distance_cm;
    uint8_t slot1_occupied;
    uint8_t slot2_occupied;
    uint8_t free_slots;
    uint8_t segment_value;

    /* Initialize sensors */
    IR_Init(IR1_PORT, IR1_PIN);
    IR_Init(IR2_PORT, IR2_PIN);

    Ultrasonic_Init(TRIG_PORT, TRIG_PIN,
                    ECHO_PORT, ECHO_PIN);

    /* Initialize indicators */
    ParkingLEDs_Init();

    SevenSegment2_Init(SEGMENT_PORT, SEGMENT_PORT);

    /* Initialize display and buzzer */
    LCD_Init();
    Buzzer_Init();

    while (1)
    {
        /* Read both slot sensors */
        slot1_occupied = IR_ObjectDetected(IR1_PIN);
        slot2_occupied = IR_ObjectDetected(IR2_PIN);

        /* Count free parking slots */
        free_slots = 0;

        if (!slot1_occupied)
            free_slots++;

        if (!slot2_occupied)
            free_slots++;

        /* Read ultrasonic distance for parking assistance */
        distance_cm = Ultrasonic_Read();

        /* Update the LCD */
        LCD_ParkingDisplay(distance_cm, free_slots);

        /*
         * Requested seven-segment mapping:
         * Both occupied -> 0
         * One free      -> 1
         * Both free     -> 0
         */
        if (free_slots == 0)
{
    segment_value = 0;
}
else if (free_slots == 1)
{
    segment_value = 1;
}
else
{
    segment_value = 2;
}

SevenSegmentwrite(SEGMENT_PORT, segment_value, SEGMENT_TYPE);
        SevenSegmentwrite(SEGMENT_PORT,
                          segment_value,
                          SEGMENT_TYPE);

        /* Update distance LEDs */
        ParkingLEDs_Update(distance_cm);

        /* Buzzer depends only on ultrasonic distance */
        Buzzer_Alert(distance_cm);
    }

    return 0;
}