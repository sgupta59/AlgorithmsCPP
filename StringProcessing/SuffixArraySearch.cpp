#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <algorithm>
using namespace std;

struct MySort {

	bool operator()(string& left, string& right)
	{
		bool cmp = left < right;
		int value =  left.compare(right);
		return value < 0;
	}
} ;

vector<string> createSuffixArrays(string text)
{
	vector<string> suffixArrays;
	for (int i = 0; i < text.size(); ++i)
		suffixArrays.push_back(text.substr(i));
	sort(suffixArrays.begin(), suffixArrays.end(), MySort());
	return suffixArrays;
}

void findSubstring(vector<string> suffixArray, string& substr, int& start, int& end)
{
	int lo = 0;
	int len = substr.size();
	int hi = suffixArray.size()-1;
	while (lo < hi)
	{
		int mid = lo + (hi-lo)/2;
		string midstr = suffixArray[mid];
		int cmp = substr.compare(0,len,suffixArray[mid], 0, len);
		if (substr.compare(0,len,suffixArray[mid], 0, len) <= 0)
		{
			hi = mid-1;
		}
		else
			lo = mid+1;
		
	}
	start = lo;
	lo = start;
	hi = suffixArray.size()-1;
	while (lo  < hi)
	{
		int mid = lo + (hi-lo)/2+1;
		string midstr = suffixArray[mid];
		if (suffixArray[mid].compare(0,len, substr, 0, len) >  0)
			hi = mid-1;
		else /** if (substr.compare(0,len, suffixArray[mid], 0, len) > 0) */
			lo=mid;
		
		
	}
	end = hi;
}
void main()
{
	string input = "acggtacgtac";
	int len = input.size();
	vector<string> suffixArray = createSuffixArrays(input);

	for (int i = 0; i < len; ++i)
		cout << "[" << i << "]" << suffixArray.at(i) << endl;
	int lo = 0;
	int hi = 0;
	string substr = "c";
	findSubstring(suffixArray,substr,lo, hi);
	for (int i = lo; i <= hi; ++i)
		cout << "-->: " << suffixArray[i] << endl;
}