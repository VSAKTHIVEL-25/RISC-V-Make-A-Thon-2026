#include"GPIO.h"
#include"Sevensegment.h"
#include<stdint.h>
const uint8_t segment_pattern1[10] ={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f};
const uint8_t segment_pattern2[10]={~0x3f,~0x06,~0x5B,~0x4F,~0x66,~0x6D,~0x7D,~0x07,~0x7F,~0x6F};
void SevenSegmentset(uint8_t PORT)
{
  pinset(PORT, 0, OUTPUTS); 
    pinset(PORT, 1, OUTPUTS); 
    pinset(PORT, 2, OUTPUTS); 
    pinset(PORT, 3, OUTPUTS); 
    pinset(PORT, 4, OUTPUTS); 
    pinset(PORT, 5, OUTPUTS); 
    pinset(PORT, 6, OUTPUTS); 
}

uint8_t SevenSegmentwrite(uint8_t PORT,uint8_t number,uint8_t com)
{
  SevenSegmentset(PORT);
  if(number>9)
  {
    return 0;
  }

  volatile uint8_t *writes;
    writes = (volatile uint8_t *)out[PORT];
    if(com==1)
    {
    *writes=segment_pattern2[number];
    }
    else if(com==2)
    {
      *writes=segment_pattern1[number];
    }
    return *writes;
}
uint8_t SevenSegment_Clear(uint8_t PORT,uint8_t com)
{
  volatile uint8_t *writes;
    writes = (volatile uint8_t *)out[PORT];
    if(com==ANODE)
    {
    *writes=0xff;
    }
    else
    {
      *writes=0x00;
    }
    return *writes;
}

void SevenSegment2_Init(uint8_t PORT1, uint8_t PORT2)
{
    SevenSegmentset(PORT1);
    SevenSegmentset(PORT2);
}

void SevenSegment2_Write(uint8_t PORT1, uint8_t PORT2,
                         uint8_t number, uint8_t com)
{
    uint8_t tens;
    uint8_t units;

    if (number > 99)
    {
        return;
    }

    tens = number / 10;
    units = number % 10;

    SevenSegmentwrite(PORT1, tens, com);
    SevenSegmentwrite(PORT2, units, com);
}
