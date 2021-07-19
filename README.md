# ByteFifo

This module provides a simple byte byte_fifo in pure C. Unless there are heavy resource constraints, it is recommended to use the regular Fifo module. 

byte_fifos can be defined staticly or initiallized dynamicly 

dynamic example:
```c
#include "Modules/Utilities/byte_fifo.h"

byte_fifo_t my_fifo;

uint8_t myBuf[64];

int main(void)
{
    //creates a byte_fifo that can store 64 uin16_t
    byte_fifo_init(&my_fifo, 64);   
    
    uint16_t myData = 0;
    for(int i =0; i < 64; i++)
    {
        myData++;
        byte_fifo_push(myData); //
    }

    byte_fifo_pop_buf(&my_fifo, myBuf, 64);

    return 0;
}
```


static example:
```c
#include "Modules/Utilities/byte_fifo.h"

byte_fifo_DEF(my_fifo, 64); //Expands to:
/*
uint8_t my_fifo_data[64];
byte_fifo_t my_fifo = {                      
    .mBuffer = my_fifo_data,     
    .mHead = 0,                 
    .mTail = 0,                 
    .mMaxLen = 64,             
    .mCount = 0,                
};
*/

uint8_t myBuf[64];

int main(void)
{
    uint8_t myData = 0;
    for(int i =0; i < 64; i++)
    {
        myData++;
        byte_fifo_push(myData); //
    }

    byte_fifo_pop_buf(&my_fifo, myBuf, 64);

    return 0;
}
```
> The main benefit of the static define is that it uses an array of 'type' to hold the data. This can help with debugging when the type is a struct. 
