// A Dynamic Programming solution for subset sum problem
#include <stdio.h>
#include <cstring>
#include <string>
// Returns true if there is a subset of set[] with sun equal to given sum
bool isSubsetSum(int set[], int n, int sum)
{
    // The value of subset[i][j] will be true if there is a subset of set[0..j-1]
    //  with sum equal to i
    bool subset[7][10];
  
    // If sum is 0, then answer is true
    for (int i = 0; i <= n; i++)
      subset[0][i] = true;
 
    // If sum is not 0 and set is empty, then answer is false
    for (int i = 1; i <= sum; i++)
      subset[i][0] = false;
 
     // Fill the subset table in botton up manner
     for (int i = 1; i <= sum; i++)
     {
       for (int j = 1; j <= n; j++)
       {
         subset[i][j] = subset[i][j-1];
         if (i >= set[j-1])
           subset[i][j] = subset[i][j] || subset[i - set[j-1]][j-1];
       }
     }
 
     // uncomment this code to print table
     for (int i = 0; i <= sum; i++)
     {
       for (int j = 0; j <= n; j++)
          printf ("%4d", subset[i][j]);
       printf("\n");
     } 
 
     return subset[sum][n];
}
 void teststr()
 {
	 using namespace std;
	 char* str = " arrayof";
	 string mainstring(str);
	 int n = strlen(str);
	 for (int d = 1; d < n-1;++d)
	 {
		 string string1(str,1,(n-d)+1);
		 printf("%s \n", string1.c_str());
		 for (int i = 1; i < n-d; ++i)
		 {
			  
			 int j = i + d;
			 //string string1(str,i,(j-i)+1);
			 //printf("%s \n", string1.c_str());
			 for (int k = i+1; k < j-1; ++k)
			 {
				 string left(str,i,(k-i));
				 string right(str,k,j-k+1);
				 //printf("%s %s %s\n", string1.c_str(), (const char*)left.c_str(), (const char*) right.c_str());
			 }
		 }
		 //printf("=============d:%d, (n-d):%d========\n", d, (n-d));
	 }
	 return;
 }
// Driver program to test above function
int main()
{
	teststr();
  int set[] = {3, 34, 4, 12, 5, 2};
  int sum = 9;
  int n = sizeof(set)/sizeof(set[0]);
  if (isSubsetSum(set, n, sum) == true)
     printf("Found a subset with given sum");
  else
     printf("No subset with given sum");
  return 0;
}