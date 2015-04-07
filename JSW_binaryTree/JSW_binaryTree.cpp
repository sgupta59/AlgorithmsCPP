// JSW_binaryTree.cpp : Defines the entry point for the console application.
//
//http://www.eternallyconfuzzled.com/tuts/datastructures/jsw_tut_bst1.aspx
// https://github.com/gyaikhom/binary-search-trees/blob/master/src/BinarySearchTree.cpp
// http://stackoverflow.com/questions/5502916/explain-morris-inorder-tree-traversal-without-using-stacks-or-recursion/5506601#5506601
//http://stackoverflow.com/questions/5496464/write-a-non-recursive-traversal-of-a-binary-search-tree-using-constant-space-and?lq=1
// http://tech.technoflirt.com/2011/03/04/non-recursive-tree-traversal-in-on-using-constant-space/
#include "stdafx.h"

#include <queue>
using namespace std;
typedef struct Node {
	int data;
	Node* left;
	Node* right;
	Node* parent;
} *pNode;

typedef struct Tree {
	Node* root;
};

Node* make_node(int data)
{
	Node* node = new Node();
	node->left=NULL;
	node->right=NULL;
	node->parent = NULL;
	node->data = data;
	return node;
}
Node* insert_node_r(Node* root, int data)
{
	if (root == NULL)
		return make_node(data);
	if (root->data == data)
		return root;
	if (data < root->data)
	{
		root->left =  insert_node_r(root->left,data);
		if (root->left->parent == NULL) root->left->parent = root;
	}
	else
	{
		root->right = insert_node_r(root->right,data);
		if (root->right->parent == NULL) root->right->parent = root;
	}
	return root;
}

Node* insert_node_i (Node* root, int data)
{
	if (root == NULL)
		return make_node(data);
	Node* current = root;
	Node* parent = root;
	while (current != NULL)
	{
		if (current->data == data)
			return current;
		parent = current;
		if (current->data > data)
			current = current->left;
		else
			current = current->right;
	}
	current = make_node(data);
	if (parent->data > data) 
		parent->left = current;
	else
		parent->right = current;
	// set the parent of the current node.
	current->parent = parent;
	return root;
}
int insert_tree(Tree* tree, int data)
{
	//tree->root = insert_node_r(tree->root,data);
	tree->root = insert_node_i(tree->root,data);
	return 1;
}
Node* tree_find_r(Node* root, int data)
{
	if (root == NULL)
		return root;
	if (root->data == data)
		return root;

	if (root->data > data)
		return tree_find_r(root->left, data);
	return tree_find_r(root->right,data);
}
Node* tree_find_i(Node* root, int data)
{
	while (root != NULL)
	{
		if (root->data == data)
			return root;
		if (data < root->data)
			root = root->left;
		else
			root = root->right;
	}
	return root;
}
void printInOrder(Node* root)
{
	queue<Node*> q;
	if (root == NULL)
		return;
	q.push(root);
	while (q.empty() == false)
	{
		Node* current = q.front();
		q.pop();
		printf( " %d ", current->data);
		if (current->left != NULL)
			q.push(current->left);
		if (current->right != NULL)
			q.push(current->right);
	}
	printf("\n");
}

