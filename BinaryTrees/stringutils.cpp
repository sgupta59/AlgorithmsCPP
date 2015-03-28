#include <stdio.h>
#include <stdlib.h>
#include <cstring>
void stringtypes()
{
	// array size is 6, 5 characters are added to it, 6th character is 0. after that the memory is junk.
	// 6th character is '0' is I think just because this is debug mode, can be anything
	char strarray[6] = "abcde";
	// by chance strlen gives 5 because 6th character is '0'
	int l1 = strlen(strarray);
	// array of 5 characters, after that memory is junk
	char strarray1[5] = { '1', '2', '3', '4', '5'};
	// strlen gives > 5 as there is no null terminating character unless by chance
	l1 = strlen(strarray1);
	// array is terminated by a null terminating character
	char* strarray2 = "abcde";
	// strlen gives 5 as the 6th character is null terminator.
	l1 = strlen(strarray2);
	// allocate an array and add one for null terminating character
	char* strarray3 = new char[l1+1];
	// set everything in array to be null
	memset(strarray3,'\0',l1+1);
	// copy 5 characters from strarray2 to strarray3
	memcpy(strarray3,strarray2,l1);
	// length of strarray will be 5 as 6the character is '\0'
	l1 = strlen(strarray3);
	printf("test");

}
const char* mystrstr(const char* s1, const char* s2)
{
	if (s1 == NULL || s2 == NULL)
		return NULL;
	int l1 = strlen(s1);
	int l2 = strlen(s2);
	int start = -1;
	int idx = 0; int jdx = 0;
	while (s1[idx] != '\0')
	{
		while (s2[jdx] != '\0')
		{
			if (s1[idx] == s2[jdx])
			{
				if (start == -1)
					start = idx;
				++idx;
				++jdx;
				continue;
			}
			start = -1;
			jdx=0;
			break;
		}
		++idx;
	}
	return start == -1 ? NULL : s1+start;
}
char *strstrImp(char *input, const char *find)
{
    do
    {
        const char *p, *q;
		p = input;q=find;
        for (p = input, q = find; *q != '\0' && *p == *q; p++, q++) 
		{
			printf("test");
		}
        if (*q == '\0')
        {
            return input;
        }
    } while (*(input++) != '\0');
    return NULL;
}
char* strstrImp1(char* input, const char* find)
{
	while (*input != '\0') 
	{
		const char* p,*q;
		for (p = input, q= find; *q != '\0' && *p == *q;++p,++q)
		{
		}
		if (*q=='\0')
			return input;
		++input;
	}
	return NULL;
}

void stringtests()
{
	const char* s1 = "abcde";
	const char* s2 = "cde";
	char* s4 = strstrImp1(const_cast<char*>(s1), s2);
	const char* s3 = mystrstr(s1, s2);
	stringtypes();
}