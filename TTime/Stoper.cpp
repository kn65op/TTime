#include "Stoper.h"

#include <algorithm>

using namespace TTime;
using namespace std::chrono;

Stoper::StoperContainer Stoper::stopers = Stoper::StoperContainer();

StoperException::StoperException(std::string desription)
{
  message = desription;
}

StoperException::operator  std::string() const
{
  return message;
}

std::ostream & operator <<(std::ostream & out, StoperException ex)
{
  out << (std::string)ex;
  return out;
}

Stoper::Stoper(void)
{
  measured_time = unit::zero();
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
}

void Stoper::start(std::string name, bool from_beginning)
{
  StoperIterator it = stopers.find(name);
  if (it != stopers.end()) //stoper exists
  {
    Stoper* stoper = it->second;
    if (stoper->running)
    {
      throw StoperException("Stoper " + name + " already defined and is running");
    }
    else
    {
      stoper->start(from_beginning);
    }
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
  StoperIterator it = stopers.find(name);
  if (it != stopers.end()) //stoper exists
  {
    return it->second->stop(); //TODO:
  }
  else
  {
    throw NotExistStoperException("Stoper named " + name + " does not exist");
  }
}



Stoper::unit Stoper::getTime(std::string name)
{
  return Stoper::unit::zero();
}

void Stoper::start(bool from_beginning)
{
  
}

Stoper::unit Stoper::clear(std::string name)
{
  return Stoper::unit::zero();
}

Stoper::unit Stoper::clear()
{
  return Stoper::unit::zero();
}

Stoper::unit Stoper::stop()
{
  return Stoper::unit::zero();
}

Stoper::unit Stoper::getTime()
{
  return Stoper::unit::zero();
}
