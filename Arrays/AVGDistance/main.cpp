#include <iostream>

//Написать программу, вычисляющкю среднее значение до 100 интервалов (в английской системе измерения), введённых пользователем

class Distance{
private:
  int feet;
  float inches;
public:
  Distance(): feet(0), inches(0)
  {}
  void get_dist()
  {
    std::cout << "Insert feet: ";
    std::cin >> feet;
    std::cout << "Insert inches: ";
    std:: cin >> inches;
  }
  void add_dist(Distance d) {
    inches += d.inches;
    if(inches >= 12)
    {
      inches -= 12;
      feet ++;
    }
    feet += d.feet;
  } 
  void display()
  {
    std::cout << feet <<"'-" << inches << "\"" << std::endl; 
  }
  void div_dist(int n)
  {
    inches = (inches + feet * 12) / n;
    feet = inches/12;
    inches = inches - feet * 12;
    
  }
};

int main() {
  const int MAX = 100;
  Distance d_array[MAX];
  int n = 0;
  char confirm = 'y';
  Distance result;
    
  for(int i = n; i < MAX && confirm!='n'; i++)
   {
     std::cout << "Insert Distans " << n <<std::endl;
     d_array[i].get_dist();
     n++;
     result.add_dist(d_array[i]);
     std::cout <<"Continue(y/n)?";
     std::cin >> confirm;
   }
  result.div_dist(n);
  std::cout <<"Average Distance = ";
  result.display();
}