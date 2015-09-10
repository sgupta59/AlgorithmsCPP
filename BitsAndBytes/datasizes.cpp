#include <iostream>
#include <string>
using namespace std;

/**
 * Complexity is O(n)
 */
void printBin(int n)
{
    string binstring;
    int k = 1;
    // do this till the number becomes 0.
    for (int i = 0; i < 8; ++i)
    {
        // check if the right most bit is 0 or 1 using a bit test, add it to a string or a stack.
        if ((n & k) == 0)
            binstring.insert(binstring.begin(),1,'0');
        else
            binstring.insert(binstring.begin(),1,'1');
        // right shift the number now and repeat the process.
        k <<= 1;
    }
    
    cout << binstring << endl;
}

/*
 * To count number of bits for an unsigned value
 * do an '&' of 1 with the number i.e. the right most bit. 
 * now right shift the number by 1
 * continue as long as the number is not 0
 */
int count1Bits_1(unsigned int n)
{
    int c = 0;
    while (n > 0) {
        if (n & 1)
            ++c;
        n >>= 1;
    }
    return c;
}

/**
 * Do Binary addition of 2 numbers 
 */
int binaryAdd(int a, int b)
{
    int carry = 0;
    // adding two numbers, 1 + 1 = 10, so
    while (b > 0) {
        // first calculate the carry
        carry = a & b;
        // do a half add
        a = a ^ b;

        b = carry << 1;
    }

    return a;
}

bool isPalindrome(int a)
{
    // get the size of the int, assume 32 bit integer. Here I am doing only 8 bits
    // left bit is 0, right bit is 7
    int l = 0;
    int r = 7;
    while (l < r) {
        // check if left bit is set or not
        bool lset = a & (1 << l);
        // check if the right most bit is set or not.
        bool rset = a & (1 << r);
        // if the two do not match then this is not a palindrome
        if ( lset != rset)
            return false;
        ++l;
        --r;
    }
    return true;
}
void main()
{
    isPalindrome(-102);
    binaryAdd(5,6);
    count1Bits_1(5);
    printBin(-5);
}