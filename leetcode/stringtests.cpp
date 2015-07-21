#include <iostream>
using namespace std; 
 
int main()
{
	char p[5];
   char q[]="Hello";
   char *r="Hello";
   int i=129;
   char* p1 = (char*)&i;
   if (p1[0] == 1)
	   printf("test");
   strcpy(p,"Hello");
   printf("strlen(p)=%d\n",strlen(p));
   printf("sizeof(p)=%d\n",sizeof(p));
   printf("strlen(q)=%d\n",strlen(q));
   printf("sizeof(q)=%d\n",sizeof(q));
     printf("strlen(r)=%d\n",strlen(r));
   printf("sizeof(r)=%d\n",sizeof(r));
   	char  str[] = "Hello";
	int len = strlen(str);
	printf("sizeof(str)=%d\n",sizeof(str));
	printf("strlen(str)=%d\n",strlen(str));
	char* s1 = "abc def";
	char s2[] = "abc def";
	int len1 = strlen(s1);
	int len2 = strlen(s2);
		printf("sizeof(s1)=%d\n",sizeof(s1));
	printf("strlen(s1)=%d\n",strlen(s1));
		printf("sizeof(s2)=%d\n",sizeof(s2));
	printf("strlen(s2)=%d\n",strlen(s2));
	char s3[7];
	char s4[7];
	strcpy(s3,s1);
	len1 = strlen(s3);
	len2 = sizeof(s3);
    printf("strlen(s3)=%d\n",strlen(s3));
    printf("sizeof(s3)=%d\n",sizeof(s3));
	strcpy(s4,s2);
	len1 = strlen(s3);
	len2 = sizeof(s3);
	printf("strlen(s4)=%d\n",strlen(s4));
    printf("sizeof(s4)=%d\n",sizeof(s4));

}