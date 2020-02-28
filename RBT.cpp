#include<iostream>
#include<stdlib.h>

using namespace std;

struct node{
	
	struct node* right;
	struct node* left;
	struct node* parent;
	int red;
	int black;
	int doubleBlack;
	int data;
};

struct node* root = NULL;

//create a new node
struct node* createNode(int data){
	
	struct node* newNode  = (struct node*)malloc(sizeof(struct node));
	newNode->black = 0;
	newNode->red = 1;
	newNode->doubleBlack = 0;
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->parent = NULL;
	newNode->data = data;
	
	return newNode;
}

//insert node
struct node* insertNode(struct node* rootNode, struct node* ptr){
	
	if(rootNode == NULL){
		if(root == NULL){
			root->black = 1;
			root->red = 0;
		}
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

void fixViolation(struct node *&rootNode, struct node *&pt) 
{ 
    node *parent_pt = NULL; 
    node *grand_parent_pt = NULL; 
  
    while ((pt != rootNode) && (pt->black != 1) && 
           (pt->parent->red == 1)) 
    { 
  
        parent_pt = pt->parent; 
        grand_parent_pt = pt->parent->parent; 
  
        /*  Case : A 
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
                parent_pt->black = 1; 
                uncle_pt->black = 1; 
                pt = grand_parent_pt; 
            } 
  
            else
            { 
                /* Case : 2 
                   pt is right child of its parent 
                   Left-rotation required */
                if (pt == parent_pt->right) 
                { 
                    rotateLeft(root, parent_pt); 
                    pt = parent_pt; 
                    parent_pt = pt->parent; 
                } 
  
                /* Case : 3 
                   pt is left child of its parent 
                   Right-rotation required */
                rotateRight(root, grand_parent_pt); 
                swap(parent_pt->color, grand_parent_pt->color); 
                pt = parent_pt; 
            } 
        } 
  
        /* Case : B 
           Parent of pt is right child of Grand-parent of pt */
        else
        { 
            Node *uncle_pt = grand_parent_pt->left; 
  
            /*  Case : 1 
                The uncle of pt is also red 
                Only Recoloring required */
            if ((uncle_pt != NULL) && (uncle_pt->red == 1)) 
            { 
                grand_parent_pt->red = 1; 
                parent_pt->black = 1; 
                uncle_pt->black = 1; 
                pt = grand_parent_pt; 
            } 
            else
            { 
                /* Case : 2 
                   pt is left child of its parent 
                   Right-rotation required */
                if (pt == parent_pt->left) 
                { 
                    rotateRight(root, parent_pt); 
                    pt = parent_pt; 
                    parent_pt = pt->parent; 
                } 
  
                /* Case : 3 
                   pt is right child of its parent 
                   Left-rotation required */
                rotateLeft(root, grand_parent_pt); 
                swap(parent_pt->color, grand_parent_pt->color); 
                pt = parent_pt; 
            } 
        } 
    } 
  
    root->black = 1; 
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
