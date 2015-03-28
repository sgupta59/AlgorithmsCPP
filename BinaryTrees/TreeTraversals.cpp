#include "TreeTraversals.h"
int treeTests()
{
	Node* root1 = getSimpleTree();
	int height = treeHeight(root1);
	Node* root = getComplexTree();//getSimpleTree();
#if 0
	printf("Preorder traversal, expected:\n 15 5 3 12 10 6 7 13 16 20 18 23\n");
	preOrderRecursive(root);
	printf("\n");
	preOrderIterative(root);
	printf("\n");
	preOrderIterative1(root);
	printf("\n");
	preOrderIterative2(root);
	printf("\n");
#endif 
#if 1
	printf("in order traversal, expected:\n 3 5 6 7 10 12 13 15 16 18 20 23\n");
	inOrderRecursive(root);
	printf("\n");
	inOrderIterative(root);
	printf("\n");
	inOrderIterative1(root);
	printf("\n");
#endif
#if 1
	printf("PostOrder traversal, expected:\n 3 7 6 10 13 12 5 18 23 20 16 15\n");
	postOrderRecursive(root);
	printf("\n");
	postOrderIterative(root);
#endif
#if 0 
	printf("Level Order traversal, expected:\n 15 5 16 3 12 20 10 13 18 23 6 7\n");
	printLevelOrder2(root);
	printLevelOrder1(root);
#endif
	printf("in order traversal, expected:\n 3 5 6 7 10 12 13 15 16 18 20 23\n");
	MorrisInOrder(root,0);
	printf("\n");
	printf("Preorder traversal, expected:\n 15 5 3 12 10 6 7 13 16 20 18 23\n");
	MorrisInOrder(root,1);
	return 0;
}

Node* createNode(int data)
{
	Node* node = new Node();
	node->data = data;
	node->left = NULL;
	node->right = NULL;
	return node;
}

int treeHeight(Node* root)
{
	if (root == NULL)
		return 0;
	int lheight = treeHeight(root->left);
	int rheight = treeHeight(root->right);
	if (lheight > rheight)
		return lheight+1;
	return rheight+1;
}
void preOrderRecursive(Node* root)
{
	// print current node.
	if (root == NULL)
		return;
	printf(" %d", root->data);
	// print left tree
	preOrderRecursive(root->left);
	// print right tree
	preOrderRecursive(root->right);
	return;
}
/**
 * Collect all the right nodes of a root
 */
void preOrderIterative(Node* root)
{
	stack<Node*> mystack;
	while (root != NULL || mystack.empty() == false)
	{
		if (root == NULL)
		{
			root = mystack.top();
			mystack.pop();
		}
		printf(" %d" , root->data);
		if (root->right != NULL)
			mystack.push(root->right);
		root = root->left;
	}
}

void preOrderIterative1(Node* root)
{
	stack<Node*> mystack;
	while (root != NULL || mystack.empty() == false)
	{
		if (root != NULL)
		{
			mystack.push(root);
			printf( " %d", root->data);
			root = root->left;
			continue;
		}
		Node* node = mystack.top();
		mystack.pop();
		root = node->right;
	}
}
void preOrderIterative2(Node* root)
{
	stack<Node*> mystack;
	mystack.push(root);
	while (mystack.empty()==false)
	{
		Node* curnode = mystack.top();
		mystack.pop();
		printf(" %d", curnode->data);
		if (curnode->right != NULL)
			mystack.push(curnode->right);
		if (curnode->left != NULL)
			mystack.push(curnode->left);
	}
}

void inOrderRecursive(Node* root)
{
	if (root == NULL)
		return;
	// print left tree
	inOrderRecursive(root->left);
	// print current node
	printf(" %d", root->data);
	// print right tree
	inOrderRecursive(root->right);
}

void inOrderIterative(Node* root)
{
	stack<Node*> mystack;
	while (root != NULL || mystack.empty() == false)
	{
		if (root != NULL)
		{
			mystack.push(root);
			root = root->left;
		}
		else
		{
			root = mystack.top();
			mystack.pop();
			printf(" %d", root->data);
			root = root->right;
		}
	}
}
void inOrderIterative1(Node* root)
{
	stack<Node*> s;
	s.push(root);
	Node* lastPopped = NULL;
	while (s.empty() == false)
	{
		Node* current = s.top();
		if (current->left != NULL && current->left != lastPopped)
		{
			s.push(current->left);
			continue;
		}
		printf(" %d", current->data);
		s.pop();
		lastPopped = current;
		if (current->right != NULL)
			s.push(current->right);
	}
}
void postOrderRecursive(Node* root)
{
	if (root == NULL)
		return;
	// print left tree
	postOrderRecursive(root->left);
	// print right tree
	postOrderRecursive(root->right);
	// print node
	printf(" %d" , root->data);
}
/**
 *  if root is not null, put the roots right child and the root on teh stack in this order.
 */