int delete_node(Tree* tree, int data)
{
	if (tree->root == NULL)
		return 0;
	Node* root = tree->root;
	// first find the node to delete and its parent node.
	Node* current = root;
	// Parent is null in case root is being deleted.
	Node* parent = NULL;
	while (current != NULL)
	{
		if (current->data == data)
			break;
		parent = current;
		if (current->data > data)
		{
			parent = current;
			current = current->left;
		}
		else
		{
			current = current->right;
		}
	}
	if (current->left != NULL && current->right != NULL)
	{
		// do something
		Node* toDel = current;
		Node* parent = current;
		Node* successor = current->right;
		while (successor->left != NULL)
		{
			parent = successor;
			successor = successor->left;
		}
		current->data = successor->data;
		parent->left = successor->right;
		delete successor;
	}
	else
	{
		Node* child = current->left == NULL ? current->right : current->left;
		if (parent == NULL)
		{
			// root is being deleted.
			tree->root = child;		
		}
		else
		{
			if (parent->left == current)
				parent->left = child;
			else
				parent->right = child;
		}
		delete current;
	}
	return 1;
}
Node* delete_node_r(Node* root, int data)
{
	if (root == NULL)
		return NULL;
	if (root->data == data)
	{
		if (root->left != NULL && root->right != NULL)
		{
			Node* successor = root->right;
			while(successor->left != NULL)
			{
				successor = successor->left;
			}
			root->data = successor->data;
			data = successor->data;
		}
		else
		{
			Node* save = root;
			Node* child = root->left == NULL ? root->right : root->left;
			if (root->left == NULL)
				root = root->right;
			else
				root = root->left;
			delete save;
			return root;
		}
	}
	if (data < root->data)
		root->left = delete_node_r(root->left,data);
	else
		root->right = delete_node_r(root->right,data);
	return root;
}
void destroyTreeWithParentPointer(Node* root)
{
	if (root == NULL)
		return ;
	Node* temp;
	while (root != NULL)
	{
		// find a node which has no left and right children.
		if (root->left != NULL)
		{
			root = root->left;
			continue;
		} 
		else if (root->right != NULL)
		{
			root = root->right;
			continue;
		}
		temp = root->parent;
		if (temp) {
			if (temp->left == root)
				temp->left = NULL;
			else 
				temp->right = NULL;
		}
		fprintf(stdout,"Deleting Node: %d", root->data);
		delete root;
		root = temp;
	}
}

void deleteTreeRotation(Node* root)
{
	Node* it = root;
	Node* save = NULL;
	while (it != NULL)
	{
		// Right rotate till a node found with no left child
		if (it->left != NULL)
		{
			save = it->left;
			it->left = save->right;
			save->right = it;
		}
		else
		{
			save = it->right;
			delete it;
		}
		it = save;
	}
}
void tree_structure_r(Node* root, int level)
{
	int i = 0;
	if (root == NULL) {
		for (i = 0; i < level; ++i)
			putchar('\t');
		puts("~");
	}
	else {
		tree_structure_r(root->left,level+1);
		for (i = 0; i < level; ++i)
			putchar('\t');
		printf("%d\n", root->data);
		tree_structure_r(root->right,level+1);
	}
}

