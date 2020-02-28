#include<iostream>
#include<stdlib.h>
//#include <bits/stdc++.h>

using namespace std;

//enum color {red, black};

struct node{
	
	struct node* right;
	struct node* left;
	struct node* parent;
//	bool color;
	int black;
	int red;
	int data;
};

struct node* root = NULL;

//create a new node
struct node* createNode(int data){
	
	struct node* newNode  = (struct node*)malloc(sizeof(struct node));
	newNode->red = 1;
	newNode->black = 0;
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->parent = NULL;
	newNode->data = data;
	
	return newNode;
}

//swap colors of two nodes
void swap(struct node* parentPt, struct node* grandParentPt){
	
	struct node* temp;
	temp->black = parentPt->black;
	temp->red = parentPt->red;
	
	parentPt->black = grandParentPt->black;
	parentPt->red = grandParentPt->red;
	
	grandParentPt->black = temp->black;
	grandParentPt->red = temp->red;
}

//rotate right
void rotateRight(node *&rootNode, node *&pt) 
{ 
	node *pt_left = pt->left; 

	pt->left = pt_left->right; 

	if (pt->left != NULL) 
		pt->left->parent = pt; 

	pt_left->parent = pt->parent; 

	if (pt->parent == NULL) 
		rootNode = pt_left; 

	else if (pt == pt->parent->left) 
		pt->parent->left = pt_left; 

	else
		pt->parent->right = pt_left; 

	pt_left->right = pt; 
	pt->parent = pt_left; 
}

//rotate left
void rotateLeft(node *&rootNode, node *&pt) 
{ 
	node *pt_right = pt->right; 

	pt->right = pt_right->left; 

	if (pt->right != NULL) 
		pt->right->parent = pt; 

	pt_right->parent = pt->parent; 

	if (pt->parent == NULL) 
		rootNode = pt_right; 

	else if (pt == pt->parent->left) 
		pt->parent->left = pt_right; 

	else
		pt->parent->right = pt_right; 

	pt_right->left = pt; 
	pt->parent = pt_right; 
}

//check for violences
void fixViolation(node *&rootNode, node *&pt) 
{ 
	node *parent_pt = NULL; 
	node *grand_parent_pt = NULL; 

	while ((pt != rootNode) && (pt->black != 1) && 
		(pt->parent->red == 1)) 
	{ 

		parent_pt = pt->parent; 
		grand_parent_pt = pt->parent->parent; 

		/* Case : A 
			Parent of pt is left child of Grand-parent of pt */
		if (parent_pt == grand_parent_pt->left) 
		{ 

			node *uncle_pt = grand_parent_pt->right; 

			/* Case : 1 
			The uncle of pt is also red 
			Only Recoloring required */
			if (uncle_pt != NULL && uncle_pt->red == 1) 
			{ 
				grand_parent_pt->red = 1; 
				grand_parent_pt->black = 0;
				parent_pt->black = 1;
				parent_pt->red = 0; 
				uncle_pt->black = 1; 
				uncle_pt->red = 0;
				pt = grand_parent_pt; 
			} 

			else
			{ 
				/* Case : 2 
				pt is right child of its parent 
				Left-rotation required */
				if (pt == parent_pt->right) 
				{ 
					rotateLeft(rootNode, parent_pt); 
					pt = parent_pt; 
					parent_pt = pt->parent; 
				} 

				/* Case : 3 
				pt is left child of its parent 
				Right-rotation required */
				rotateRight(rootNode, grand_parent_pt); 
				swap(parent_pt, grand_parent_pt); 
				pt = parent_pt; 
			} 
		} 

		/* Case : B 
		Parent of pt is right child of Grand-parent of pt */
		else
		{ 
			node *uncle_pt = grand_parent_pt->left; 

			/* Case : 1 
				The uncle of pt is also red 
				Only Recoloring required */
			if ((uncle_pt != NULL) && (uncle_pt->red == 1)) 
			{ 
				grand_parent_pt->red = 1; 
				grand_parent_pt->black = 0;
				parent_pt->black = 1; 
				parent_pt->red = 0;
				uncle_pt->black = 1;
				uncle_pt->red = 0; 
				pt = grand_parent_pt; 
			} 
			else
			{ 
				/* Case : 2 
				pt is left child of its parent 
				Right-rotation required */
				if (pt == parent_pt->left) 
				{ 
					rotateRight(rootNode, parent_pt); 
					pt = parent_pt; 
					parent_pt = pt->parent; 
				} 

				/* Case : 3 
				pt is right child of its parent 
				Left-rotation required */
				rotateLeft(rootNode, grand_parent_pt); 
				swap(parent_pt, grand_parent_pt); 
				pt = parent_pt; 
			} 
		} 
	} 

	rootNode->black = 1; 
} 

//insert node
struct node* insertNode(struct node* rootNode, struct node* ptr){
	
	if(rootNode == NULL){

		return ptr;
	}
	
	if(ptr->data < rootNode->data){
		
		rootNode->left = insertNode(rootNode->left, ptr);
		ptr->parent = rootNode;
		cout << "left working" << endl;
		return rootNode;
	}else if(ptr->data >= rootNode->data){
		
		rootNode->right = insertNode(rootNode->right, ptr);
		ptr->parent = rootNode;
		cout << "right working" << endl;
		return rootNode;
	}
}

void inOrderTraversal(struct node* ptr){
	
	if(ptr == NULL){
		return;
	}
	
	inOrderTraversal(ptr->left);
	cout << ptr->data << "\t";
	inOrderTraversal(ptr->right);
}

int main(){
	
	root = insertNode(root, createNode(5));
	root = insertNode(root, createNode(2));
	root = insertNode(root, createNode(7));
	
	inOrderTraversal(root);
	
	return 0;
}
