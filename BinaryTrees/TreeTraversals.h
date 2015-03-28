#include <stdio.h>
#include <stdlib.h>
#include <stack>
#include <queue>
// http://www.math.ucla.edu/~wittman/10b.1.10w/Lectures/Lec18.pdf
// http://en.wikipedia.org/wiki/Tree_traversal#Morris_in-order_traversal_using_threading
// http://www.geeksforgeeks.org/618/
// http://eduk8tech.com/apcs/Data%20Structures%20and%20Algorithms%20in%20Java.pdf
// http://web.stanford.edu/~msirota/soco/inter.html : Iteration strategies
// https://www.youtube.com/watch?v=7QcoJjSVT38 : Iterative Deepning depth first search
// https://mhesham.wordpress.com/tag/bfs-vs-dfs/ : Space/Time Complexity
// http://pandeyece.blogspot.com/2012/12/part-ii-threaded-binary-search-tree.html threaded traversals
// http://www.cs.berkeley.edu/~kamil/teaching/su02/080802.ppt
// http://www.cs.usfca.edu/~brooks/S04classes/cs245/lectures/lecture11.pdf
// https://github.com/detro/coding-exercises : Good one for coding excercises
using namespace std;
class Node {
public:
	int data;
	Node* left;
	Node* right;
};
Node* createNode(int data);
int treeHeight(Node* root);
void preOrderRecursive(Node* root);
void preOrderIterative(Node* root);
void preOrderIterative1(Node* root);
void preOrderIterative2(Node* root);
void inOrderRecursive(Node* root);
void inOrderIterative(Node* root);
void inOrderIterative1(Node* root);
void postOrderRecursive(Node* root);
void postOrderIterative1(Node* root);
void postOrderIterative(Node* root);
void printLevelOrder1(Node* node);
void printLevelOrder(Node* node, int level);
void printLevelOrder2(Node* root);
void MorrisInOrder(Node* root, int travelType);
Node* getSimpleTree();
Node* getComplexTree();
int treeTests();