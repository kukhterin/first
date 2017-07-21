namespace employees {
  
  #ifndef _EMPLOYEES_
  #define _EMPLOYEES_

  class Employee
  {
  public:
   virtual double salary() = 0;
  };
  

  class Manager : public Employee
  {
  public:
    double salary();
  };
  
  ////////////////////////////////////////////////
  
  class Agent : public Employee
  {
  private:
    double amount;
  public:
    Agent(double);
    double salary();
  };
  
  ////////////////////////////////////////////////

  class Worker : public Employee
  {
  private:
    double time;
  public:
    Worker(double);
    double salary();
  };
  
  #endif

  
}