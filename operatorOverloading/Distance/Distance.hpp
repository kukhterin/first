class Distance{
private:
  int feet;
  float inches;
public:
  Distance()
  {}
  Distance(int, int)
  {}
  void get_dist();
  Distance operator+(Distance) const;
  Distance operator-(Distance) const;
  void display();
};