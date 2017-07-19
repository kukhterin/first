#include "Distance.hpp"
#include <iostream>


Distance::Distance(): feet(0), inches(0)
{};
Distance::Distance(int ft, float inch) : feet(ft), inches(inch)
{}  
void Distance::get_dist()
  {
    std::cout << "Insert feet: ";
    std::cin >> feet;
    std::cout << "Insert inches: ";
    std:: cin >> inches;
  }
void Distance::display() const
  {
    std::cout << feet << "'-" << inches << "\"" << std::endl; 
  }
Distance Distance::operator+(Distance d) const
{
  int ft = feet + d.feet;
  float inch =  inches + d.inches;
  if(inch >= 12)
   {
     inch -= 12;
     ft++;
  }
    return Distance(ft, inch);
} 
Distance Distance::operator-(Distance d) const
{
  int ft = 0;
  float inch =  (inches + feet * 12) - (d.inches + d.feet * 12);
  while(inch > 12)
  {
    inch -= 12;
    ft++;
  }
  return Distance(ft, inch);
}   

 