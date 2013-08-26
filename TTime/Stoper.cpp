#include "Stoper.h"

using namespace TTime;
using namespace std::chrono;

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

void Stoper::start(std::string name, bool from_begining)
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
      stoper->start(from_begining);
    }
  }
  else //stoper not exists
  {
    Stoper *stoper = new Stoper();
    stopers.insert(std::make_pair(name, stoper));
    stoper->start(true);
  }
}