#include "test.hpp"
int main() {
  test(" ", " ");
  test("a", "a");
  test("ab", "ba");
  test("abc", "cba");
  test("detartrated", "detartrated");
       
    return 0;
}