#include <stdlib.h>
#include <stdio.h>
#include <string.h>
void remove_all_spaces(char* str)
{
	char* current = str;
	while (*str != '\0') 
	{
		if (*str == ' ')
		{
			++str;
			continue;
		}
		*current++ = *str++;
	}
	*current = *str;
}

void remove_multiple_spaces(char* str)
{
	char* out = str;
	while (*str != '\0') 
	{
		while (*out == ' ' && *(str+1) == ' ')
			++str;
		*out++ = *str++;
	}
	*out='\0';
}

int strlen_l(char* str)
{
	int count = 0;
	while ((*str++))
		++count;
	return count;
}
int main()
{
	char* str = " ab  c  d ";
	int len1 = strlen(str);
	int len2 = strlen_l(str);
	char* str1 = (char*)malloc(strlen(str)+1);
	memcpy(str1, str, strlen(str)+1);

	remove_multiple_spaces(str1);
	remove_all_spaces(str1);
	fprintf(stdout,"Test");
	return 0;
}