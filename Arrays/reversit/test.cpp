#include "test.hpp"
#include "reverseIt.hpp"
#include <cstring>
#include <iostream>

void test(const char* s1, const char* s2)
{
  
  char* c1 = new char[strlen(s1) +1];
  strncpy(c1, s1, strlen(s1)+1);
  
  reverseit(c1);

  if(!strcmp(c1,s2))
  {std::cout << "\nТест пройден!" << std::endl;}
  else
  {std::cout << "Что-то пошло не так!" <<std::endl;}
  delete c1;
}