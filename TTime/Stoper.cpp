#include "Stoper.h"

#include <algorithm>

using namespace TTime;
using namespace std::chrono;

Stoper::StoperContainer Stoper::stopers = Stoper::StoperContainer();
std::string Stoper::unit_name = "ms"; //connecteed with time_unit

StoperException::StoperException(std::string desription)
{
  message = desription;
}

StoperException::operator  std::string() const
{
  return message;
}

std::ostream & operator<<(std::ostream & out, StoperException & ex)
{
  out << (std::string)ex;
  return out;
}

Stoper::Stoper(void)
{
  measured_time = 0;
  running = false;
}


Stoper::~Stoper(void)
{
  
}

void Stoper::clearStopers()
{
  std::for_each(stopers.begin(), stopers.end(), [](StoperPair pair)
  {
    delete pair.second;
  });
  stopers.clear();
}

void Stoper::start(std::string name, bool from_beginning)
{
  Stoper * stoper = findStoper(name, false);
  if (stoper) //stoper exists
  {
    stoper->start(from_beginning);
  }
  else //stoper not exists
  {
    Stoper *stoper = new Stoper();
    stopers.insert(std::make_pair(name, stoper));
    stoper->start(true);
  }
}

Stoper::unit Stoper::stop(std::string name)
{
  return findStoper(name)->stop();
}



Stoper::unit Stoper::getTime(std::string name)
{
  return findStoper(name)->getTime();
}

void Stoper::start(bool from_beginning)
{
  if (running)
  {
    throw StartedStoperException("Stoper is already started");
  }
  if (from_beginning)
  {
    measured_time = 0;
  }
  running = true;
  begin = clock::now();
}

Stoper::unit Stoper::clear(std::string name)
{
  return findStoper(name)->clear();
}

Stoper::unit Stoper::clear()
{
  Stoper::unit tmp;
  tmp = calculateDiffernce(clock::now(), begin);
  running = false;
  measured_time = 0;
  return tmp;
}

Stoper::unit Stoper::stop()
{
  if (!running)
  {
    throw NotStartedStoperException("Stoper didn't start");
  }
  running = false;
  return measured_time += calculateDiffernce(clock::now(), begin);
}

Stoper::unit Stoper::getTime()
{
  if (running)
  {
    return calculateDiffernce(clock::now(), begin) + measured_time;
  }
  else
  {
    return measured_time;
  }
}

Stoper* Stoper::findStoper(std::string name, bool throw_exception)
{
  StoperIterator it = stopers.find(name);
  if (it != stopers.end()) //stoper exists
  {
    return it->second; //TODO:
  }
  else
  {
    if (throw_exception)
    {
      throw NotExistStoperException("Stoper named " + name + " does not exist");
    }
    else
    {
      return nullptr;
    }
  }
}

Stoper::unit Stoper::calculateDiffernce(clock::time_point & end, clock::time_point & begin)
{
  return duration_cast<time_unit>(end - begin).count();
}

std::string Stoper::getUnitName()
{
  return unit_name;
}
