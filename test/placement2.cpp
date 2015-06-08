#include <iostream>
using namespace std;
/** Reference http://www.sourcetricks.com/2008/05/c-placement-new.html#.VXMEV89VhBc */
class MyClass {
   int idx;
   int jdx;
   //float kdx;
   double ldx;
   public:

    // Placement new operator
    void* operator new (size_t sz, void* v) {
        cout << "Placement new invoked" << endl;
        return v;
    }

    ~MyClass() {
        // Cleanup
    }
};

int main()
{
    // Create a buffer to store the object
    int buffer[32];
    cout << "Starting address of my buffer = " << &buffer << endl;

    // Create the object. Use placement new
    MyClass* obj = new (buffer) MyClass();
    cout << "Location of my object = " << obj << endl;
	int* buffer1 = buffer + sizeof(MyClass);
	MyClass* obj1 = new (buffer1) MyClass();
    // Don't delete object created with placement delete
    // Call the destructor explicitly
    obj->~MyClass();
}