#include <stdlib.h>
#include <stdio.h>

int strlen(char* str)
{
	int len = 0;
	while (*str++ != '\0')
		++len;
	return len;
}
void main()
{
	char* str1 = "abc";
	int len = strlen(str1);
	fprintf(stdout,"Length is %d\n", len);
}