void MorrisTraversal(Node* root)
{
	Node* current, *pre;
	if (root == NULL)
		return;
	current = root;
	while (current != NULL)
	{
		if (current->left == NULL)
		{
			printf(" %d ", current->data);
			current = current->right;
		}
		else
		{
			pre = current->left;
			while (pre->right != NULL && pre->right != current)
				pre = pre->right;
			if (pre->right == NULL)
			{
				pre->right = current;
				current = current->left;
			}
			else
			{
				pre->right = NULL;
				printf(" %d ", current->data);
				current = current->right;
			}
		}
	}
}
void traversal_constant(Node* root)
{
	while (root)
	{
		Node* next = root->left;
		if (next) {
			root->left = next->right;
			next->right = root;
			root = next;
		} 
		else
		{
			printf(" %d ", root->data);
			root = root->right;
		}
	}
}
// http://tech.technoflirt.com/2011/03/04/non-recursive-tree-traversal-in-on-using-constant-space 
void printPreOrderConstant(Node* node)
{
	Node* prev = node->parent;
	Node* temp = NULL;
	while (node != NULL)
	{
		if (node->parent == prev)
			printf(" %d ", node->data);
		temp = prev;
		prev = node;
		if (node->left && node->parent == temp)
			node = node->left;
		else if (node->right && temp != node->right)
			node = node->right;
		else
			node = node->parent;
	}
}
/** http://stackoverflow.com/questions/5496464/write-a-non-recursive-traversal-of-a-binary-search-tree-using-constant-space-and?lq=1 */
void printInorderConstant(Node* current, Node* parent)
{
	while (current != NULL) {
		if (parent != NULL) {
			printf(" %d ", parent->data);
			parent->left = current->right;
			current->right = parent;
		}
		if (current->left != NULL)
		{
			printf(" %d ", current->data);
			parent = current;
			current = current->left;
		} else {
			//printf(" %d ", current->data);
			current = current->right;
			parent = NULL;
		}
	}
}
Node* constructTreeUtil(int pre[], int* preIndex, int low, int high, int size)
{
	if (*preIndex >= size || low > high)
		return NULL;
	Node* root = make_node(pre[*preIndex]);
	*preIndex = *preIndex+1;
	if (low == high)
		return root;
	int idx = 0;
	for (idx = low; idx <= high; ++idx)
		if (pre[idx] > root->data)
			break;
	root->left = constructTreeUtil(pre,preIndex,*preIndex,idx-1,size);
	root->right = constructTreeUtil(pre,preIndex,idx,high,size);
	return root;
}
// http://www.geeksforgeeks.org/serialize-deserialize-binary-tree/
// http://www.geeksforgeeks.org/construct-bst-from-given-preorder-traversal-set-2/
// http://www.geeksforgeeks.org/construct-bst-from-given-preorder-traversa/
Node* constructTree()
{
	int pre[] = {10, 5, 1, 7, 40, 50};
	int size = sizeof(pre)/sizeof(pre[0]);
	int preIndex = 0;
	return constructTreeUtil(pre, &preIndex, 0, size-1,size);
}
void reverse(Node *from, Node *to) // reverse the tree nodes 'from' -> 'to'.
{
    if (from == to)
        return;
    Node *x = from, *y = from->right, *z;
    while (true)
    {
        z = y->right;
        y->right = x;
        x = y;
        y = z;
        if (x == to)
            break;
    }
}

void printReverse(Node* from, Node *to) // print the reversed tree nodes 'from' -> 'to'.
{
    reverse(from, to);
    
    Node *p = to;
    while (true)
    {
        printf("%d ", p->data);
        if (p == from)
            break;
        p = p->right;
    }
    
    reverse(to, from);
}

void postorderMorrisTraversal(Node *root) {
    Node dump;
    dump.left = root;
	dump.right = NULL;
    Node *cur = &dump, *prev = NULL;
    while (cur)
    {
        if (cur->left == NULL)
        {
            cur = cur->right;
        }
        else
        {
            prev = cur->left;
            while (prev->right != NULL && prev->right != cur)
                prev = prev->right;

            if (prev->right == NULL)
            {
                prev->right = cur;
                cur = cur->left;
            }
            else
            {
                printReverse(cur->left, prev);  // call print
                prev->right = NULL;
                cur = cur->right;
            }
        }
    }
}
int main()
{
	Node* test = constructTree();
	Tree* tree = new Tree();
	tree->root = NULL;
	insert_tree(tree,10);
	insert_tree(tree,5);
	insert_tree(tree,20);
	insert_tree(tree,3);
	insert_tree(tree,7);
	postorderMorrisTraversal(tree->root);
#if 0 
	insert_tree(tree,5);
	insert_tree(tree,2);
	insert_tree(tree,8);
	insert_tree(tree,1);
	insert_tree(tree,4); 
	insert_tree(tree,7);
	insert_tree(tree,9);
	insert_tree(tree,0);
	insert_tree(tree,3);
	insert_tree(tree,6);
#endif
	printInorderConstant(tree->root->left, tree->root);
	printPreOrderConstant(tree->root);
	// should print 5 2 8 1 4 7 9 0 3 6
	printInOrder(tree->root);
	traversal_constant(tree->root);
	printInOrder(tree->root);
	tree_structure_r(tree->root,0);
	Node* node = tree_find_r(tree->root,0);
	// delete 6 and print tree
	delete_node(tree,7);
	printInOrder(tree->root);
	insert_tree(tree,7);
	printInOrder(tree->root);
	delete_node_r(tree->root,2);
	printInOrder(tree->root);
	return 0;
}

