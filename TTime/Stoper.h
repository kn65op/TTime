#pragma once

#include <string>
#include <iostream>
#include <chrono>
#include <map>

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
  operator std::string() const;
  
private:
  std::string message;
  
};

class NotExistStoperException : public StoperException
{
  
};

class NotStartedStoperException : public StoperException
{
  
};

std::ostream & operator<<(std::ostream & out, StoperException ex);

class Stoper
{
public:
  typedef std::chrono::microseconds unit;
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
   * Name has to be unique. It is forbidden to start stoper which runs nad has name that was already used.
   * If stoper with name already exists, but was stopped then can be specified if starts from 0 or continue counting.
   * If name is in use and stoper is running then StoperException will be thrown.
   * @param name Stoper name.
   * @param from_begining Specify if stoper starts from 0 or continue counting.
   * If stoper wasn't exist it starts from 0 event if specified otherwise.
   * Default is start from begining.
   */
  inline static void start(std::string name, bool from_begining = true);

  /**
   * Stop stoper with specified name
   * If stoper with specified name doesn't existed throws NoExistedStoperException.
   * If stoper with specified name doesn't started throws NotStartedStoperException.
   * @param name Stoper name.
   * @return Measured time.
   */
  inline static unit stop(std::string name);
  
  /**
   * Get measured time.
   * If stoper with specified name doesn't existed throws NoExistedStoperException.
   * @param name Stoper name.
   * @return Measured time.
   */
  static unit getTime(std::string name);
  
  /**
   * Start stoper.
   * @param from_beginning Specify if stoper will start from 0 or from stopped time.
   */
  inline void start(bool from_beginning);
  
  /**
   * Clear actual time. If stoper runs it will stop and set measured time to 0.
   */
  void clear();
  
  /**
   * End stoper. If stoper wasn't started does nothing.
   * @return Measured time.
   */
  inline unit stop();
  
  /**
   * Get measured time. If stoper runs it will return actual time.
   * @return Measured time. 
   */
  unit getTime();

private:
  typedef std::chrono::high_resolution_clock clock;

  bool running;
  clock::time_point begin;
  unit measured_time;
  
  std::map<std::string, Stoper*> stopers;
};

} //namespace TTime