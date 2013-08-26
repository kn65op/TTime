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
  
}