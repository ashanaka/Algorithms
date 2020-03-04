#include<iostream>

using namespace std;

enum Color {red, black, doubleBlack, redBlack};

struct node{
	
	struct node* right;
	struct node* left;
	struct node* parent;
	bool color;
	int data;
	
	node(int data){
		
		this->data = data;
		this->color = red;
		this->left = NULL;
		this->right = NULL;
		this->parent = NULL;
	}
};

struct node* root = NULL;


//rotate right
void rightRotate(node *&rootNode, node *&ptr) { 
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

//rotate left
void leftRotate(node *&rootNode, node *&ptr) 
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

//check for violences
void arrangeNodes(node *&rootNode, node *&ptr) { 
	node *parentPtr = NULL; 
	node *grandParentPtr = NULL; 
	
	while (ptr != rootNode && ptr->color != black && ptr->parent->color == red) { 

		parentPtr = ptr->parent; 
		grandParentPtr = ptr->parent->parent; 

		//Case A
		if (parentPtr == grandParentPtr->left){ 

			node *unclePtr = grandParentPtr->right; 

			//Case 1
			if (unclePtr != NULL && unclePtr->color == red){ 

				grandParentPtr->color = red; 
				parentPtr->color = black; 
				unclePtr->color = black; 
				ptr = grandParentPtr; 
			} 

			else{ 
				//Case2
				if (ptr == parentPtr->right){ 
					leftRotate(rootNode, parentPtr); 
					ptr = parentPtr; 
					parentPtr = ptr->parent; 
				} 
				//Case 3
				rightRotate(rootNode, grandParentPtr); 
				swap(parentPtr->color, grandParentPtr->color); 
				ptr = parentPtr; 
			} 
		} 

		//Case B
		else{ 
			node *unclePtr = grandParentPtr->left; 

			//Case 1
			if ((unclePtr != NULL) && (unclePtr->color == red)){ 

				grandParentPtr->color = red; 
				parentPtr->color = black; 
				unclePtr->color = black; 
				ptr = grandParentPtr; 
			} 
			else{ 
				//Case 2
				if (ptr == parentPtr->left){ 
					rightRotate(rootNode, parentPtr); 
					ptr = parentPtr; 
					parentPtr = ptr->parent; 
				} 

				//Case 3
				leftRotate(rootNode, grandParentPtr); 
				swap(parentPtr->color, grandParentPtr->color); 
				ptr = parentPtr; 
			} 
		} 
	} 

	rootNode->color = black; 
} 

//insert node and connect to the parent
node* insertNode(struct node* rootNode, struct node* ptr){

	if(rootNode == NULL){
		
		return ptr;
	}
	
	if(ptr->data < rootNode->data){
		
		rootNode->left = insertNode(rootNode->left, ptr);
		rootNode->left->parent = rootNode;
	}else if(ptr->data >= rootNode->data){
		
		rootNode->right = insertNode(rootNode->right, ptr);
		rootNode->right->parent = rootNode;
	}
	return rootNode;
}

//Insert the node into the RBT
void insert(int data){
	
	node *newNode = new node(data);
	
	root = insertNode(root, newNode);
	
	arrangeNodes(root, newNode);
}

//Inorder traversal
void inOrderTraversal(struct node* ptr){
	
	if(ptr == NULL){
		return;
	}
	
	inOrderTraversal(ptr->left);
	cout << ptr->data << "\t";
	inOrderTraversal(ptr->right);
}

//search for data
node* searchNode(node* rootNode, int data){
	
	if(rootNode == NULL){
		cout << "Not found!" << endl;
		return root;
	}
	
	if(rootNode->data == data){
		cout << "Found " << rootNode->data << endl;
		return rootNode;
	}else if(rootNode->data > data){
		return searchNode(rootNode->left, data);
	}else{
		return searchNode(rootNode->right, data);
	}
}

//find right most
node* findRightMost(node* rootNode){
	
	if(rootNode->right == NULL){
		return rootNode;
	}else{
		return findRightMost(rootNode->right);
	}
}

//find left most
node* findLeftMost(node* rootNode){
	
	if(rootNode->left == NULL){
		return rootNode;
	}else{
		return findLeftMost(rootNode->left);
	}
}

//======================================DELETION=============================

node* successor(node*& rootNode)
{
      node *k=NULL;
     if(rootNode->left!=NULL)
     {
         k=rootNode->left;
         while(k->right!=NULL)
              k=k->right;
     }
     else
     {
         k=rootNode->right;
         while(k->left!=NULL)
              k=k->left;
     }
     return k;

}

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

//rbt deletion fix-up
void rbtDeleteFix(node*& rootNode, node*& x, int isLeft){
	
	
	while(x!= root && x->color == black){
		node* w = NULL;
		if(isLeft == 1){
			w = x->parent->right;
			if(w->color == red){
				w->color = black;
				x->parent->color = red;
				rotateLeft(rootNode, x->parent);
				w = x->parent->right;
			}	
		}
		
		if ((w->left == NULL && w->right == NULL) ||
                ((w->left != NULL && w->left->color == black) &&
                 (w->right != NULL && w->right->color == black))) {
                w->color = red;
                if (x->parent->color == red) {
                    x->parent->color = black;
                    x = root; // parent is red black and fixing ends
                } else {
                    x = x->parent;
                }
            }
                //case 2 //
                //case 3 :
            else if (w->right == NULL ||
                     (w->right != NULL && w->right->color == black)) {
                w->left->color = black;
                w->color = red;
                rightRotate(rootNode, w);
                w = x->right;
            }
                //case 3 //
                //case 4 :
            else if (w->right->color == red) {
                w->color = x->parent->color;
                x->parent->color = black;
                w->right->color = black;
                leftRotate(rootNode, x->parent);
                x = root; //terminating case -- hence node is root and ends up the while loop
            }
            //case 4 //
            else {
            w = x->parent->left;
            //case 1 :
            if (w->color == red) {
                w->color = black;
                x->parent->color = red;
                rightRotate(rootNode, x->parent);
                w = x->parent->left;
            }
            //case 1 //
            //case 2 :
            if ((w->left == NULL && w->right == NULL) ||
                ((w->left != NULL && w->left->color == black) &&
                 (w->right != NULL && w->right->color == black))) {
        		w->color = red;
                if (x->parent->color == red) {
                    x->parent->color = black;
                    x = root; // parent is red black and fixing ends
                } else {
                    x = x->parent;
                }
            }
                //case 2 //
                //case 3 :
            else if (w->left == NULL ||
                     (w->left != NULL && w->left->color == black)) {
                w->right->color = black;
                w->color = red;
                rightRotate(rootNode, w);
                w = x->left;
            }
                //case 3 //
                //case 4 :
            else if (w->left->color == red) {
                w->color = x->parent->color;
                x->parent->color = black;
                w->left->color = black;
                rightRotate(rootNode, x->parent);
                x = root;
            }
            //case 4 //
        }
		x->color = black;
        } 
	
}

//delet rbt
node* rbDelete(node*& rootNode, node*& z){
	
	node* y = NULL;
	node* x = NULL;
	
	if(z == rootNode){
		cout << "Root deleted!" << endl;
		root = NULL;
		return z;
	}
	
	if(z->left == NULL || z->right == NULL){
		y = z;
	}else{
		y = successor(z);
	}
	
	if(y->left != NULL){
		x = y->left;
		x->parent = y->parent;
	}else{
		if(y->right != NULL){
			x = y->right;
			x->parent = y->parent;
		}
	}
	
	bool isLeft = 0;
	
	if(y->parent == NULL){
		rootNode = x;
	}else if(y == y->parent->left){
		y->parent->left = x;
		isLeft = 1;
	}else{
		y->parent->right = x;
	}
	
	if(y != z){
		z->data = y->data;
	}
	
	if(y->color == black){
		//delete fix-up
		rbtDeleteFix(rootNode, z, isLeft);
	}
	
	return y;
}



int main(){
	
	insert(5);
	insert(3);
	insert(7);
	insert(6);
	insert(2);
	insert(1);
	insert(4);
	


	node* temp = findLeftMost(root);
	rbDelete(root, temp);
	temp = findLeftMost(root);
	rbDelete(root, temp);
	temp = findLeftMost(root);
	rbDelete(root, temp);
	temp = findLeftMost(root);
	rbDelete(root, temp);
	temp = findLeftMost(root);
	rbDelete(root, temp);
	
	
	cout << root->data << endl;
	
	temp = findLeftMost(root);
	rbDelete(root, temp);
	
	
	
//	temp = findLeftMost(root);
//	cout << temp->data << endl;

	
	return 0;
}
