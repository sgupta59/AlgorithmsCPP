#include <iostream>
#include <stdlib.h>
/**
 http://codereview.stackexchange.com/questions/10776/simplified-regular-expression-engine
 --> "real" regular expression, do this here
*/
bool isMatch(const char* str, const char* pattern)
{
	if (str[0] == '\0' && pattern[0] == '\0')
		return true;
	if (str[0] == '\0' && pattern[0] == '*')
		return isMatch(str, pattern+1);
	if (str[0] == '\0')
		return false;
	if (str[0] == pattern[0] || pattern[0] == '.')
		return isMatch(str+1,  pattern+1 );
	if (pattern[0] == '*')
	{
		return isMatch(str, pattern+1) || isMatch(str+1, pattern);
	}
	return false;
}
int main()
{
	printf("%d\n", isMatch("aa",".*"));
	printf("%d\n", isMatch("ab",".*c"));
	printf("%d\n", isMatch("aa","a*"));
	printf("%d\n", isMatch("aaa","aa"));
	printf("%d\n", isMatch("aa","*"));
	printf("%d\n", isMatch("ab","."));
	printf("%d\n", isMatch("aab","c*a*b"));
}