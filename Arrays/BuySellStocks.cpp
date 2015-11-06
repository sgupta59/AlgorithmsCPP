#include <iostream>
#include <algorithm>
#include <limits>

/** 
 * Brute force algorithm. O(N^2) 
 * n + n-1 + n-2 + n-3 + ... 1
 * n(n+1)/2
 */
int buy_sell_stock_1(int* a, int len)
{
	// check for 0 lengh array, null pointer etc or
	int maxprofit = 0;
	for (int i = 0; i < len; ++i)
	{
		for (int j = i; j < len; ++j)
		{
			maxprofit = std::max(maxprofit, a[j] - a[i]);
		}
	}
	return maxprofit;
}

/**
 * Linear solution
 * Max profit at i is max (profit(i-1), a[i] - min)
 * where prifit(i-1) is some max profit in array [0, i-1] 
 * min is the minimum price in the array i-1
 * you can write a recursion as max ( maxprofit, maxprofit(i-1, min))
 * if i == 1, return 0 as the terminating condition.
 */
int buy_sell_stock_2(int* a, int lo, int hi)
{
	int maxprofit = 0;
	int min = a[lo];
	for (int i = lo+1; i <= hi; ++i)
	{
		maxprofit = std::max(maxprofit, a[i] - min);
		if (a[i] < min)
			min = a[i];
	}
	return maxprofit;
    
}
// O(N^2) as for each i, there is an O(n) calculation for all n
int buy_sell_stock_twice_1(int* a, int len)
{
	int maxprofit = 0;
	for (int i = 0; i < len; ++i)
	{
		int max1 = buy_sell_stock_2(a, 0, i);
		int max2 = buy_sell_stock_2(a, i, len-1);
		maxprofit = std::max(maxprofit, max1+max2);
	}
	return maxprofit;
}

int buy_sell_stock_twice_2(int* a, int len)
{
	int maxprofit = 0;
	int* maxp1 = new int[len];
	int* maxp2 = new int[len];
	int min = a[0];
	maxp1[0] = 0;
	for (int i = 1; i < len; ++i)
	{
		maxp1[i] = std::max(maxp1[i-1], a[i] - min);
		min = std::min(min, a[i]);
	}
	maxp2[len-1] = 0;
	int max = a[len-1];
	for (int j = len-2; j >= 0; --j)
	{
		maxp2[j] = std::max(maxp2[j+1], max-a[j]);
		max = std::max(max, a[j]);
	}
	for (int i = 0; i < len; ++i)
	{
		maxprofit = std::max(maxprofit, maxp1[i] + maxp2[i]);
	}
	delete [] maxp1;
	delete [] maxp2;
	return maxprofit;
}
int main()
{
	int a[] = {2, 7, 1, 8, 2, 8, 4, 5, 9, 0, 4, 5};
	int len = sizeof(a)/sizeof(int);
	int profit1 = buy_sell_stock_1(a, len);
	int profit2 = buy_sell_stock_2(a, 0, len-1);
	int price[] = {10, 22, 5, 75, 65, 80};
	len = sizeof(price)/sizeof(int);
	int profit3 = buy_sell_stock_twice_1(price, len);
	int profit4 = buy_sell_stock_twice_2(price, len);
	return 0;
}