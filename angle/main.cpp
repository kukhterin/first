#include <iostream>
using namespace std;

//Объект для хранения координат с двумя конструкторами и 2 методами: задающим пользовательские значения и отображающим значения
//в main сначала создать объект с помощью трехаргументного конструктора, потом циклически запрашивать пользователя ввести значения и отображать ввод на экране.
class Angle{
private:
  int deg;
  float min;
  char dir;
public:
  
  Angle(): deg(0), min(0), dir(0)
  {}
  Angle(int dg, float m, char dr): deg(dg), min(m), dir(dr)
  {}
  
  void set_coordinates()
  {
    cout << "\nЗадайте координату точки: ";
    cout << "\nЗадайте направление (E/W/N/S) ";
    cin >> dir;
    cout << "\nЗадайте градусы : ";
    cin >> deg;
    cout << "\nЗадайте минуты: ";
    cin >> min;
  }
  void display()
  {
    cout << "\n" << deg << '\xF8' << min << "'" << dir;
    
  }
  
  
};



int main() {
  Angle a1(179, 59.9, 'E');
  a1.display();
  char flag = 'y';
  while (flag != 'n') 
  {
    a1.set_coordinates();
    a1.display();
    cout << "\nПродолжить?(y/n) ";
    cin >> flag;
  }

    
    return 0;
}
