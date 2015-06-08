#include <iostream>
using namespace std; 
 
int main()
{
	char p[5];
   char q[]="Hello";
   int i=129;
   char* p1 = (char*)&i;
   if (p1[0] == 1)
	   printf("test");
   strcpy(p,"Hello");
   printf("strlen(p)=%d\n",strlen(p));
   printf("sizeof(p)=%d\n",sizeof(p));
   printf("strlen(q)=%d\n",strlen(q));
   printf("sizeof(q)=%d\n",sizeof(q));
	char* s1 = "abc def";
	char s2[] = "abc def";
	int len1 = strlen(s1);
	int len2 = strlen(s2);
	char s3[7];
	strcpy(s3,s1);
	len1 = strlen(s3);
	len2 = sizeof(s3);
	strcpy(s3,s2);
	len1 = strlen(s3);
	len2 = sizeof(s3);
	char  str[] = "abc def";
	int len = strlen(str);

}