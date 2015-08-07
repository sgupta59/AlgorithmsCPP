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

char *strcat_l(char *  s1, const char *  s2)
{
    char* orig = s1;
    if (s1 == NULL || s2 == NULL)
        return s1;
    while (*s1 != '\0')
        ++s1;
    while ((*s1++ = *s2++) != '\0');
  
    return orig;
}

void strcat_test()
{
    char* s2 = "abcde";
    char* s1 = new char[strlen(s2)+1];
    *s1 = '\0';
    s1 = strcat_l(s1,s2);
}

int strcmp_l(char* s1, char* s2)
{
    unsigned char c1;
    unsigned char c2;
    while (*s1 != '\0' && *s1 == *s2)
    {
        ++s1;
        ++s2;
    }
    c1 = *((unsigned char*)s1);
    c2 = *((unsigned char*)s2);

    return ((c1 < c2) ? -1 : (c1 > c2));
}

int strlen_l(char* s)
{
    char* p = s;
    while (*p != '\0')
        ++p;
    return p-s;
}
char *strncat_l(char *s1, const char *s2, size_t n)
{
    char* p = s1;
    while (*p != '\0')
        ++p;
    while (n-- > 0 && (*p++ = *s2++) != '\0');
    if (*p != '\0')
        *p = '\0';
    return s1;
}

void strncat_test()
{
    char* s2 = "abcde";
    char* s1 = new char[strlen(s2)+1];
    s1[0] = 'a';
    s1[1] = '\0';
 
    s1 = strncat_l(s1,s2,3);
    printf("%s",s1);
}
void *(memmove_l)(void *s1, const void *s2, size_t n) 
 {
    /* note: these don't have to point to unsigned chars */
    char *p1 = (char*) s1;
    const char *p2 = (char*) s2;
    /* test for overlap that prevents an ascending copy */
    if (p2 < p1 && p1 < p2 + n) {
        /* do a descending copy */
        p2 += n;
        p1 += n;
        while (n-- != 0) 
            *--p1 = *--p2;
    } else 
        while (n-- != 0) 
            *p1++ = *p2++;
    return s1; 
 }

int memcmp_l(void* s1, void* s2, size_t n)
{
    unsigned char* us1 = (unsigned char*)s1;
    unsigned char* us2 = (unsigned char*)s2;
    while (n-- > 0) {
        if (*us1 != *us2) {
            return (*us1 < *us2 ? -1 : 1);
        }
        ++us1;
        ++us2;
    }
    return 0;
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
    int length1b = strlen_l(str1);
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
    
    char str2[] = "memmove can be very useful......";
    //             --------------------^ insert here
    //             ---------------^ from here
    memmove_l (str2+20,str2+15,11);
    char str3[] = "abcdefghijkl12345678";
    memmove_l (str3+9,str3+5,7);
    strncat_test();
    stringLengthTests();
    strcat_test();
	test_strstr();
	memset_test();
	
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