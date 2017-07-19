#include <iostream>
#include "Distance.hpp"

Distance::Distance(): feet(0), inches(0)
{}
Distance(int ft, int inch) : feet(ft), inches(inch)
{}  
void Distance::get_dist()
  {
    std::cout << "Insert feet: ";
    std::cin >> feet;
    std::cout << "Insert inches: ";
    std:: cin >> inches;
  }
Distance Distance::operator+(Distance d) const
{
  int ft = feet + d.feet;
  float inch =  inches + d.inches;
  if(inch>= 12)
   {
     inch -= 12;
     ft++;
  }
    return Distance(ft, inch);
} 
Distance Distance::operator-(Distance d) const
{
  int ft = 0;
  float inch =  (inches + feet*12) - (d.inches + d.feet * 12);
  while(inch > 12)
  {
    inch-=12;
    ft++;
  }
  return Distance(ft, inch);
}   
void Distance::display()
  {
    std::cout << feet <<"'-" << inches << "\"" << std::endl; 
  }
 