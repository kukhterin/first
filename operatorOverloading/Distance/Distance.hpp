#ifndef _DISTANCE_HPP_
#define _DISTANCE_HPP_
class Distance{
private:
  int feet;
  float inches;
public:
  Distance();
  Distance(int, float);
  void get_dist();
  void display() const;
  Distance operator+(Distance) const;
  Distance operator-(Distance) const;
};

#endif