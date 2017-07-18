#include <iostream>
#include <string>
#include <string.h>

int main() {
  void reverseit(char s[]);
  const int MAX = 100;
  char s[MAX];
  std::cout << "Insert your string: ";
  std::cin.get(s, MAX);
  reverseit(s);
  std::cout << s << std::endl;
       
    return 0;
}

void reverseit(char s[])
{
  int len = strlen(s);
  for(int i=0; i < len/2; i++)
  {
    char temp = s[i];
    s[i] = s[len-i-1];

  }
}