/*!
   \@file byte_fifo_c.case
   \@brief pure C implementation of byte_fifo
   \@author Jason Berger
   \@date 05/03/2017
*/


#include "byte_fifo.h"
#include <stdlib.h>
#include <string.h>

#define byte_fifo_LOCK //pFifo->mLock =1//while(pFifo->lock){delay_ms(1);} pFifo->lock = 1
#define byte_fifo_UNLOCK //pFifo->mLock = 0

#define byte_fifo_min(X,Y) (((X) < (Y)) ? (X) : (Y))
#define byte_fifo_max(X,Y) (((X) > (Y)) ? (X) : (Y))


void byte_fifo_init(byte_fifo_t* pFifo, int depth)
{
  pFifo->mBuffer = (uint8_t*) malloc(depth);
  pFifo->mHead = 0;
  pFifo->mTail = 0;
  pFifo->mMaxLen = depth;
  pFifo->mCount = 0;
  pFifo->mLock = 0;
}

void byte_fifo_deinit(byte_fifo_t* pFifo)
{
  free(pFifo->mBuffer);
}

int byte_fifo_push( byte_fifo_t* pFifo, const uint8_t data)
{
	byte_fifo_LOCK;

    if (pFifo->mCount >= pFifo->mMaxLen) /* check if byte_fifo is full */
    {
		    byte_fifo_UNLOCK;
        return byte_fifo_OVERFLOW;
    }

    int next = pFifo->mHead + 1;                          /*next is where head will point to after this write*/

    if (next >= pFifo->mMaxLen)                           /* wrap head at end of buffer*/
    {
        next = 0;
    }

    pFifo->mCount++;                                      /* increment count*/
    pFifo->mBuffer[pFifo->mHead] = data;

    pFifo->mHead = next;                                  /* set head to next */

    byte_fifo_UNLOCK;

    return byte_fifo_OK;  // return success to indicate successful push.
}

int byte_fifo_pop( byte_fifo_t* pFifo, uint8_t* data)
{
	  byte_fifo_LOCK;
    // if the head isn't ahead of the tail, we don't have any characters
    if (pFifo->mCount <= 0) // check if circular buffer is empty
    {
		    byte_fifo_UNLOCK;
        return byte_fifo_UNDERFLOW;          // and return with an error
    }

    // next is where tail will point to after this read.
    int next = pFifo->mTail + 1;
    if (next >= pFifo->mMaxLen)
    {
        next = 0;
    }

    *data = pFifo->mBuffer[pFifo->mTail];
    
    pFifo->mTail = next;             // tail to next data offset.

    if(pFifo->mCount > 0)
    {
        pFifo->mCount--;
    }
    byte_fifo_UNLOCK;

    return byte_fifo_OK;  // return success to indicate successful push.
}

int byte_fifo_push_buf( byte_fifo_t* pFifo, const uint8_t* data, int len)
{
  int result = 0;
  for(int i=0; i < len; i++)
  {
    result |= byte_fifo_push(pFifo, data[i]);
  }
  return result;
}

int byte_fifo_pop_buf( byte_fifo_t* pFifo, uint8_t* data, int len)
{
  int result = 0;
  for(int i=0; i < len; i++)
  {
    result |= byte_fifo_pop(pFifo, &data[i]);
  }
  return result;
}

int byte_fifo_clear( byte_fifo_t* pFifo)
{
  pFifo->mHead = 0;
  pFifo->mTail = 0;
  pFifo->mCount = 0;

  return byte_fifo_OK;
}

