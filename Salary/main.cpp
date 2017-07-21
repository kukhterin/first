#include <iostream>
#include "Employees.hpp"

using namespace employees;

int main() {
    
  Employee *emparr[9]; //список из 9 указателей на Employee
  emparr[0] = new Manager;
  emparr[1] = new Manager;
  emparr[2] = new Manager;
  emparr[3] = new Agent(100000);
  emparr[4] = new Agent(110000);
  emparr[5] = new Agent(120000);
  emparr[6] = new Worker(140);
  emparr[7] = new Worker(150);
  emparr[8] = new Worker(160);
  
  for (int i = 0; i < 9; i++)
  {
    std::cout <<  "Salary of employee #" << i
    << ": " << emparr[i] ->salary() << std::endl;
    delete emparr[i];

  }
  
}
