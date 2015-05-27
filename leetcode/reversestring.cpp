#include <iostream>
using namespace std;

void printReverse(char* str)
{
	if (*str == '\0')
		return;
	printReverse(str+1);
	putchar(*str);
}
int main2()
{
	char* str = "abcde";
	printReverse(str);
	return 0;
}