#include <iostream>
using namespace std;

//Использование класса для представления пункта взимания платежей

class tollBoth{
private:
  unsigned int carsCount;//количество машин
  double sum;//подсчёт выручки

public:
  tollBoth(): carsCount(0), sum(0.0)
  {}
  void payingCar()
  {
    carsCount++;
    sum += 0.50;
  }
  void noPayingCar()
  {
    carsCount++;
  }
  void display() const
  {
    cout << "Всего машин: " << carsCount <<endl;
    cout << "Выручка:  " << sum << "$" <<endl;
  }
  
};

int main()
{
  tollBoth tb;
  char ch;
  bool flag = 1;
  
  while(flag)
  {
    cout << "\nНажмите 0 для машины, проезжающей без оплаты";
    cout << "\nНажмите 1, чтобы оплатить проезд\n";
    cin >> ch;
    switch(ch)
    {
      case '0':
	tb.noPayingCar();
      break;
      case '1':
	tb.payingCar();
      break;
      default:
	cout << "\nНедопустимый ввод";
    }
    tb.display();
    cout << "\nПродолжить(y/n)?";
    cin >> ch;
    if(ch == 'n') 
    {
      flag = 0;
    }
  }
    
}
