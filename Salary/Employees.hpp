namespace employees {
  
  #ifndef _EMPLOYEE_
  #define _EMPLOYEE_

  class Employee
  {
  public:
   virtual double salary() = 0;
  };
  #endif
  
  #ifndef _MANAGER_
  #define _MANAGER_

  class Manager : public Employee
  {
  public:
    double salary();
  };
  
  #endif

  ////////////////////////////////////////////////
  
  #ifndef _AGENT_
  #define _AGENT_

  class Agent : public Employee
  {
  private:
    double amount;
  public:
    Agent(double);
    double salary();
  };
  
  #endif

  ////////////////////////////////////////////////
  
  #ifndef _WORKER_
  #define _WORKER_

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