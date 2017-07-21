#include "Employees.hpp"

using namespace employees;


////////////////////////////////////

double Manager::salary()
{
  return 13000;   
}

////////////////////////////////////


Agent::Agent(double a): amount(a)
{}
double Agent::salary()
{
  return 5000 + amount * 0.05;
}

////////////////////////////////////

Worker::Worker(double t) : time(t)
{}
double Worker::salary()
{
return 100 * time;
}
