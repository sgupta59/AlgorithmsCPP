#include <iostream>
#include <vector>
using namespace std;
	
vector<int> price;
vector<int> weight;
vector<int> included;
vector<int> best;
int W = 16;

bool is_solution(int idx)
{
	return idx == price.size();
}

void knapsack_bruteforce(int idx, int cp, int cw, int& opt)
{
	// if this is a solution, then return, i.e. can not go beyond this.
	// this is the last item in the array.
	if (is_solution(idx))
		return;
	// adding this item goes beyond the limit, 
	if (cw + weight[idx] > W)
		return;
	// if weight limit is reached, update the optimal profit if this item were selected
	if (cw + weight[idx] == W)
	{
		if (cp + price[idx] > opt)
		{
			opt = cp + price[idx];
			// update the best vector and mark it as included.
			included[idx] = 1;
			best = included;
		}
		return;
	}
	
	// if adding the current node gives an optimal solution, 
	if (cp + price[idx] > opt)
	{
		// update optimal solution.
		opt = cp + price[idx];
		// mark this node as included, this is done again at the recursive call but we do it here for completeness.
		included[idx] = 1;
		// copy the best solution so far
		best = included;
	}
	// include this item
	included[idx] = 1;
	knapsack_bruteforce(idx+1, cp+price[idx], cw+weight[idx], opt);
	// do not include this item.
	included[idx] = 0;
	knapsack_bruteforce(idx+1, cp, cw, opt);
}
void knapsack_bruteforce_test()
{

	W = 16;
	// NOTE: price[0] and weight[0] are starting nodes, and added as sentinals.
	int i_price[] = { 0, 40, 30, 50, 10 };
	int i_weight[] = { 0, 2, 5, 10, 5 };
	for (int i = 0; i < sizeof(i_price)/sizeof(int); ++i)
	{
		price.push_back(i_price[i]);
		weight.push_back(i_weight[i]);
		included.push_back(0);
		best.push_back(0);
	}

	
	// opt is the optimal price for a weight of 16 or less.
	int opt = -1; 
	knapsack_bruteforce(1, 0, 0, opt);
	cout << "Max Profit " << opt << endl;
	cout << "Items Included: ";
	for (int i = 0; i < best.size(); ++i)
	{
		if (best[i] > 0) cout << weight[i] << " " ;
	}
	cout << endl;
}
void main()
{
	knapsack_bruteforce_test();
}