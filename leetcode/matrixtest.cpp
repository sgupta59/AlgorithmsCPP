#include <iostream>
using namespace std;
/** http://stackoverflow.com/questions/8767166/passing-a-2d-array-to-a-c-function*/

/**
* Pass by reference, dimensions have to be known at compile time
*/
template<size_t rows, size_t cols>
void process_2d_array_template(int (&array)[rows][cols])
{
     
    for (size_t i = 0; i < rows; ++i)
    {
        std::cout << i << ": ";
        for (size_t j = 0; j < cols; ++j)
            std::cout << array[i][j] << '\t';
        std::cout << std::endl;
    }
}

/**
* size has to be known at compile time
* call via process_2d_array_pointer(&array)
*/
void process_2d_array_pointer(int (*array)[5][10])
{
     
    for (size_t i = 0; i < 5; ++i)
    {
        std::cout << i << ": ";
        for (size_t j = 0; j < 10; ++j)
            std::cout << (*array)[i][j] << '\t';
        std::cout << std::endl;
    }    
}

/**
 * variable number of rows, fixed number of columns
 * array is a pointer to 10 integers. Only one array is known.
 */
void process_2d_array(int (*array)[10], size_t rows)
{
     
    for (size_t i = 0; i < rows; ++i)
    {
        std::cout << i << ": ";
        for (size_t j = 0; j < 10; ++j)
            std::cout << array[i][j] << '\t';
        std::cout << std::endl;
    }
}

// variable rows and columns 
void process_pointer_2_pointer(int **array, size_t rows, size_t cols)
{
     
    for (size_t i = 0; i < rows; ++i)
    {
        std::cout << i << ": ";
        for (size_t j = 0; j < cols; ++j)
            std::cout << array[i][j] << '\t';
        std::cout << std::endl;
    }
}
int main()
{
    int a[5][10] = { { } };
    process_2d_array_template(a);
    process_2d_array_pointer(&a);    // <-- notice the unusual usage of addressof (&) operator on an array
    process_2d_array(a, 5);
    // works since a's first dimension decays into a pointer thereby becoming int (*)[10]

    int *b[5];  // surrogate
    for (size_t i = 0; i < 5; ++i)
    {
        b[i] = a[i];
    }
    // another popular way to define b: here the 2D arrays dims may be non-const, runtime var
    // int **b = new int*[5];
    // for (size_t i = 0; i < 5; ++i) b[i] = new int[10];
    process_pointer_2_pointer(b, 5, 10);
    // process_2d_array(b, 5);
    // doesn't work since b's first dimension decays into a pointer thereby becoming int**
}

