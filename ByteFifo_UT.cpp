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


uint8_t byte_fifo_testSize = 64;
byte_fifo_t test_byte_fifo_c;
uint8_t byte_fifo_comp;


//C tests
//Test pushing data to byte_fifo
TEST(ByteFifo_Test, Push_c)
{
  byte_fifo_init( &test_byte_fifo_c, byte_fifo_testSize);
  //push 64 bytes into byte_fifo
  for(uint8_t i=0; i < byte_fifo_testSize; i++)
  {
    //verify count
    ASSERT_EQ(i, test_byte_fifo_c.mCount);

    //make sure we get a status byte_fifo_OK for each push
    ASSERT_EQ(byte_fifo_OK , byte_fifo_push(&test_byte_fifo_c, i));
  }
}

//Verify Overflow handling
TEST(ByteFifo_Test, Overflow_c)
{
  ASSERT_EQ(byte_fifo_OVERFLOW , byte_fifo_push(&test_byte_fifo_c, byte_fifo_comp));
  ASSERT_EQ(byte_fifo_testSize, test_byte_fifo_c.mCount);
}


//Test popping data from byte_fifo
TEST(ByteFifo_Test, Pop_c)
{
  //push 64 bytes into byte_fifo
  for(uint8_t i=0; i < byte_fifo_testSize; i++)
  {
    //make sure we get a status byte_fifo_OK
    ASSERT_EQ(byte_fifo_testSize-i, test_byte_fifo_c.mCount);
    ASSERT_EQ(byte_fifo_OK , byte_fifo_pop(&test_byte_fifo_c, &byte_fifo_comp));
    ASSERT_EQ(i, byte_fifo_comp);
  }
}

//Verify Underflow handling
TEST(ByteFifo_Test, Underflow_c)
{
    ASSERT_EQ(byte_fifo_UNDERFLOW , byte_fifo_pop(&test_byte_fifo_c, &byte_fifo_comp));
    ASSERT_EQ(0, test_byte_fifo_c.mCount);
}

#endif
