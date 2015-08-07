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

/**
 * Searches for the first occurance of a char 'c' in string str.
 * returns the occurance or a NULL pointer
 */
char* strstr_l(char* str, int c)
{
	while (*str != '\0' && *str != (char)c)
		++str;
	return (*str == (char)c ? str : NULL);
}
void test_strstr()
{
	char* str = "abcdefg";
	char* str1 = strstr_l(str,'d');
}
/**
 * memset takes the memory location pointed to by s, and replaces its contents with
 * an unsigned char version of c for n items
 */
void* memset_l(void *s, int c, size_t n)
{
	unsigned char* us = (unsigned char*)s;
	unsigned char uc = (unsigned char)c;
	while (n-- > 0) 
		*us++ = uc;
	return s;
}

void memset_test()
{
	char* str = "abcd";
	char* newstr = new char[strlen(str)+1];
	newstr = (char*)memset_l((void*)newstr,'2',strlen(str));
	return;
}
static void stringLengthTests()
{
	char* str1 = "abcde";
	char* str2 = "abcde";
	char str3[] = "abcde";
	char str4[6] = "abcd "; /** Can not be less than 6 as 0-4 store 'abcd ' and 5 is for null terminator */
	char str5[3] = {'a', 'b', 'c'};
	// strlen gives the number of characters up to the null terminator so here it is 5
	int length1 = strlen(str1);
	// sizeof of a pointer is 4 on 32 bit.
	int length1a = sizeof(str1);
	// same as str1 but the address is the same. this is a constrant string.
	int length2 = strlen(str2);
	int length2a = sizeof(str2);
	//  strlen of a character array is 5 not including null terminator, same as normal strlen
	int length3 = strlen(str3);
	// size of array includes the null terminator. this is the actual size of the array.
	int length3a = sizeof(str3);
	int length4 = strlen(str4);
	int length4a = sizeof(str4);
	int length5 = strlen(str5);
	int length5a = sizeof(str5);
	fprintf(stdout,"String length string literal:\n");
}
int main()
{
	test_strstr();
	memset_test();
	stringLengthTests();
	char* str = " ab  c  d ";
	int len1 = strlen(str);
	int len2 = strlen_l(str);
	char* str1 = (char*)malloc(strlen(str)+1);
	memcpy(str1, str, strlen(str)+1);
	memset_l((void *)str1, '2', strlen(str));
	remove_multiple_spaces(str1);
	remove_all_spaces(str1);
	fprintf(stdout,"Test");
	return 0;
}