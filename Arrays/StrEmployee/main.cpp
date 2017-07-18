#include <iostream>
#include <string>
#include <string.h>

//cоздать класс Employee с именем типа string и номером, которые вводятся пользователем
//в main создать массив Employee (100), предложить пользователю ввести до ста служащих, затем вывести на экран введённую информацию
class Employee{
private:
  std::string name;
  long number;
public:
  void getdata(){
    std::cout << "Insert name: ";
    std::cin >> name;
    std::cout << "Insert number: ";
    std::cin >> number;
  }
  void putdata()
  {
    std::cout << "Number: " << number <<std::endl;
    std::cout << "Name: " << name <<std::endl;
    std::cout << std::endl;
  }
  
};


int main() {
  static int MAX = 100;
  int in_num = 0;
  char confirm = 'y';
  Employee earray[MAX];
  
  do
  { 
  std::cout << "Insert employee info: " <<std::endl;
  earray[in_num].getdata();
  std::cout << "Continue(y/n)?";
  std::cin >> confirm;
  in_num++;
  }  while(confirm != 'n');
  std::cout << "List of employers: " << std::endl;
  for(int i = 0; i < in_num; i++)
  {
    earray[i].putdata();
  }
  
}