#include "Stoper.h"

using namespace TTime;
using namespace std::chrono;

Stoper::Stoper(void)
{
  measured_time = unit::zero();
}


Stoper::~Stoper(void)
{
}
