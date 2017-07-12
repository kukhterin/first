#include <iostream>
using namespace std;

//Класс со переменной, подсчитывающей количество объектов класса и выводящий при создании нового объекта ео номер

class SerialNumber{
private:
  static int serialNumber;
public:
  SerialNumber()
  {serialNumber++;
   cout << "\nMy serial number is " << serialNumber;
  }
  
};
int SerialNumber::serialNumber = 0;
int main() {
    SerialNumber s1, s2, s3;
    return 0;
}
