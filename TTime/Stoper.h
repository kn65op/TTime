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
public:
  NotExistStoperException(std::string d) : StoperException(d)
  {
  }
};

class NotStartedStoperException : public StoperException
{
public:
  NotStartedStoperException(std::string d) : StoperException(d)
  {
  }
};

class StartedStoperException : public StoperException
{
public:
  StartedStoperException(std::string d) : StoperException(d)
  {
  }
};

std::ostream & operator<<(std::ostream & out, StoperException ex);

class Stoper
{
public:
  typedef long long unit;
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
   * If name is in use and stoper is running then StartedStoperException will be thrown.
   * @param name Stoper name.
   * @param from_beginning Specify if stoper starts from 0 or continue counting.
   * If stoper wasn't exist it starts from 0 event if specified otherwise.
   * Default is start from beginning.
   */
  static void start(std::string name, bool from_beginning = true);

  /**
   * Clear exitsing stopers without exceptions
   */
  static void clearStopers();

  /**
   * Stop stoper with specified name
   * If stoper with specified name doesn't existed throws NoExistedStoperException.
   * If stoper with specified name doesn't started throws NotStartedStoperException.
   * @param name Stoper name.
   * @return Measured time.
   */
  static unit stop(std::string name);
  
  /**
   * Get measured time.
   * If stoper with specified name doesn't existed throws NoExistedStoperException.
   * @param name Stoper name.
   * @return Measured time.
   */
  static unit getTime(std::string name);

  /**
   * Clear actual time.
   * If stoper with specified name doesn't existed throws NoExistedStoperException.
   * @param name Stoper name.
   * @return Measured time.
   */
  static unit clear(std::string name);
  
  /**
   * Start stoper. Default start is from beginning.
   * If stoper was started and not stopped it throw StartedStoperException.
   * @param from_beginning Specify if stoper will start from 0 or from stopped time.
   */
  void start(bool from_beginning = true); 
  
  /**
   * Clear actual time. If stoper runs it will stop and set measured time to 0.
   * @return Measured time.
   */
  unit clear();
  
  /**
   * End stoper. If stoper wasn't started it throw NotStartedStoperException.
   * @return Measured time.
   */
  unit stop();
  
  /**
   * Get measured time. If stoper runs it will return actual time.
   * @return Measured time. 
   */
  unit getTime();

private:
  typedef std::chrono::high_resolution_clock clock;

  typedef std::string Key;
  typedef Stoper* OwnPtr;
  typedef std::map<Key, OwnPtr> StoperContainer;
  typedef StoperContainer::iterator StoperIterator;
  typedef std::pair<Key, OwnPtr> StoperPair;

  bool running;
  clock::time_point begin;
  unit measured_time;
  
  static StoperContainer stopers;
  static Stoper* findStoper(std::string name, bool throw_exception = true);

  unit calculateDiffernce(clock::time_point & begin, clock::time_point & end);
};

} //namespace TTime