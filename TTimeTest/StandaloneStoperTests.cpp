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
  std::this_thread::sleep_for(std::chrono::milliseconds(2));
  ASSERT_NE(stoper.getTime(), getZero());
}

TEST_F(StandaloneStoperTest, NonZeroAfterStartStop)
{
  stoper.start();
  std::this_thread::sleep_for(std::chrono::milliseconds(2));
  ASSERT_NE(stoper.stop(), getZero());
}

TEST_F(StandaloneStoperTest, BiggerAfterRestart)
{
  stoper.start();
  std::this_thread::sleep_for(std::chrono::milliseconds(2));
  Stoper::unit end1 = stoper.stop();
  stoper.start(false);
  std::this_thread::sleep_for(std::chrono::milliseconds(1));
  ASSERT_GT(stoper.stop(), end1);
}

TEST_F(StandaloneStoperTest, LessAfterRestartFromBeginning)
{
  stoper.start();
  std::this_thread::sleep_for(std::chrono::milliseconds(20));
  Stoper::unit end1 = stoper.stop();
  stoper.start(true);
  std::this_thread::sleep_for(std::chrono::milliseconds(2));
  ASSERT_LT(stoper.stop(), end1);
}

TEST_F(StandaloneStoperTest, LessAfterRestartFromBeginningDefault)
{
  stoper.start();
  std::this_thread::sleep_for(std::chrono::milliseconds(20));
  Stoper::unit end1 = stoper.stop();
  stoper.start();
  std::this_thread::sleep_for(std::chrono::milliseconds(2));
  ASSERT_LT(stoper.stop(), end1);
}

TEST_F(StandaloneStoperTest, GetTimeBeforeStop)
{
  stoper.start();
  std::this_thread::sleep_for(std::chrono::milliseconds(2));
  Stoper::unit end1 = stoper.getTime();
  std::this_thread::sleep_for(std::chrono::milliseconds(2));
  ASSERT_GT(stoper.stop(), end1);
}

TEST_F(StandaloneStoperTest, GetTimeAfterStop)
{
  stoper.start();
  std::this_thread::sleep_for(std::chrono::milliseconds(2));
  Stoper::unit end1 = stoper.stop();
  std::this_thread::sleep_for(std::chrono::milliseconds(2));
  ASSERT_EQ(stoper.getTime(), end1);
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

TEST_F(StandaloneStoperTest, TestClear)
{
  stoper.start();
  std::this_thread::sleep_for(std::chrono::milliseconds(2));
  ASSERT_NE(stoper.stop(), getZero());
  std::this_thread::sleep_for(std::chrono::milliseconds(2));
  ASSERT_NE(stoper.clear(), getZero());
  ASSERT_EQ(stoper.getTime(), getZero());
}

TEST_F(StandaloneStoperTest, TestClearRunning)
{
  stoper.start();
  std::this_thread::sleep_for(std::chrono::milliseconds(2));
  Stoper::unit get, clear;
  get = stoper.getTime();
  ASSERT_NE(get, getZero());
  std::this_thread::sleep_for(std::chrono::milliseconds(2));
  clear = stoper.clear();
  ASSERT_NE(clear, getZero());
  ASSERT_NE(get, clear);
  ASSERT_EQ(stoper.getTime(), getZero());
  ASSERT_NO_THROW(stoper.start());
}
