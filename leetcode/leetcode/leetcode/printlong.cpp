#include <iostream>
using namespace std;

void printLong(unsigned long n)
{
	if (n < 10)
	{
		putchar(n + '0');
		return;
	}
	printLong(n/10);
	putchar(n%10+'0');
}
int main1()
{
	unsigned long n = 4294967295l ;
	printLong(n);
	return 0;
}