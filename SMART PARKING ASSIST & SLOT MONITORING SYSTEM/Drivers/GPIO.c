#include"GPIO.h"
#include <stdint.h>
volatile uint16_t dr[11] = {
    0x21, 0x24, 0x27, 0x2A, 0x2D, 0x30, 0x33,
    0x101, 0x104, 0x107, 0x10A
};
volatile uint16_t out[11] = {
    0x22, 0x25, 0x28, 0x2B, 0x2E, 0x31, 0x34,
    0x102, 0x105, 0x108, 0x10B
};
volatile uint16_t inp[11] = {
    0x20, 0x23, 0x26, 0x29, 0x2C, 0x2F, 0x32,
    0x100, 0x103, 0x106, 0x109
};

void portset(uint8_t PORT, uint8_t type)
{
  volatile uint8_t *ddr;

    ddr = (volatile uint8_t *)dr[PORT];
    

    if (type == 0)
    {
        

        *ddr = 0x00;
    }

    else if (type == 1)
    {
        

        *ddr = 0xFF;
        
        
    }

    
}
uint8_t portwrite(uint8_t PORT, uint8_t state)
{
  
  
    volatile uint8_t *writes;
    writes = (volatile uint8_t *)out[PORT];
    *writes=state;
    return *writes;
  
  

}
uint8_t portread(uint8_t PORT)
{
  
    volatile uint8_t *reads;
    reads = (volatile uint8_t *)inp[PORT];
    
  
  return *reads;
}

void pinset(uint8_t PORT,uint8_t PIN,uint8_t type)
{
  volatile uint8_t *ddr;

    ddr = (volatile uint8_t *)dr[PORT];
    if(type==0)
    {
      *ddr&=~(1<<PIN);
    }
    else if(type==1)
    {
      *ddr|=(1<<PIN);
    }
}
uint8_t pinwrite(uint8_t PORT,uint8_t PIN, uint8_t state)
{
  
  
    volatile uint8_t *writes;
    writes = (volatile uint8_t *)out[PORT];
    if(state==1)
    {
    *writes|=(1<<PIN);
    
    }
    else if(state==0)
    {
    *writes&=~(1<<PIN);
    }
  
  return *writes;

}
uint8_t pinread(uint8_t PORT,uint8_t PIN)
{
  
  
    volatile uint8_t *reads;
    reads = (volatile uint8_t *)inp[PORT];
    
  
  return ((*reads>>PIN)&1);

}
void pintoggle(uint8_t PORT, uint8_t PIN)
{
  volatile uint8_t *writes;

    writes = (volatile uint8_t *)out[PORT];

    *writes ^= (1 << PIN);
}