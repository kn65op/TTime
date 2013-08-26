#include "StandaloneStoperTestClasses.h"

#include <chrono>
#include <thread>

using namespace TTime;

TEST_F(StandaloneStoperTest, ZeroBeforeStart)
{
  ASSERT_EQ(stoper.getTime(), getZero());
}

TEST_F(StandaloneStoperTest, NonZeroAfterStart)
{
  stoper.start();
  ASSERT_NE(stoper.getTime(), getZero());
}

TEST_F(StandaloneStoperTest, NonZeroAfterStartStop)
{
  stoper.start();
  ASSERT_NE(stoper.stop(), getZero());
}

TEST_F(StandaloneStoperTest, BiggerAfterRestart)
{
  stoper.start();
  Stoper::unit end1 = stoper.stop();
  stoper.start(false);
  ASSERT_GT(stoper.stop(), end1);
}

TEST_F(StandaloneStoperTest, LessAfterRestartFromBeginning)
{
  stoper.start();
  std::this_thread::sleep_for(std::chrono::milliseconds(2000));
  Stoper::unit end1 = stoper.stop();
  stoper.start(true);
  ASSERT_LT(stoper.stop(), end1);
}

TEST_F(StandaloneStoperTest, LessAfterRestartFromBeginningDefault)
{
  stoper.start();
  std::this_thread::sleep_for(std::chrono::milliseconds(2000));
  Stoper::unit end1 = stoper.stop();
  stoper.start();
  ASSERT_LT(stoper.stop(), end1);
}

TEST_F(StandaloneStoperTest, GetTimeBeforeStop)
{
  stoper.start();
  Stoper::unit end1 = stoper.getTime();
  ASSERT_GT(stoper.stop(), end1);
}

TEST_F(StandaloneStoperTest, GetTimeAfterStop)
{
  stoper.start();
  Stoper::unit end1 = stoper.stop();
  ASSERT_EQ(stoper.stop(), end1);
}

TEST_F(StandaloneStoperTest, StartAfterStart)
{
  stoper.start();
  ASSERT_THROW(stoper.start(), StartedStoperException);
}

TEST_F(StandaloneStoperTest, StopBeforeStart)
{
  ASSERT_THROW(stoper.stop(), NotStartedStoperException);
}