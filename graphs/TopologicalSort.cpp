#include <iostream>
#include <list>
#include <algorithm>
#include <map>
#include <functional>
#include <queue>
using namespace std;

class Vertex {
public:
	Vertex(int id) {
		_id = id;
		indegree = 0;
	}

	int id() const { return _id; }

	void addEdge(Vertex& to)
	{
		adjList.push_front(to);
	}

	int increment() { ++indegree;return indegree;}
	int getIndegree() { return indegree; }
	int decrement() { --indegree; return indegree;}
	list<reference_wrapper<Vertex> >& getAdjList() { return adjList; }

	friend bool operator==(const Vertex& first, const Vertex& second);
	bool operator<(const Vertex&  other) const
	{
		return _id < other.id();
	}
private:
	int _id;
	list<reference_wrapper<Vertex> > adjList;
	int indegree;
};
struct ObjectLess{

    bool operator()(const Vertex& lhs, const Vertex& rhs) const 
    {
        return lhs<rhs;
    }
};
bool operator==(const Vertex& first, const Vertex& second)
{
	return first.id() == second.id();
}
class Graph {
private:
	std::list<std::reference_wrapper<Vertex> > vertices;
	map< reference_wrapper<Vertex>, int,ObjectLess> getIndegreeMap()
	{
		map< reference_wrapper<Vertex>, int,ObjectLess> indegreeMap;
		for (list<std::reference_wrapper<Vertex> >::iterator iter = vertices.begin(); iter != vertices.end(); ++iter)
		{
			Vertex& from = (*iter).get();
			for (list<std::reference_wrapper<Vertex>>::iterator iter1 = from.getAdjList().begin(); iter1 != from.getAdjList().end(); ++iter1)
			{
				(*iter1).get().increment();
			}
		}
		for (list<std::reference_wrapper<Vertex> >::iterator iter = vertices.begin(); iter != vertices.end(); ++iter)
		{
			indegreeMap.insert(std::pair<reference_wrapper<Vertex>,int>(*iter, (*iter).get().getIndegree()));
		}
		return indegreeMap;
	}
public:
	Graph() {
	}

	void addEdge(Vertex& from, Vertex& to)
	{
		if (find(vertices.begin(),vertices.end(),from) == vertices.end())
			vertices.push_back(from);
		if (find(vertices.begin(), vertices.end(), to) == vertices.end())
			vertices.push_back(to);
		from.addEdge(to);
	}

	void toposort()
	{
		map< reference_wrapper<Vertex>, int,ObjectLess> indegmap = getIndegreeMap();
		queue< reference_wrapper<Vertex> > q;
		for (map< reference_wrapper<Vertex>, int, ObjectLess>::iterator iter = indegmap.begin(); iter != indegmap.end(); ++iter)
		{
			if ((*iter).second == 0)
				q.push(ref((*iter).first.get()));
		}
		cout << "Vertices: ";
		while (q.size() != 0) {
			Vertex& v = q.front();
			cout << " " << v.id() << " ";
			q.pop();
			list<reference_wrapper<Vertex> > neighbors = v.getAdjList();
			for (list<reference_wrapper<Vertex> >::iterator iter = neighbors.begin(); iter != neighbors.end(); ++iter) {
				if ((*iter).get().decrement()==0)
					q.push(*iter);
			}
		}
		cout << endl;
	}
};
int main()
{
	Vertex v1 =  Vertex(1);
	Vertex v2 =  Vertex(2);
	Vertex v3 =  Vertex(3);
	Vertex v4 =  Vertex(4);
	Graph* pg = new Graph();
	pg->addEdge(v1, v2);
	pg->addEdge(v1, v3);
	pg->addEdge(v3,v2);
	pg->addEdge(v3,v4);
	pg->addEdge(v2,v4);
	pg->toposort();
	delete pg;
}