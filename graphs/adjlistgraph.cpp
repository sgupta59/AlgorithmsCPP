#include <stdio.h>
#include <list>
#include <stack> 
using namespace std;
 
// Graph class represents a directed graph using adjacency list representation
class Graph
{
    int V;    // No. of vertices
    list<int> *adj;    // Pointer to an array containing adjacency lists
    void DFSUtil(int v, bool visited[],int *parent ) ; // A function used by DFS
	void BFSUtil(int v, bool visited[],int *parent ) ;
	void DFSUtil_Stack(int v, bool visited[],int *parent);
public:
    Graph(int V);   // Constructor
    void addEdge(int v, int w);   // function to add an edge to graph
    void DFS(int v);    // DFS traversal of the vertices reachable from v
	void BFS(int v);
};
 
Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];
}
 
void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w); // Add w to v’s list.
	adj[w].push_back(v);
}
 
void Graph::DFSUtil(int v, bool visited[],int *parent ) 
{
    // Mark the current node as visited and print it
    visited[v] = true;

    printf(" %d " , v+1);
 
    // Recur for all the vertices adjacent to this vertex
    list<int>::iterator i;
    for(i = adj[v].begin(); i != adj[v].end(); ++i)
        if(!visited[*i])
        {
			parent[*i]=v;
			DFSUtil(*i, visited,parent);
		}
}
 
void Graph::DFSUtil_Stack(int v1, bool* visited,int *parent)
{
	int* parentList = new int[V];

	stack<int> stk;
	stk.push(v1);
	parent[v1] = -2;
	int prevparent = v1;
	while (stk.empty()==false)
	{
		int u = stk.top();
		
		stk.pop();
		if (visited[u] == false)
		{
			//printf(" %d " , u+1);
			visited[u] = true;
			printf("Edge: %d -> %d\n", parent[u],u);
			parentList[u] = parent[u];
			list<int>::iterator iter;
			for (iter = adj[u].begin(); iter != adj[u].end(); ++iter)
			{
				int v = (*iter);
				stk.push(v);
				if (visited[v]==false)
					parent[v]=u;
			}
		}				
	}

	return;
}
void Graph::BFS(int v)
{
	bool *visited = new bool[V];
    for(int i = 0; i < V; i++)
        visited[i] = false;
	int *parent = new int[V];
	for (int idx = 0; idx < V; ++idx)
		parent[idx] = -1;
	BFSUtil(v,visited,parent);
	printf ("BFS parent pointer: ");
	for (int idx = 0; idx < V; ++idx)
		printf(" %d ",parent[idx]);
}
void Graph::BFSUtil(int v, bool* visited,int *parent )
{
	visited[v] = true;
	list<int> queue;
	queue.push_back(v);
	//printf (" %d " , v);
	while (queue.empty()==false)
	{
		int v1 = queue.front();
		queue.pop_front();
		list<int>::iterator i;
		for(i = adj[v1].begin(); i != adj[v1].end(); ++i)
		{
			int adjV = *i;
			if (visited[adjV] == false)
			{
				visited[adjV] = true;
				parent[adjV] = v1;
				queue.push_back(adjV);
				printf("-> %d -> %d\n", v1+1, adjV+1);
			}
		}
	}
}
// DFS traversal of the vertices reachable from v. It uses recursive DFSUtil()
void Graph::DFS(int v)
{
    // Mark all the vertices as not visited
    bool *visited = new bool[V];
    for(int i = 0; i < V; i++)
        visited[i] = false;
   int *parent = new int[V];
   	for (int idx = 0; idx < V; ++idx)
		parent[idx] = -1;
    // Call the recursive helper function to print DFS traversal
	parent[v]=-2;
    DFSUtil(v, visited,parent);
	printf ("\nDFS Rec parent pointer: ");
	for (int idx = 0; idx < V; ++idx)
		printf(" %d ",parent[idx]);
	for(int i = 0; i < V; i++)
       visited[i] = false;
	
	for (int idx = 0; idx < V; ++idx)
		parent[idx] = -1;
	printf("\n");
	DFSUtil_Stack(v,visited,parent);
	printf ("DFS Stack parent pointer: ");
	for (int idx = 0; idx < V; ++idx)
		printf(" %d ",parent[idx]);
	 
}
 
int main2()
{
    // Create a graph given in the above diagram
#if 0
    Graph g(8);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(1,3);
    g.addEdge(1,4);
    g.addEdge(3,4);
	g.addEdge(4,5);
	g.addEdge(2,4);
	g.addEdge(2,6);
	g.addEdge(2,7);
	g.addEdge(6,7);
#endif
	Graph g (9);
	g.addEdge(0,1);
	g.addEdge(1,2);

	g.addEdge(0,3);
	g.addEdge(1,4);
	g.addEdge(2,5);

	g.addEdge(3,4);
	g.addEdge(4,5);

	g.addEdge(3,6);
	g.addEdge(4,7);
	g.addEdge(5,8);

	g.addEdge(6,7);
	g.addEdge(7,8);
    printf("%s\n", "Following is Depth First Traversal (starting from vertex 2) \n");
	g.BFS(0);
    g.DFS(0);
 
    return 0;
}