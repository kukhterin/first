#include <iostream>
using namespace std;

//cоздать класс time c int полями(час, мин, сек)
//c 2 конструкторами(инициализирующими поля 0 и заданными значениями
//в main создать 2 инициализированных объекта, сложить зничения полей
//результат присвоить 3 и вывести на экран

class Time{
private:
  int hours, min, sec;
public:
  Time(): hours(0),min(0),sec(0)
  {}
  Time(int h, int m, int s): hours(h),min(m),sec(s)
  {}
  void display()const
  {
    cout << hours << ":" << min << ":" << sec << endl;
    
  }
  void add(Time t1, Time t2)//сложение объектов time
  {
    
    sec = t1.sec + t2.sec;
    if(sec >= 60)
    {
      sec -= 60;
      min++;
    }
    min += t1.min + t2.min;
    if(min >= 60)
    { 
      min -= 60;
      hours++;
    }
    hours += t1.hours + t2.hours;
  }
  
};

int main()
{
    Time time1(10, 34, 50), time2(5, 45, 27), time3;
    time3.add(time1,time2);
    time3.display();
    
    return 0;
}

