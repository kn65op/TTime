#include <gtest\gtest.h>

#include <Stoper.h> 

class StandaloneStoperTest : public ::testing::Test
{
protected:
  void SetUp()
  {

  }

  TTime::Stoper::unit getZero()
  {
    return 0;
  }

  TTime::Stoper stoper;
};