#include <stdio.h>
#include <stdlib.h>
#include <stack>
using namespace std;
const int V = 4;

bool isValidColor(int G[V][V], int vid, int color, int c[])
{
	for (int idx = 0; idx < V; ++idx)
	{
		if (G[vid][idx] != 0 && c[idx] == color)
			return false;
	}
	return true;
}
bool colorGraph(int G[V][V], int vid,  int clen, int c[])
{
	if (vid == V)
		return true;
	for (int idx = 1; idx <= clen; ++idx)
	{
		if (isValidColor(G, vid, idx,c))
		{
			c[vid] = idx;
			if (colorGraph(G,vid+1,clen,c))
				return true;
			c[vid] = 0;
		}
	}
	return false;
}
int main()
{
	int G[4][4] = {{0, 1, 1, 1},
        {1, 0, 1, 0},
        {1, 1, 0, 1},
		{1, 0, 1, 0}};
	int color[4] = {0,0,0,0};
	colorGraph(G,0,4,color);
	return 0;
}