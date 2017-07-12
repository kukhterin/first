#include <iostream>
using namespace std;

class Employee {
private:
  int number;
  float salary;
public:
  Employee()
  {cout<< "\nВведите номер сотрудника: " << endl;
   cin >> number;
   cout<< "\nВведите оклад сотрудника: " << endl;
   cin >> salary;
  }
  void display()
  {cout << "\n" << "Сотрудник № " << number << " , оклад: " << salary << endl;}
};
int main() {
  Employee e1, e2, e3;
  e1.display();
  e2.display();
  e3.display();
    
   
    return 0;
}
