#include <iostream>
#include <cassert>
using namespace std;

int f(int x) 
{ 
	return (x*x - 10*x - 20); 
}
int findMissing(int* arr, int len)
{   
        int lowNum = arr[0];
        int low = 0;
        int high = len -1;
        int middle = (low + high)/2;
        while(low <= high){
            middle = (low + high)/2;
            if(arr[middle] == (middle+1 + lowNum) && middle-1 >=0 && arr[middle-1] == (middle + lowNum-1)){
                return middle + lowNum;
            }
            else if((middle + lowNum) == arr[middle]){
                low = middle+1;
            }else {
                high = middle-1;
            }
        }
        return -1;
}
int binarySearch(int lo, int hi)
{
	
	while (lo <= hi) {
		int mid = lo + (hi-lo)/2;
		int val = f(mid);
		if (val > 0 && (lo == hi || f(mid-1) < 0))
			return mid;
		if (val <= 0)
			return binarySearch(mid+1, hi);
		return binarySearch(lo,mid-1);
	}
	return -1;
}
int findFirstPositive()
{

	if (f(0) > 0)
		return 0;

	int num = 1;
	while (f(num) < 0) {
		num <<= 1;
	}

	int lo = num >> 1;
	int hi = num;
	return binarySearch(lo, hi);
}
void main()
{
	 int arr[] = {3,4,5,6,7,8,9,10,11,13};
	 findMissing(arr,sizeof(arr)/sizeof(arr[0]));
	int pos = findFirstPositive();
	assert(pos == 12);
	cout << "First Positive is: " << pos << endl;
}