#include <iostream>
using namespace std;
void removeSpaces(char* str)
{
	char* s1 = str;
	char* s2 = str;
	int i = 0, j = 0;
	for (i = 0; i < strlen(str); ++i)
	{
		if (str[i] == ' ')
			continue;
		s1[j++] = str[i];
	}
	/*while (s1[i] != '\0')
	{
		if (s1[i] != ' ')
			s2[j++] = s1[i];
		++i;
	}*/
	s2[j] = '\0';
}
int main()
{	
	char  str[] = "abc def";
	removeSpaces(str);
	cout << str << endl;
}