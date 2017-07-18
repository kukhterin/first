#include "reverseIt.hpp"
#include "test.hpp"
#include <cstring>

void test(const char* s1, const char* s2)
{
  reverseit(s1);
  if(!strcmp(s1,s2))
  {std::cout << "\nТест пройден!" << std::endl;}
  else
  {std::cout << "Что-то пошло не так!" <<std::endl;}
}