#include <iostream>
#include <set>
#include <string>
#include <functional>
#include <queue>
//https://www.topcoder.com/community/data-science/data-science-tutorials/power-up-c-with-the-standard-template-library-part-2/#dijkstra2
using namespace std;
#define V 9
int sol[V] = {0, 4, 12, 19, 21, 11, 9, 8, 14};
int dist[V] ;
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

 
struct ltDist { 
	bool operator()( int u, int v ) const { 
		//return make_pair( dist[u], u ) < make_pair( dist[v], v );
		return dist[u] < dist[v];
	} 
};
void dijkstra( int s ) {
	for( int i = 0; i < V; i++ ) dist[i] = INT_MAX;
	dist[s] = 0;
	set< int, ltDist > q;
	priority_queue<int, vector<int> , ltDist> pq1(s);
	q.insert( s );
	while( !q.empty() ) {
		int u = *q.begin(); // like u = q.front()
		q.erase( q.begin() ); // like q.pop()
		for( int v = 0; v < V; v++ ) 
			if( graph[u][v] != 0 ) {
			int newDist = dist[u] + graph[u][v];
			if( newDist < dist[v] ) // relaxation
			{
				if( q.count( v ) ) q.erase( v );
				dist[v] = newDist;
				q.insert( v );
			}
		}
	}
}
int main()
{
   /* Let us create the example graph discussed above */
   
 
    dijkstra(0);
 
    return 0;
}