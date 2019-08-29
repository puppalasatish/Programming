// Tree_Sample.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <queue>
#include "stdio.h" 
#include <stdlib.h> 
using namespace std;


// C program to demonstrate delete operation in binary search tree 


struct node
{
	int key;
	struct node *left, *right;
};

// A utility function to create a new BST node 
struct node *newNode(int item)
{
	struct node *temp = (struct node *)malloc(sizeof(struct node));
	temp->key = item;
	temp->left = temp->right = NULL;
	return temp;
}



int auxtreeHeight(node* root){	
	if (root == NULL) return 0;
	int l = 0, r = 0;
	if (root->left != NULL) 
		l = 1 + auxtreeHeight(root->left);
	if (root->right != NULL) 
		r = 1 + auxtreeHeight(root->right);
	return l > r ? l : r;
}

void printLevelOrder(node* root)
{
	// Base Case  
	if (root == NULL) return;

	// Create an empty queue for level order tarversal  
	queue<node*> q;

	// Enqueue Root and initialize height  
	q.push(root);

	while (q.empty() == false)
	{
		// nodeCount (queue size) indicates number 
		// of nodes at current lelvel.  
		int nodeCount = q.size();

		// Dequeue all nodes of current level and  
		// Enqueue all nodes of next level  
		//while (nodeCount > 0)
		{
			node* node = q.front();
			cout << node->key << " ";
			q.pop();
			if (node->left != NULL)
				q.push(node->left);
			if (node->right != NULL)
				q.push(node->right);
			nodeCount--;
		}
		cout << endl;
	}
}


// A utility function to do inorder traversal of BST 
void inorder(struct node *root)
{
	if (root != NULL)
	{
		inorder(root->left);
		printf("%d ", root->key);
		inorder(root->right);
	}
}

void preOrder(struct node* root) {
	if (root != NULL) {
		printf("%d ", root->key);
		preOrder(root->left);
		preOrder(root->right);
	}
}

/* A utility function to insert a new node with given key in BST */
struct node* insert(struct node* node, int key)
{
	/* If the tree is empty, return a new node */
	if (node == NULL) return newNode(key);

	/* Otherwise, recur down the tree */
	if (key < node->key)
		node->left = insert(node->left, key);
	else
		node->right = insert(node->right, key);

	/* return the (unchanged) node pointer */
	return node;
}

/* Given a non-empty binary search tree, return the node with minimum
   key value found in that tree. Note that the entire tree does not
   need to be searched. */
struct node * minValueNode(struct node* node)
{
	struct node* current = node;

	/* loop down to find the leftmost leaf */
	while (current && current->left != NULL)
		current = current->left;

	return current;
}

/* Given a binary search tree and a key, this function deletes the key
   and returns the new root */
struct node* deleteNode(struct node* root, int key)
{
	// base case 
	if (root == NULL) return root;

	// If the key to be deleted is smaller than the root's key, 
	// then it lies in left subtree 
	if (key < root->key)
		root->left = deleteNode(root->left, key);

	// If the key to be deleted is greater than the root's key, 
	// then it lies in right subtree 
	else if (key > root->key)
		root->right = deleteNode(root->right, key);

	// if key is same as root's key, then This is the node 
	// to be deleted 
	else
	{
		// node with only one child or no child 
		if (root->left == NULL)
		{
			struct node* temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL)
		{
			struct node* temp = root->left;
			free(root);
			return temp;
		}

		// node with two children: Get the inorder successor (smallest 
		// in the right subtree) 
		struct node* temp = minValueNode(root->right);

		// Copy the inorder successor's content to this node 
		root->key = temp->key;

		// Delete the inorder successor 
		root->right = deleteNode(root->right, temp->key);
	}
	return root;
}



// Driver Program to test above functions 
int main()
{
	/* Let us create following BST
			  50
		   /     \
		  30      70
		 /  \    /  \
	   20   40  60   80 */
	struct node *root = NULL;
	root = insert(root, 20);
	root = insert(root, 10);
	root = insert(root, 30);
	root = insert(root, 5);
	root = insert(root, 13);
	root = insert(root, 36);
	root = insert(root, 29);

	root = insert(root, 37);
	root = insert(root, 38);
	root = insert(root, 39);


	//printf("Inorder traversal of the given tree \n");
	//inorder(root);

	//printf("\nDelete 20\n");
	//root = deleteNode(root, 20);
	//printf("Inorder traversal of the modified tree \n");
	//inorder(root);

	//printf("\nDelete 30\n");
	//root = deleteNode(root, 30);
	//printf("Inorder traversal of the modified tree \n");
	//inorder(root);

	//printf("\nDelete 50\n");
	//root = deleteNode(root, 50);
	//printf("Inorder traversal of the modified tree \n");
	//inorder(root);


	//printf("\Level traversal of the modified tree \n");
	//printLevelOrder(root);

	printf("Height of the tree = %d \n", auxtreeHeight(root)+1);

	return 0;
}