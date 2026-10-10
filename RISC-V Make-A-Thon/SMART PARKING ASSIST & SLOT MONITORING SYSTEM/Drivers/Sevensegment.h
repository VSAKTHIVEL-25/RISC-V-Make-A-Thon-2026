
#ifndef Sevensegment_H
#define Sevensegment_H

#include <stdint.h>

void SevenSegmentset(uint8_t PORT);

extern const uint8_t segment_pattern1[10];
extern const uint8_t segment_pattern2[10];

uint8_t SevenSegmentwrite(uint8_t PORT, uint8_t number, uint8_t com);
uint8_t SevenSegment_Clear(uint8_t PORT, uint8_t com);

void SevenSegment2_Init(uint8_t PORT1, uint8_t PORT2);
void SevenSegment2_Write(uint8_t PORT1, uint8_t PORT2,
                         uint8_t number, uint8_t com);

#endif