#include <iostream>

//Написать класс saferray, использующий массив типа int фиксированной длины LIMIT, с двумя методами:
//putel() принимает индекс и значение типа int и вставляет значение по индексу, если индекс не меньше 0 и не больше LIMIT
//getel() принимает индекс как аргумент и возвращает значение типа int, содержащееся в элементе с этим индексом.
//
class SafeArray{
private:
  static const int LIMIT = 10;
  int arr[LIMIT];
public:
  void putel()
  {
    int index, val;
    std::cout << "\nДобавление элемента" << std::endl;
    std::cout << std::endl;
    std::cout << "\nВведите индекс элемента" << std::endl;
    std::cin >> index;
    if(index<0 || index > LIMIT-1) 
      {std::cout << "\nМассив ограничен " << LIMIT << " элементов!" <<std::endl;}
    else
    {
      std::cout << "\nВведите значение элемента" << std::endl;
      std::cin >> val;
      arr[index] = val;
    }
  }
    
  void getel()
  {
    int index;
    std::cout << "\nПолучение элемента по индексу" << std::endl;
    std::cout << std::endl;
    std::cout << "\nВведите индекс элемента" << std::endl;
    std::cin >> index;
    if(index >= 0 && index < LIMIT)
    {
      std::cout << "Значение элемента " << index << ": " << arr[index] << std::endl;
    }
    else
    {
      std::cout << "\nМассив ограничен " << LIMIT << " элементов!" <<std::endl;
}
  }
  
};
int main() {
  SafeArray s1;
  char flag = 'y';
  while(flag != 'n')
  {
    
    s1.putel();
    s1.getel();
    std::cout << "Продолжить?(y/n)";
    std::cin >> flag;
  }
    
    return 0;
}
