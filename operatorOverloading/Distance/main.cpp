#include "Distance.hpp"
#include <iostream>


//Добавить в класс Distance перегруженную операцию -, которая вычисляет разность двух интервалов (dist3 = dist1-dist2)
//предполагается. что операция не будет использоваться для вычитания большего интервала из меньшего.

int main() {
  Distance d1(5, 12), d2(3,6);
  Distance d3 = d1 - d2;
  d3.display();
  
  return 0; 
}


