#include <stdio.h>
#include <list>
 
using namespace std;
#define V 12
bool graph[11][11] = {
	{0, 1, 1, 0, 0, 0, 0, 0,0,0,0}, // 1
    {1, 0, 1, 1, 1, 0, 0, 0,0,0,0}, // 2
    {1, 1, 0, 0, 1, 0, 1, 1,0,0,0}, // 3
    {0, 1, 0, 0, 1, 0, 0, 0,0,0,0}, // 4
    {0, 1, 1, 1, 0, 1, 0, 0,0,0,0}, // 5
	{0, 0, 0, 0, 1, 0, 0, 0,0,0,0}, // 6
	{0, 0, 1, 0, 0, 0, 0, 1,0,0,0}, // 7
	{0, 0, 1, 0, 0, 0, 1, 0,0,0,0}, // 8
	{0, 0, 0, 0, 0, 0,0, 0,0,1,0},  // 9
	{0, 0, 0, 0, 0, 0, 0, 0,1,0,1}, // 10
	{0, 0, 0, 0, 0, 0, 0, 0,0,1,0} // 11
};
bool** createMatrixForm()
{

	bool** graph1 = NULL;
	graph1 = new bool*[V];
	for (int i = 0; i < V; ++i)
	{
		graph1[i] = new bool[V];
	}

	return graph1;
}

void BFS(int vid, bool* visited, int length)
{
	visited[vid] = true;
	// create a queue.
	list<int> queue;

	queue.push_back(vid);

	while (queue.empty()==false)
	{
		int id = queue.front();
		queue.pop_front();
		for (int idx = 0; idx < length; ++idx)
		{
			if (visited[idx] != true && graph[id][idx] == true)
			{
				visited[idx] = true;
				queue.push_back(idx);
				printf("Edge from %d to %d\n", id+1, idx+1);
			}
			
		}
	}
}
int countConnectedBFS()
{
	int length = sizeof(graph[0])/sizeof(bool);
	bool *visited = new bool[length];
	for (int idx = 0; idx < length; ++idx)
		visited[idx] = false;
	int components = 0;
	for (int idx = 0; idx < length; ++idx)
	{
		if (visited[idx] == false)
		{
			BFS(idx,visited,length);
			++components;
		}
	}
	return components;
}
int main1()
{
	countConnectedBFS();
	return 0;
}