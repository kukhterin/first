#include <iostream>

class Queue{
private:
  enum {MAX = 4};
  int q[MAX];//очередь в виде массива
  int head;
  int tail;
public:
  Queue()
  {head = 0;
   tail = 0;
  }
  void put(int var)
  {
    q[tail++] = var;
  
  }
  void get()
  {
    if(head == tail)
    {
      std::cout << "Очередь пуста";
      return;
    }
    std::cout << q[head++] << std::endl;
    
  }
};

int main() {
    Queue q1;
    q1.put(1);
    q1.put(2);
    q1.put(3);
    q1.get();
    q1.get();
    q1.get();
    q1.get();
  
    return 0;
}
