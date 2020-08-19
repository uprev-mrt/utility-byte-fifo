/**
  *@file byte_fifoTest.cpp
  *@brief unit tests for the byte_fifo class
  *@author Jason Berger
  *@date 02/16/2019
  */
#ifdef UNIT_TESTING_ENABLED

extern "C"{

  #include "byte_fifo.c"
}
#include <gtest/gtest.h>


uint8_t c_testSize = 64;
byte_fifo_t test_byte_fifo_c;
uint8_t c_comp;


//C tests
//Test pushing data to byte_fifo
TEST(ByteFifo_Test, Push_c)
{
  byte_fifo_init( &test_byte_fifo_c, c_testSize);
  //push 64 bytes into byte_fifo
  for(uint8_t i=0; i < c_testSize; i++)
  {
    //verify count
    ASSERT_EQ(i, test_byte_fifo_c.mCount);

    //make sure we get a status byte_fifo_OK for each push
    ASSERT_EQ(byte_fifo_OK , byte_fifo_push(&test_byte_fifo_c, &i));
  }
}

//Verify Overflow handling
TEST(ByteFifo_Test, Overflow_c)
{
  ASSERT_EQ(byte_fifo_OVERFLOW , byte_fifo_push(&test_byte_fifo_c, &c_comp));
  ASSERT_EQ(c_testSize, test_byte_fifo_c.mCount);
}

//Verify Overflow handling
TEST(ByteFifo_Test, PeekBuffer_c)
{
  uint8_t peekBuf[10];

  uint8_t tp = byte_fifo_peek_buf(&test_byte_fifo_c, peekBuf, 10);

  ASSERT_EQ(10 * sizeof(int), tp);

  for(uint8_t i =0; i < 10; i++)
  {
    ASSERT_EQ(i, peekBuf[i]);
  }

}

//Test popping data from byte_fifo
TEST(ByteFifo_Test, Pop_c)
{
  //push 64 bytes into byte_fifo
  for(uint8_t i=0; i < c_testSize; i++)
  {
    //make sure we get a status byte_fifo_OK
    ASSERT_EQ(c_testSize-i, test_byte_fifo_c.mCount);
    ASSERT_EQ(byte_fifo_OK , byte_fifo_pop(&test_byte_fifo_c, &c_comp));
    ASSERT_EQ(i, c_comp);
  }
}

//Verify Underflow handling
TEST(ByteFifo_Test, Underflow_c)
{
    ASSERT_EQ(byte_fifo_UNDERFLOW , byte_fifo_pop(&test_byte_fifo_c, &c_comp));
    ASSERT_EQ(0, test_byte_fifo_c.mCount);
}

#endif
