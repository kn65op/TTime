#include <gtest\gtest.h>

#include <Stoper.h> 

class ContainerStoperTest : public ::testing::Test
{
protected:
  void SetUp()
  {
    name_one = "qwe";
    name_two = "rty";
    name_three = "asd";
  }

  void startStoperOne(bool fb = true)
  {
    TTime::Stoper::start(name_one, fb);
  }
  
  void startStoperTwo()
  {
    TTime::Stoper::start(name_two);
  }

  void startStoperThree()
  {
    TTime::Stoper::start(name_three);
  }

  TTime::Stoper::unit stopStoperOne()
  {
    return TTime::Stoper::stop(name_one);
  }

  TTime::Stoper::unit getTimeStoperOne()
  {
    return TTime::Stoper::getTime(name_one);
  }

  void clearStoperOne()
  {
    TTime::Stoper::clear(name_one);
  }

  TTime::Stoper::unit getZero()
  {
    return TTime::Stoper::unit::zero();
  }

  std::string name_one;
  std::string name_two;
  std::string name_three;
};