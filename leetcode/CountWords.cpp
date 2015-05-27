#include <iostream>
using namespace std;
/**
 * count state transitions from space to not space.
 * set state to "space" if going from not space to space
 * set state to "not space" if going from space to not space or from not space to not space.
 */
int countwords(char* str)
{
	int count = 0;
	bool space = true;
	for (int i = 0; i < strlen(str); ++i)
	{
		if (space && str[i] != ' ')
		{
			++count;
			space = false;
		}
		if (!space && str[i] == ' ')
			space = true;
	}
	return count;
}
int main()
{	
	char  str[] = " abc  def g";
	int n = countwords(str);
	cout << n << endl;
}