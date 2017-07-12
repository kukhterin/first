#include <iostream>
using namespace std;

//Используя Angle  и Number создать новый класс Ship с номером, соответствующим порядку создания объекта
//и координатами, задаваемыми пользователем и отображением соотв. полей
//в main создать 3 объекта, задать значения и вывести в консоль

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
    cout << "\nЗадайте направление (E/W/N/S) "; cin >> dir;
    cout << "Задайте градусы : ";  cin >> deg;
    cout << "Задайте минуты: "; cin >> min;
  }
  void display()
  {cout << "\n" << deg << '\xF8' << min << "'" << dir;}
};

class Ship{
  private:
    static int number;
    int serialnumber;
    Angle latitude;
    Angle longitude;
    
public:
  Ship()
  {number++;
   serialnumber = number;
  }
  void makeShip()
  { 
    cout << "\nВведите координаты корабля " << serialnumber;
    cout << "\nЗадайте широту: ";
    latitude.set_coordinates();
    cout << "\nЗадайте долготу: ";
    longitude.set_coordinates();
  }
  void getShip()
  {
    cout << "\nКорабль №" << serialnumber;
    cout << "\nКоординаты:";
    latitude.display();
    longitude.display();
    
  }
  
};
int Ship::number = 0;
int main() {
    Ship s1, s2, s3;
    s1.makeShip();
    s2.makeShip();
    s3.makeShip();
    s1.getShip();
    s2.getShip();
    s3.getShip();
    return 0;
}
