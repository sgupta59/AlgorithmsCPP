#include <iostream>
#include <stack>
using namespace std;
class Node {
public:
    int data;
    Node* next;
};

Node* createNode(int data)
{
    Node* node = new Node();
    node->next = NULL;
    node->data = 0;
    return node;
}
void insertAtBottom(stack<int>& s, int i)
{
    if (s.empty())
    {
        s.push(i);
        return;
    }
    int j = s.top();
    s.pop();
    insertAtBottom(s,i);
    s.push(j);
}
void reverse(stack<int>& s)
{
    if (s.empty())
        return;
    int i = s.top();
    s.pop();
    reverse(s);
    insertAtBottom(s,i);
}

void insertSorted(stack<int>& s, i)
{
    if (s.empty() || i < s.top())
        s.push(i);
    int j = s.top();
    s.pop();
    insertSorted(s,i);
    s.push(j);
}
void sort(stack<int>& s)
{
    if (s.empty())
        return;
    int i = s.top();
    s.pop();
    sort(s);
    insertSorted(s,i);
    return;
}
void main()
{
    stack<int> s;
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);
    s.push(5);
    //while (!s.empty()) 
    //{
    //    cout << s.top() << endl;
    //   s.pop();
    //}
     
    while (!s.empty()) 
    {
        cout << s.top() << endl;
        s.pop();
    }
}