#include <stdio.h>
#include <stdlib.h>

struct Node {
	int data;
	Node* left;
	Node* right;
};


int height(Node* node)
{
	if (node == NULL)
		return 0;
	int lheight = height(node->left);
	int rheight = height(node->right);
	if (lheight > rheight)
		return 1+lheight;
	return 1+rheight;
}
Node* newNode(int data)
{
	Node* node = (Node*)malloc(sizeof(Node));
  node->data = data;
  node->left = NULL;
  node->right = NULL;
 
  return(node);
}

void printGivenLevel(Node* root, int level)
{
	if (root == NULL)
		return;
	if (level == 1)
		printf(" %d " , root->data);
	else {
		printGivenLevel(root->left,level-1);
		printGivenLevel(root->right,level-1);
	}
}
void printLevelOrder(Node* node)
{
	for (int i = 1; i <= height(node); ++i)
		printGivenLevel(node,i);
}
void main()
{
  Node *root = newNode(1);
  root->left        = newNode(2);
  root->right       = newNode(3);
  root->left->left  = newNode(4);
  root->left->right = newNode(5);	
  printf("Height = %d\n",height(root));
  printLevelOrder(root);
	return;
}