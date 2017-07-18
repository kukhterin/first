#include <iostream>
using namespace std;
class Fraction{
  private:
  int numerator;
  int denominator;
  char ch = '/';
public:
  Fraction()
  {
    cout << "\nInsert fraction(n/n): ";
    cin >> numerator >> ch >> denominator;
  }
  void desplay()
  {
    cout << numerator << ch << denominator << endl;
  }
   void add(Fraction f)
  {
    desplay();
    numerator = numerator*f.denominator + f.numerator*denominator;
    denominator = denominator * f.denominator;
    cout << " + ";
    f.desplay();
    cout << " = ";
    desplay();
  }
  
  
};

int main() {
  char flag = 'y';
  while(flag != 'n')
  {
    Fraction f1,f2;
    f1.add(f2);
    cout << "Continue(y/n)";
    cin >> flag;
  
  }
   
    return 0;
}
