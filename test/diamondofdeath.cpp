#include <iostream>
using namespace std;
class Base {
public:
  // ...
protected:
  int data_;
};
class Der1 : public virtual Base {
                     
public:
  // ...
};
class Der2 : public virtual Base {
                     
public:
  // ...
};
class Join : public Der1, public Der2 {
public:
  void method()
  {
     data_ = 1;  // Good: this is now unambiguous
  }
};
int main()
{
  Join* j = new Join();
  Base* b = j;   // Good: this is now unambiguous
}