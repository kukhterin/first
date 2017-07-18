#include <iostream>
// Написать программу, которая позволит пользователю вводить целые числа, затем сохранять их в массиве.
// Написать функцию, которая находит наибольший элемент 
//Функция должна принимать в качестве аргумента адрес массива и количество элементов, а выдавать индекс наибольшего элемента
//Программа должна вызвать эту функцию и вывести наибольший элемент и его индекс
int n = 0;
int main() {
 int getmax(int[]);
 const int MAX = 100;
 int intar[MAX];
 char confirm = 'q';
 while(confirm == 'q'){
 std::cout <<"Insert your number: " << std::endl;
 std::cin >> intar[n];
 n++;
 std::cout <<"Press 'q' to continue" << std::endl;
 std::cin >> confirm;
}
int x = getmax(intar);
std::cout << "Index of max element: " << x << ", Max element: " << intar[x];
    
}

int getmax(int arr[]) 
{
  int max = 0;
  int res = 0;
  for(int i = 0; i < n; i++)
  {
    if(arr[i] > max)
    {
      max = arr[i];
      res = i;
    }
  }
  return res;
}