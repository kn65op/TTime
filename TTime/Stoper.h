#pragma once

#include <string>
#include <iostream>
#include <chrono>

namespace TTime
{

class StoperException
{
public:
  /**
   * Specify Exception description.
   * @param desription
   */
  StoperException(std::string desription);
  
  /**
   * Return std::string with exception description.
   * @return Exception description.
   */
  operator std::string();
  
private:
  std::string message;
  
};

std::ofstream & operator<<(std::ostream & out, StoperException ex);

class Stoper
{
public:
  /**
   * Default constructor. Creates simple stoper.
   */
  Stoper(void);
  
  /**
   * Destructor.
   */
  ~Stoper(void);

  /**
   * Start stoper with specified name. 
   * Name has to be unique. It is forbidden to start stoper, which has name that was already used.
   * If name is in use StoperException will be thrown.
   * @param name Stoper name.
   */
  static void start(std::string name);
  
  /**
   * Start stoper.
   * @param from_beginning Specify if stoper will start from 0 or from stopped time.
   */
  void start(bool from_beginning);
  
  /**
   * Clear actual time. If stoper runs it will stop and set measured time to 0.
   */
  void clear();
  
  /**
   * End stoper. If stoper wasn't started does nothing.
   */
  void stop();
  
  /**
   * Get measured time. If stoper runs it will return actual time.
   * @return Measured time. 
   */
  long getTime();

private:
  typedef std::chrono::high_resolution_clock clock;
  typedef std::chrono::microseconds unit;

  bool running;
  clock::time_point begin;
  unit measured_time;
};

} //namespace TTime