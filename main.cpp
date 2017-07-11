#include <iostream>
using namespace std;

class Int {
  private:
    int n;
public:
  Int()
  {n = 0;}
  Int(int i)
  {n = i;}
  void intSum(Int i1, Int i2)
  {n = i1.n + i2.n;}
  void show()
  {cout << n << endl;}
  
};



int main() 
{
 Int i1(11), i2(9), i3;
 i1.show();
 i2.show();
 i3.intSum(i1,i2);
 i3.show();
 
 
  
return 0;

}