void postOrderIterative1(Node* root)
{
	stack<Node*> mystack;
	while (root != NULL || mystack.empty() == false)
	{
		if (root != NULL)
		{
			if (root->right != NULL)
				mystack.push(root->right);
			mystack.push(root);
			root = root->left;
		}
		else
		{
			Node* top = mystack.top();
			mystack.pop();
			if (mystack.empty() == false && top->right == mystack.top())
			{
				// If the top node's right child and stack top are the same
				root = mystack.top();
				mystack.pop();
				mystack.push(top);
			}
			else
			{
				printf(" %d", top->data);
			}
		}
	}
}
void postOrderIterative(Node* root)
{
	stack<Node*> mystack;
	Node* lastPopped = NULL;
	while (root != NULL || mystack.empty() == false)
	{
		if (root == NULL)
		{
			Node* top = mystack.top();
			// If root is null, get the top of the stack. If the right child of the stack's top
			// and the last popped items are not the same, then go to the right. 
			// This is done as a "root" will be visited twice, once from root to right child (this case)
			// and other from the right child to root , i.e. rivht child has been processed and now it is
			// time for the root (node 6 in this example)
			if (top->right != NULL && top->right != lastPopped)
			{
				root = top->right;
				continue;
			}
			printf(" %d", top->data);
			mystack.pop();
			lastPopped = top;
		}
		if (root  != NULL)
		{
			// 1. continue going to the right subtree as long as there are left children.
			mystack.push(root);
			root = root->left;
			continue;
		}
		if (root  != NULL)
		{
			// 2. From (1), once a null item is found, keep collecting the right sub tree items.
			mystack.push(root);
			root = root->right;
			continue;
		}
		 
	}
}
void printLevelOrder1(Node* node)
{
	queue<Node*> myqueue;
	myqueue.push(node);
	while (myqueue.empty() == false)
	{
		Node* node = myqueue.front();
		myqueue.pop();
		printf(" %d", node->data);
		if (node->left != NULL)
			myqueue.push(node->left);
		if (node->right != NULL)
			myqueue.push(node->right);
	}
}
void printLevelOrder(Node* node, int level)
{
	if (node == NULL)
		return;
	if (level == 1)
		printf(" %d", node->data);
	else /** if (level > 1) */
	{
		printLevelOrder(node->left,level-1);
		printLevelOrder(node->right,level-1);
	}
#if 0 
	else
	{
		printf("caught!!");
	}
#endif
}
void printLevelOrder2(Node* root)
{
	int height = treeHeight(root);
	for (int i = 1; i <= height; ++i)
		printLevelOrder(root,i);
}
void MorrisInOrder(Node* root, int travelType)
{
	Node* p = root; Node* tmp;
	while (p != NULL)
	{
		if (p->left == NULL) 
		{
			printf(" %d", p->data);
			p = p->right;
		}
		else
		{
			tmp = p->left;
			while (tmp->right != NULL && tmp->right != p) {
				// Go to the rightmost node of the left subtree or to the temporary parent of p.
				tmp = tmp->right;
			}
			if (tmp->right == NULL) {
				// at the right most node of the left child (tmp), make the node p point to right child of 
				// tmp. Set p to be the left child, i.e make the tmp node parent of 'p'
				tmp->right = p;
				if (travelType == 1)
					printf(" %d", p->data);
				p = p->left;
			} else {
				// A temporary parent is found, visit p and blah blah
				if (travelType == 0)
					printf(" %d", p->data);
				tmp->right = NULL;
				p = p->right;
			}
		}
	}
}
Node* getSimpleTree()
{
	Node* root = createNode(1);
	root->left = createNode(2);
	root->right = createNode(3);
	root->left->left = createNode(4);
	root->left->right = createNode(5);
	return root;
}

Node* getComplexTree()
{
	// Level order insertions
	Node* root = createNode(15);
	root->left = createNode(5);
	root->right = createNode(16);

	root->left->left = createNode(3);
	root->left->right = createNode(12);

	root->left->right->left = createNode(10);
	root->left->right->right = createNode(13);


	root->left->right->left->left = createNode(6);
	root->left->right->left->left->right = createNode(7);

	root->right->right = createNode(20);
	root->right->right->left = createNode(18);
	root->right->right->right = createNode(23);
    return root;
}
