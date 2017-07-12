#include <iostream>
using namespace std;

class Date{
private:
  char ch;
  int month;
  int day;
  int year;
public:
  void get_date()
  {
    cout << "\nВведите дату в формате ДД/MM/ГГ: ";
    cin >> day >> ch>> month >> ch >> year;
    
  }
  void display() 
  {
    cout << "\n" << day << ch << month << ch << year << endl;
  }
  
  
};

int main( ) {
    
  Date d1;
  d1.get_date();
  d1.display();
  
    return 0;
}
