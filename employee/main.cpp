#include <iostream>
using namespace std;

//Расширенная версия класса Enployee, включающая класс Date и перечичление etype
//В main предложить пользователю ввести информацию о 3 работниках. затем вывести ее на экран

 class Date{
  private:
    char ch;
    int month;
    int day;
    int year;
  public:
    void get_date()
    {
      cout << "\nВведите дату трудоустройства в формате ДД/MM/ГГ: ";
      cin >> day >> ch>> month >> ch >> year;
    
    }
    void display() 
    {
      cout << day << ch << month << ch << year << endl;
    }
  
  
  };

class Employee {
private:
  int number;
  float salary;
  Date date;
  enum etype {laborer, secretary, manager, accounter, executive, researcher};
  etype position;
  char ch;
public:
  Employee()
  {
    get_employee();
  }
  void get_employee()
  { 
   cout<< "\nВведите номер сотрудника: " << endl;
   cin >> number;
   cout<< "\nВведите оклад сотрудника: " << endl;
   cin >> salary;
   date.get_date();
   cout << "\nВведите первую букву должности(laborer, secretary, manager, accounter, executive, researcher): ";
   cin >> ch;
   switch(ch)
   {
     case 'l': position =  laborer; 
     break;
     case 's': position =  secretary; 
     break;
     case 'm': position =  manager; 
     break;
     case 'a': position =  accounter; 
     break;
     case 'e': position =  executive; 
     break;
     case 'r': position =  researcher; 
     break;
   }
  } 
  
  void put_employee()
  {
    cout << "\nНомер сотрудника: " << number << "\nОклад: " << salary << "\nДата рудоустройства: ";
    date.display();
    cout << "\nДолжность: ";
    switch(position)
    {
     case laborer: cout << "laborer"; 
     break;
     case secretary: cout << "secretary"; 
     break;
     case manager: cout << "manager"; ; 
     break;
     case accounter: cout << "accounter"; ; 
     break;
     case executive: cout << "executive"; ; 
     break;
     case researcher: cout << "researcher"; ; 
     break;
      
    }
    cout << endl;  
  }  
};
int main() {
  Employee e1, e2, e3;
  e1.put_employee();
  e2.put_employee();
  e2.put_employee();

  
    return 0;
}
