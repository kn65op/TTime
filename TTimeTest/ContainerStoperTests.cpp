#include "ContainerStoperTestClasses.h"

#include <chrono>
#include <thread>

using namespace TTime;

TEST_F(ContainerStoperTest, DifferentStopers)
{
  ASSERT_NO_THROW(startStoperOne());
  ASSERT_NO_THROW(startStoperTwo());
  ASSERT_NO_THROW(startStoperThree());
}

TEST_F(ContainerStoperTest, ClearStopers)
{
  ASSERT_NO_THROW(startStoperOne());
  ASSERT_NO_THROW(startStoperTwo());
  ASSERT_NO_THROW(startStoperThree());
  Stoper::clearStopers();
  ASSERT_NO_THROW(startStoperOne());
  ASSERT_NO_THROW(startStoperTwo());
  ASSERT_NO_THROW(startStoperThree());
}

TEST_F(ContainerStoperTest, SameStopers)
{
  ASSERT_NO_THROW(startStoperOne());
  ASSERT_THROW(startStoperOne(), StoperException);
}

TEST_F(ContainerStoperTest, NonZeroAfterStart)
{
  ASSERT_NO_THROW(startStoperOne());
  ASSERT_NE(getTimeStoperOne(), getZero());
}

TEST_F(ContainerStoperTest, NonZeroAfterStop)
{
  ASSERT_NO_THROW(startStoperOne());
  ASSERT_NE(stopStoperOne(), getZero());
}

TEST_F(ContainerStoperTest, BiggerAfterRestart)
{
  ASSERT_NO_THROW(startStoperOne());
  Stoper::unit end1 = stopStoperOne();
  startStoperOne(false);
  ASSERT_GT(stopStoperOne(), end1);
}

TEST_F(ContainerStoperTest, LessAfterRestartFromBeginning)
{
  ASSERT_NO_THROW(startStoperOne());
  std::this_thread::sleep_for(std::chrono::milliseconds(2000));
  Stoper::unit end1 = stopStoperOne();
  startStoperOne(true);
  ASSERT_LT(stopStoperOne(), end1);
}

TEST_F(ContainerStoperTest, LessAfterRestartFromBeginningDefault)
{
  ASSERT_NO_THROW(startStoperOne());
  std::this_thread::sleep_for(std::chrono::milliseconds(2000));
  Stoper::unit end1 = stopStoperOne();
  ASSERT_NO_THROW(startStoperOne());
  ASSERT_LT(stopStoperOne(), end1);
}

TEST_F(ContainerStoperTest, GetTimeBeforeStop)
{
  ASSERT_NO_THROW(startStoperOne());
  Stoper::unit end1 = getTimeStoperOne();
  ASSERT_GT(stopStoperOne(), end1);
}

TEST_F(ContainerStoperTest, GetTimeAfterStop)
{
  ASSERT_NO_THROW(startStoperOne());
  Stoper::unit end1 = stopStoperOne();
  ASSERT_EQ(stopStoperOne(), end1);
}

TEST_F(ContainerStoperTest, StartAfterStart)
{
  ASSERT_NO_THROW(startStoperOne());
  ASSERT_THROW(startStoperOne(), StartedStoperException);
}

TEST_F(ContainerStoperTest, GetTimeNoExisted)
{
  ASSERT_THROW(getTimeStoperOne(), NotExistStoperException);
}

TEST_F(ContainerStoperTest, StopNotExisted)
{
  ASSERT_THROW(stopStoperOne(), NotExistStoperException);
}

TEST_F(ContainerStoperTest, StopNotStarted)
{
  startStoperOne();
  stopStoperOne();
  ASSERT_THROW(stopStoperOne(), NotStartedStoperException);
}


TEST_F(ContainerStoperTest, TestClear)
{
  startStoperOne();
  ASSERT_NE(stopStoperOne(), getZero());
  clearStoperOne();
  ASSERT_EQ(getTimeStoperOne(), getZero());
}

TEST_F(ContainerStoperTest, TestClearRunning)
{
  startStoperOne();
  ASSERT_NE(getTimeStoperOne(), getZero());
  clearStoperOne();
  ASSERT_EQ(getTimeStoperOne(), getZero());
  ASSERT_NO_THROW(startStoperOne());
}

