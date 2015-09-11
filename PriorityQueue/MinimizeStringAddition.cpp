#include <iostream>
#include <queue>
#include <algorithm>
using namespace std;

class compLess {
public:
	bool operator() (const int& lhs, const int& rhs) {
		cout << "LHS: " << lhs << ", RHS " << rhs << ", " << (lhs < rhs) << endl;
		return lhs < rhs;
	}
};

class compGreater {
public:
	bool operator() (const int& lsh, const int& rhs) {
		cout << "LHS:  " << lsh << ", RHS: " << rhs << ": " << (lsh > rhs) << endl;
		return lsh > rhs;
	}
};
/* http://popalgo.blogspot.com/2015/07/minimize-cost-of-string-concatenation.html */
int concat (priority_queue<int,vector<int>,compLess>& pq, int& sum) 
{
	if (pq.size() == 1)
		return pq.top();
	int n1 = pq.top();
	pq.pop();
	int n2 = pq.top();
	pq.pop();
	pq.push(n1+n2);
	sum += n1+ n2;
	return concat(pq,sum);
}
void main()
{
	int myints[] = {1, 3,2}; 
	int sum = 0;
	priority_queue<int,vector<int>, greater<int> > pq1;
	pq1.push(1);
	cout << endl;
	pq1.push(2);
	cout << endl;
	pq1.push(3);
	cout << endl;
	pq1.push(4);
	cout << endl;
	pq1.push(5);
	cout << endl;
	cout << pq1.top() << endl;
	pq1.pop();
	cout << pq1.top() << endl;
	pq1.pop();
	cout << pq1.top() << endl;
	pq1.pop();
	
	std::priority_queue<int,std::vector<int>,compLess> pq(myints, myints+3);
	concat(pq, sum);
	cout << sum;
}