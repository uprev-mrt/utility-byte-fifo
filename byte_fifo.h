/*!
   \@file byte_byte_fifo.h
   \@brief header file for spi byte_fifo buffer
   \@author Jason Berger
   \@date 05/03/2017
*/

#pragma once

#include <stdint.h>

#define byte_fifo_OK 0
#define byte_fifo_OVERFLOW -1
#define byte_fifo_UNDERFLOW -2
/**
 *@brief creates byte_fifo
 *@param name : name of byte_fifo buffer
 *@param len : max number of elements in buffer
 *@return "Return of the function"
 */
#define byte_fifo_DEF(name,len)     \
  uint8_t name##_data[len];            \
  byte_fifo_t name = {                      \
        .mBuffer = name##_data,        \
        .mHead = 0,                 \
        .mTail = 0,                 \
        .mMaxLen = len,             \
        .mCount = 0,                \
    };

typedef struct {
    uint8_t *  mBuffer; //pointer to data buffer
    int mHead;      //next address to write to
    int mTail;      //next address to read from
    int mCount;     //number of items in byte_fifo
    int mMaxLen;
    uint8_t mLock;     //lock for byte_fifo that is accessed by multiple threads
} byte_fifo_t;


/**
 * @brief initialize byte_fifo
 * @param pFifo ptr to byte_fifo_t
 * @param depth number of items to to store in byte_fifobyte
 */
void byte_fifo_init(byte_fifo_t* pFifo, int depth);

/**
 * @brief deinitialize byte_fifo
 * @param pFifo ptr to byte_fifo
 */
void byte_fifo_deinit(byte_fifo_t* pFifo);

/**
 * @brief push a single 'object' into the byte_fifo
 * @param pFifo ptr to byte_fifo
 * @param data ptr to obj to add to byte_fifo
 * @return byte_fifo_OK on success  
 */
int byte_fifo_push(byte_fifo_t* pFifo, uint8_t data);

/**
 * @brief pops the next obj from the byte_fifo
 * 
 * @param pFifo ptr to byte_fifo
 * @param data ptr to store obj
 * @return byte_fifo_OK on success  
 */
int byte_fifo_pop(byte_fifo_t* pFifo, uint8_t* data);

/**
 * @brief push a buffer of objects into byte_fifo
 * @param pFifo ptr to byte_fifo
 * @param data ptr to objects to add to byte_fifo
 * @param len number of objects to add to byte_fifo
 * @return byte_fifo_OK on success 
 */
int byte_fifo_push_buf(byte_fifo_t* pFifo, const uint8_t* data, int len);

/**
 * @brief retrieve a buffer of objects from the byte_fifo
 * @param pFifo ptr to byte_fifo
 * @param data ptr to store objects
 * @param len number of objects to retrieve
 * @return byte_fifo_OK on success 
 */
int byte_fifo_pop_buf(byte_fifo_t* pFifo, uint8_t* data, int len);

/**
 * @brief deletes objects from byte_fifo
 * @param pFifo ptr to byte_fifo
 * @param len number of objects to remove
 * @return int 
 */
int byte_fifo_clear(byte_fifo_t* pFifo);

