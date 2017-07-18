#include <iostream>
#include <string>
#include <iomanip>//setprecision
#include <stdlib.h>//atof
#include <sstream>//ostringstream

//написать класс money и  метод mstold, который принимает денежную строку со знаком $ и разделенную запятыми ($199, 123, 456.12) 
//и возвращает эквивалентное её значению число типа long double

//UPD
//написать класс ldtoms, переводящий, наоборот, long double  в денежную строку
//к началу строки добавляется $
//в случае лишних нолей в начале - убрать
//разделить запятыми/пробелами через каждые три цифры - не сделано

class Money{
private:
  std::string str; //строковое представление
  long double amount;//числовое представление
  
public:
  long double mstold();//moneyString to long double
  std::string ldtoms();//longdouble to moneyString
  void reverse(std::string);
  void display(){
    std::cout<< std::fixed << std::showpoint << std::setprecision(2) 
    << amount <<std::endl;
  }
};

long double Money::mstold()
{
  std::cout << "Введите вашу сумму: ";
  std::getline(std::cin, str);
  int len = str.length();
  std::string num;//промежуточная строка
  
  for(int i = 0; i<len; i++)
  {
    if(str[i] != ' ' && str[i] != ',' && str[i] != '$')
    {num.push_back(str[i]);}//поместить в конец строки
  }
  const char* c = num.c_str();//рпеобразование к char* для использования atof()
  amount = atof(c);
  return amount;
}

/////////////////////////////////////////////////////////////////////////////

std::string Money::ldtoms()
{
  std::string temp;
  std::string result = "$";
  std::string error = "Ваше число слишком большое!";;
  std::cout << "Введите ваше число: ";
  std::cin >> amount;
  if(amount <= 9999999999999990.00)
  {
    std::ostringstream convert;
    convert << std::fixed << std::setprecision(2) << amount;
    temp = convert.str();
    
    for(int i = 0; i < temp.length(); i++)
    {result.push_back(temp[i]);}//копируем посимвольно
    
    if(result.length()>0 && result[0] ==0)
    {result.erase(0,1);}//удаяем возможные нули в начале 
    
    reverse(result);
    for(int j = 4; j > 1;j-=3)
    {result.insert(j, ", ");}
    reverse(result);
    
    result.push_back('\0');
    std::cout << result;
    return result;
  }
  else
    {std::cout << error <<std::endl;}
    
}

void Money::reverse(std::string s)//для разделения запятыми
{
  int len = s.length();
  for(int i=0; i < len/2; i++)
  {
    char temp = s[i];
    s[i] = s[len-i-1];
  }
}
 

////////////////////////////////////////////////////////////////////////////


int main() {
  char flag = 'y';
  while(flag != 'n')
  {
    Money m1;
    m1.ldtoms();
    //m1.mstold();
    //m1.display();
    std::cout << "\nПродолжить?(y/n)" << std::endl;
    std::cin >> flag;
  }
 return 0;
}