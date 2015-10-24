#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <queue>
#include <set>
using namespace std;

#define V 9
#define INF INT_MAX

/**
 * Find the vertex with minimum distance that has not been visited so far
 */
int find_min(vector<int>& d, vector<bool>& visited)
{
	int id = 0;
	// let the current minimum distance be infinity
	int min = INF;
	for (int i = 0; i < d.size(); ++i)
	{
		// if current vertex is at distance less than min, 
		if (d[i] < min && !visited[i]) {
			min = d[i];
			id = i;
		}
	}
	return id;
}
/**
 * adjacency matrix solution for dijkstra.
 *
 * Dijkstra's algorithm is a shortest path algorithm for weighted/unweighted directed/undirected graphs with no negative weights.
 *
 */
vector<int> dijkstra_adjmatrix(int g[V][V], int s)
{
	// Create a distance array to hold distances of each vertex from the sauce.
	vector<int> d(V);
	// Each vertex is processed only once, so create an array to hold a flag to indicate the vertex is processed.
	vector<bool> visited(V);
	vector<int> test;
	// This is O(V) 
	for (int i = 0; i < V; ++i)
	{
		d[i] = INF;
		visited[i] = false;
	}
	
	// mark the source vertex with a distanc of 0, i.e. it is 0 distance away from the source.
	d[s] = 0;

	/**
	 * The complexity will be O(V^2 + E) as all edges are processed once, and min is found V times. 
	 */

	// process each vertex once, i.e. for each vertex i.e. V times, i.e. O(V)
	for (int i = 0; i < V; ++i)
	{
		// find the smallest distance vertex this is O(V) for each i --> O(V^2) at this point.
		int u = find_min(d,visited);
		// mark this vertex as visited
		visited[u] = true;
		// for each adjacent vertex of this vertex, i..e for each edge --> O(E) cummulative.
		for (int v = 0; v < V; ++v)
		{
			// if there is an edge, and the vertex v is not visited i.e edge is not visited and there needs to be a 
			// relaxation.
			if (g[u][v] != 0 && !visited[v] && d[v] > d[u] + g[u][v]) {
				d[v] = d[u] + g[u][v];
			}
		}
	}
	// at this point d vector has the distance from source vertex s to all other vertices.
	return d;
}

bool isEquals(const int& a, const int& b)
{
	return a == b;
}
void dijkstra_adjmatrix_test()
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
 
    vector<int> d = dijkstra_adjmatrix(graph, 0);
	const int sol[V] = {0, 4, 12, 19, 21, 11, 9, 8, 14 };
	/**
	 * Pass a predicate isEquals 
	 */
	std::pair<const int* , vector<int>::iterator > mismatch1 =  std::mismatch(sol, sol+V, d.begin(),isEquals);
	cout << ( mismatch1.second == d.end() ? " PASS " : " FAIL " ) << endl;

}

class MinPQCompare     {
	private:
		vector<int>& md;
	public:
	MinPQCompare(vector<int>& d1):md(d1) 
	{

	}
	MinPQCompare(const MinPQCompare& other) 
		:md(other.md)
	{

	}
	bool operator()(int& a, int& b)
	{
		return md[a] > md[b];
	}
};

/**
 * Priority queue based implementation. There is extra processing error as the same vertex is added back
 * to the priority queue and it will accpt it, e.g. if you put a breakpiont for v = 8, there are > 1 8's
 * items are not unique
 */
