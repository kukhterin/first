#include "reverseIt.hpp"

void reverseit(const char* s)
{
  size_t len = strlen(s);
  for(int i=0; i < len/2; i++)
  {
    char temp = s[i];
    s[i] = s[len-i-1];
    s[len-i-1] = s[i];
  }
  std::cout << s <<std::endl;
