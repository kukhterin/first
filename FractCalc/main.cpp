#include <iostream>
#include <stdlib.h>
using namespace std;


class Fract{
  private:
  int num, den;
  char ch = '/';
public:
  Fract(): num(0), den(0)
  {}
  void setFract()
  { cout << "\nВведите дробь(n/n): "; cin >> num >> ch >> den; }
  void desplay()
  { cout << num << ch << den << endl; }
  
    void lowterms()
  {
    long tnum, tden, temp, gcd;
    tnum = labs(num); //неотрицательные значения
    tden = labs(den);
    if(tden == 0)
    {cout  << "Недопустимый знаменатель";}
    else if(tnum == 0) 
    { num = 0; den = 1; return;}
    
    //нахождение наибольшего общего делителя
    
    while(tnum != 0) 
    {
      if(tnum < tden) 
      { temp = tnum; tnum = tden; tden = temp;}
      tnum = tnum - tden;
    }
    gcd = tden;
    num = num / gcd;
    den = den / gcd;
  }
  
  void fadd(Fract f1, Fract f2)
  { 
    f1.desplay();
    num = f1.num*f2.den + f2.num*f1.den;
    den = f1.den * f2.den;
    cout << " + ";
    f2.desplay();
    cout << " = ";
    lowterms();
    desplay();
  }
  void fsub(Fract f1, Fract f2)
  {
    f1.desplay();
    num = f1.num*f2.den - f2.num*f1.den;
    den = f1.den * f2.den;
    cout << " - ";
    f2.desplay();
    cout << " = ";
    lowterms();
    desplay();
  }
  void fmult(Fract f1, Fract f2)
  {
    
    f1.desplay();lowterms();
    num = f1.num * f2.num;
    den = f1.den * f2.den;
    cout << " * ";
    f2.desplay();
    cout << " = ";
    lowterms();
    desplay();
  }
  void fdiv(Fract f1, Fract f2)
  {
    
    f1.desplay();
    num = f1.num * f2.den;
    den = f1.den * f2.num;
    cout << " / ";
    f2.desplay();
    cout << " = ";
    lowterms();
    desplay();
  }
  

};



int main() {
  char act;
  Fract f1, f2, temp;
  char flag = 'y';
  while(flag != 'n') 
  {
  cout << "Введите первую дробь: " << endl;
  f1.setFract();
  cout << "Введите вторую дробь: " << endl;
  f2.setFract();
  cout << "Введите требуемое действие(+,-,*,/): " << endl;
  cin >> act;
  switch(act) 
  {
    case '+': 
      temp.fadd(f1,f2);
      break;
    case '-':
      temp.fsub(f1,f2);
      break;
    case '*':
      temp.fmult(f1,f2);
      break;
    case '/':
      temp.fdiv(f1,f2);
      break;
    default:
      cout << "Неверный ввод" <<endl;
  }
    
}
  
  
    return 0;
}
