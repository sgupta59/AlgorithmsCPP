#include <stdio.h>
#include <stdlib.h>
#include <stack>
using namespace std;
//
//

#define ARRAYSIZE(a) (sizeof(a))/(sizeof(a[0]))
 
static int total_nodes;
int include[5] = {0,0,0,0,0};
int w[5] = {0,3,5,6,7};
int W = 15;
int total = 21;
int weight = 0;
// prints subset found
void printSubset(int A[], int size)
{
    for(int i = 0; i < size; i++)
    {
        printf("%*d", 5, A[i]);
    }
 
    printf("\n");
}
 
// inputs
// s            - set vector
// t            - tuplet vector
// s_size       - set size
// t_size       - tuplet size so far
// sum          - sum so far
// ite          - nodes count
// target_sum   - sum to be found
void subset_sum(int s[], int t[],
                int s_size, int t_size,
                int sum, int ite,
                int const target_sum,stack<int> q)
{
    total_nodes++;
    if( target_sum == sum )
    {
        // We found subset
        printSubset(t, t_size);
        // Exclude previously added item and consider next candidate
        //subset_sum(s, t, s_size, t_size-1, sum - s[ite], ite + 1, target_sum);
        return;
    }
    else
    {
        // generate nodes along the breadth
        for( int i = ite; i < s_size; i++ )
        {
            t[t_size] = s[i];
			q.push(s[i]);
            // consider next level node (along depth)
			// NOTE: If sum + s[i] > target_sum, there is no need to dig in deeper.
            subset_sum(s, t, s_size, t_size + 1, sum + s[i], i + 1, target_sum,q);
			q.pop();
        }
    }
}
 
// Wrapper to print subsets that sum to target_sum
// input is weights vector and target_sum
void generateSubsets(int s[], int size, int target_sum,stack<int> q)
{
    int *tuplet_vector = (int *)malloc(size * sizeof(int));
 
    subset_sum(s, tuplet_vector, size, 0, 0, 0, target_sum,q);
 
    free(tuplet_vector);
}
// Here the recursion tree is as follows e.g.  5 6 10 11
//     level 0 (no items)
//     Refer to notes for the recursion tree. or in Foundations of algorithms 5.4
void generateSubsets_method2(int s[], int size, int current, int sum, stack<int> values)
{
	if (current > size)
		return;
	if (sum == 0)
	{
		// print stack.
		while (values.empty() == false)
		{
			fprintf (stdout, " %d " , values.top());
			values.pop();
		}
		fprintf(stdout, "\n");
		return;
	}
	if (sum < 0)
		return;
	values.push(s[current]);
	generateSubsets_method2(s, size, current+1,sum-s[current],values);
	values.pop();
	generateSubsets_method2(s,size,current+1,sum,values);
}
int isPromising(int idx)
{
	return (weight + total >= W ) && (weight == W || weight + w[idx+1] <= W);
}
void generateSubsets_method3(int idx, int weight, int total)
{
	if (isPromising(idx) == 1)
	{
		if (weight == W)
		{
			fprintf(stdout,"");
		}
		else
		{
			include[idx+1] = 1;
			generateSubsets_method3(idx+1,weight+w[idx+1],total-w[idx+1]);
			include[idx+1] = 0;
			generateSubsets_method3(idx+1,weight,total);
		}
	}
}
int main()
{
    //int weights[] = {10, 7, 5, 18, 12, 20, 15};
    //int size = ARRAYSIZE(weights);
	//int final = 35;
	generateSubsets_method3(0,0,total);
	stack<int> intq;
    int weights[] = {5,6,10,11,16};
    int size = ARRAYSIZE(weights);
	int final = 21;
    generateSubsets(weights, size, final,intq);
    printf("Nodes generated %d\n", total_nodes);
	stack<int> stk;
	generateSubsets_method2(weights,size,0,final,stk);
    return 0;
}