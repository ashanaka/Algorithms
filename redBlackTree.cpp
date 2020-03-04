#include<iostream>

using namespace std;

enum Color {
	red,
	black
};

//process structure
struct process{
	int burstTime;
	int v_runTime;
	char name;
	
	process(int burstTime, char name){
		this->burstTime = burstTime;
		this->name = name;
		this->v_runTime = 0;
	}
};

//node structure
struct node{
	int val;
	node* left;
	node* right;
	node* parent;
	bool color;
	
	node(int val){
		this->val = val;
		this->left = NULL;
		this->right = NULL;
		this->parent = NULL;
		this->color = red;
	}
};

//root node
node* root = NULL;

//rotate left
void rotateLeft(node *&rootNode, node *&ptr) 
{ 
	node *rightPtr = ptr->right; 

	ptr->right = rightPtr->left; 

	if (ptr->right != NULL) {
		ptr->right->parent = ptr; 
	}

	rightPtr->parent = ptr->parent; 

	if (ptr->parent == NULL) {
		rootNode = rightPtr; 
	}

	else if (ptr == ptr->parent->left) {
		ptr->parent->left = rightPtr; 
	}

	else{
		ptr->parent->right = rightPtr; 
	}

	rightPtr->left = ptr; 
	ptr->parent = rightPtr; 
}
//left rotate operation
void leftRotate(node*& rootNode, node*& x){
	
	node* y = x->right;
	x->right = y->left;
	
	if(y->left != NULL){
		y->left->parent = x;
	}
	y->parent = x->parent;
	
	if(x->parent == NULL){
		root = y;
	}else{
		if(x == x->parent->left){
			x->parent->left = y;
		}else{
			x->parent->right = y;
		}
		y->left = x;
		x->parent = y;
	}
}
//rotate right
void rotateRight(node *&rootNode, node *&ptr) { 
	node *leftPtr = ptr->left; 

	ptr->left = leftPtr->right; 

	if (ptr->left != NULL){
		ptr->left->parent = ptr; 
	} 

	leftPtr->parent = ptr->parent; 

	if (ptr->parent == NULL){
		rootNode = leftPtr; 
	} 

	else if (ptr == ptr->parent->left) {
		ptr->parent->left = leftPtr; 
	}

	else{
		ptr->parent->right = leftPtr; 
	}

	leftPtr->right = ptr; 
	ptr->parent = leftPtr; 
}
//right rotate operation
void rightRotate(node*& rootNode, node*& x){
	
	node* y = x->left;
	x->left = y->right;
	
	if(y->right != NULL){
		y->right->parent = x;
	}
	y->parent = x->parent;
	
	if(x->parent == NULL){
		root = y;
	}else{
		if(x == x->parent->right){
			x->parent->right = y;
		}else{
			x->parent->left = y;
		}
		y->right = x;
		x->parent = y;
	}
}

//fixed-up function
void fixedUp(node* rootNode, node* z){
	
//	if(z->parent != NULL){
		while(z != rootNode && z->parent->color == red && z->color != black ){
			node* y = NULL;
			if(z->parent == z->parent->parent->left){
				 y = z->parent->parent->right;
				if(y->color == red){
					z->parent->color = black;
					y->color = black;
					z->parent->parent->color = red;
					z = z->parent->parent;
				}
			}else if(z = z->parent->right){
				cout << "else if part" << endl;
				z = z->parent;
				leftRotate(rootNode, z);
				z->parent->color = black;
				z->parent->parent->color = red;
				rightRotate(rootNode, z->parent->parent);
			}else{
				/* same as then clause with "right" and "left" exchanged */
				cout << "correct part for 6" << endl;
				z = z->parent;
				rightRotate(rootNode, z);
//				rotateRight(rootNode, z->parent);
				cout << "rotation done" << endl;
				z->parent->color = black;
				z->parent->parent->color = red;
				leftRotate(rootNode, z->parent->parent);
//				rotateLeft(rootNode, z->parent->parent->parent);
			}
		}
//		rootNode->color = black;
//	}else{
//		cout << "else part" << endl;
		rootNode->color = black;
//	}
	
}

//insert into RBT
void insert(node* rootNode, node* z){
	
	node* y = NULL;
	node* x = rootNode;
	
	while(x != NULL){
		y = x;
		if(z->val < x->val){
			x = x->left;
		}else{
			x = x->right;
		}
	}
	
	z->parent = y;
	
	if(y == NULL){
		root = z;
	}else if(z->val < y->val){
		y->left = z;
	}else{
		y->right = z;
	}
	
	z->left = NULL;
	z->right = NULL;
	z->color = red;
	
	fixedUp(root, z);
}

//create node
void createNode(int val){
	
	node* newNode = new node(val);
	
	insert(root, newNode);
}
int main(){
	
	createNode(5);
	createNode(3);
	createNode(7);
	createNode(8);
	createNode(1);

//	rightRotate(root, root->right);
	
	cout << root->right->left->color << endl;
	cout << root->left->color << " " << root->right->color;
	
	return 0;
}