vector<int> dijkstra_priority_queue(int g[V][V], int s)
{
	// create a distance array one for each vertex
	vector<int> d;
	for (int i = 0; i < V; ++i)
		d.push_back(INF);
	d[s] = 0;
	// create a priority queue which has the vertex in it, add a comparator.
	MinPQCompare mpq(d);
	priority_queue<int, vector<int> , MinPQCompare > pq(mpq);

	// add the source vertex to the priority queue
	pq.push(s);
	// while pq is not empty --> Executed V times each time logV
	// Total = VlogV + E logV
	// VlogV --> V vertices are added to the queue.
	// ElogV --> E edges have update operation as the key is reduced.
	while (!pq.empty()) {
		// get the min item
		int u = pq.top();
		pq.pop();
		// get all adjacent edges of this priority queue.
		// This is "slightly" retarded, go to through all adj vertices and 
		// really this is going through all E edges and each time it takes logV 
		// so at this point this becomes ElogV
		for (int v = 0; v < V; ++v) {
			if (g[u][v] != 0 && d[v] > d[u] + g[u][v]) 
			{
				d[v] = d[u] + g[u][v];
				// Each push takes logV times. Cummulatively this is done ElogV times
				pq.push(v);
			}
		}
	}
	return d;
}
class MySetComparator {
private :
	 const vector<int>& m_d;
public:
	MySetComparator(const vector<int>& d) : m_d(d) {}
	bool operator()(const int& a, const int& b) 
	{
		return a < b;
	}
};
vector<int> dijkstra_set(int g[V][V], int s)
{
	// create a distance vector
	vector<int> d(V);
	// set all distances O(V)
	for (int i = 0; i < d.size(); ++i)
		d[i] = INF;
	d[s] = 0;
	// create a set 
	MySetComparator mycomp(d);
	set<int, MySetComparator> pq (mycomp);
	pq.insert(s);
	/// Result:
	/// 1 + 2 = VlogV + ElogV = (V+E)logV ~= ElogV for dense graphs
	// Done for all vertices in the queue
	// 1. Remove a vertex from the queue ... pq.erase... --> vLogv times 
	while (pq.size() > 0) {
		set<int, MySetComparator>::iterator iter = pq.begin();
		int u = *iter;
		pq.erase(iter);
		/// 2. cummulatively this is all edges if adjacency list is used, then it become Elogv
		// 
		for (int v = 0; v < V; ++v) {
			if (g[u][v] != 0 && d[v] > d[u] + g[u][v]) {
				if (pq.find(v) != pq.end()) {
					pq.erase(pq.find(v));
				}
				d[v] = d[u] + g[u][v];
				pq.insert(v);
			}
		}
	}
	return d;
}
void dijkstra_set_test()
{
	 int g[V][V] = {{0, 4, 0, 0, 0, 0, 0, 8, 0},
                      {4, 0, 8, 0, 0, 0, 0, 11, 0},
                      {0, 8, 0, 7, 0, 4, 0, 0, 2},
                      {0, 0, 7, 0, 9, 14, 0, 0, 0},
                      {0, 0, 0, 9, 0, 10, 0, 0, 0},
                      {0, 0, 4, 0, 10, 0, 2, 0, 0},
                      {0, 0, 0, 14, 0, 2, 0, 1, 6},
                      {8, 11, 0, 0, 0, 0, 1, 0, 7},
                      {0, 0, 2, 0, 0, 0, 6, 7, 0}
                     };
	 vector<int> d = dijkstra_set(g, 0);
	  int sol[V] = {0, 4, 12, 19, 21, 11, 9, 8, 14 };
	 pair<vector<int>::iterator,  int*> match = std::mismatch(d.begin(),d.end(),sol);
	 if (match.first == d.end())
		 cout << "PASS" << endl;
	 else
		 cout << "FAIL" << endl;
	 return;
}
 void dijkstra_pq_test()
{
	 int g[V][V] = {{0, 4, 0, 0, 0, 0, 0, 8, 0},
                      {4, 0, 8, 0, 0, 0, 0, 11, 0},
                      {0, 8, 0, 7, 0, 4, 0, 0, 2},
                      {0, 0, 7, 0, 9, 14, 0, 0, 0},
                      {0, 0, 0, 9, 0, 10, 0, 0, 0},
                      {0, 0, 4, 0, 10, 0, 2, 0, 0},
                      {0, 0, 0, 14, 0, 2, 0, 1, 6},
                      {8, 11, 0, 0, 0, 0, 1, 0, 7},
                      {0, 0, 2, 0, 0, 0, 6, 7, 0}
                     };
	 vector<int> d = dijkstra_priority_queue(g, 0);
	  int sol[V] = {0, 4, 12, 19, 21, 11, 9, 8, 14 };
	 pair<vector<int>::iterator,  int*> match = std::mismatch(d.begin(),d.end(),sol);
	 if (match.first == d.end())
		 cout << "PASS" << endl;
	 else
		 cout << "FAIL" << endl;
	 return;
}
int main()
{
	dijkstra_set_test();
	dijkstra_pq_test();
	dijkstra_adjmatrix_test();
    return 0;
}