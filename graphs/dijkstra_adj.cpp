#include <iostream>
#include <limits>
using namespace std;
#define V 9
int sol[V] = {0, 4, 12, 19, 21, 11, 9, 8, 14};
int findMin(int* d, bool* visited)
{
	int min = 0;
	int dist = INT_MAX;
	for (int i = 1; i < V; ++i)
	{
		if (!visited[i] && d[i] < dist)
		{
			dist = d[i];
			min = i;
		}
	}
	return min;
}
void dikkstra_adjmatrix(int g [V][V], int s)
{
	// create a distrance array
	int* d = new int[V];
	bool* visited = new bool[V];

	for (int i = 0; i < V; ++i)
	{
		d[i] = INT_MAX;
		visited[i] = false;
	}
	d[s] = 0;

	// complexity is O(V^2 + E) times 
	// Executed V times
	for (int i = 0; i < V; ++i)                  
	{
		// Executed V times
		int u = findMin(d, visited);            
		visited[u] = true;
		// executed adj(u) times for each v, 
		// this sums to E times execution for all executions of V
		// E = adj(v1) + adj(v2) + adj(v3) ... 
		for (int v = 0; v < V; ++v)             
		{
			int min = INT_MAX;
			if (!visited[v] && g[u][v] != 0 && d[v] > d[u] + g[u][v])
			{
				d[v] = d[u] + g[u][v];
			}
		}
	}
	for (int i = 0; i < V; ++i)
	{
		if (d[i] != sol[i])
		{
			cout << "Fail" << endl;
		}
	}
	std::cout << "pass" << endl;
	delete [] d;
	delete [] visited;
}
int main()
{
   /* Let us create the example graph discussed above */
   int graph[V][V] = {{0, 4, 0, 0, 0, 0, 0, 8, 0},
                      {4, 0, 8, 0, 0, 0, 0, 11, 0},
                      {0, 8, 0, 7, 0, 4, 0, 0, 2},
                      {0, 0, 7, 0, 9, 14, 0, 0, 0},
                      {0, 0, 0, 9, 0, 10, 0, 0, 0},
                      {0, 0, 4, 0, 10, 0, 2, 0, 0},
                      {0, 0, 0, 14, 0, 2, 0, 1, 6},
                      {8, 11, 0, 0, 0, 0, 1, 0, 7},
                      {0, 0, 2, 0, 0, 0, 6, 7, 0}
                     };
 
    dikkstra_adjmatrix(graph, 0);
 
    return 0;
}