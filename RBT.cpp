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

//rotate around nodes
//void leftRotateAbout(node* thisNode, node* aboutNode){
//	
//	node* thisNodeLeft = thisNode->left;
//	thisNode->parent = aboutNode->parent;
//	thisNode->left = aboutNode;
//	thisNode->parent->right = thisNode;
//	thisNode->left->right = thisNodeLeft;
//}

//Delete nodes
void deleteNode(){
	
	struct node* ptr = findLeftMost(root);
	struct node* parentPtr = ptr->parent;
	struct node* siblingPtr = NULL;
	
	if(ptr != NULL){
		//Case A - left side deleting
		siblingPtr = parentPtr->right;
		
		if(ptr->color ==  red){
			//red node deletion - nothing more required
			parentPtr->left = NULL;
			delete(ptr);
		}else{
			//black node deletion - forms another  case
			if(siblingPtr->color == red){
				//deletion case 1
				delete(parentPtr->left);
				parentPtr->left = NULL;
				swap(parentPtr->color, siblingPtr->color);
				/*left rotate sibling around parent*/ 
				leftRotate(root, siblingPtr->parent);
			}else{
				//sibling is black - then check sibling's childern
				if(siblingPtr->left == NULL && siblingPtr->right->color == red){
					//deletion case 4
					delete(parentPtr->left);
					parentPtr->left = NULL;
					swap(parentPtr->color, siblingPtr->color);
					/*left rotation of w around p[x] */
					leftRotate(root, siblingPtr->parent);
				}
//				if((siblingPtr->left == NULL && siblingPtr->right == NULL) || (siblingPtr->left->color == black && siblingPtr->right->color == black)){
//					//deletion case 2
//					cout << "not implemented yet!" << endl;
//				}
				if(siblingPtr->left->color == red && (siblingPtr->right->color == black || siblingPtr->right == NULL)){
			 		//deletion case 3
			 		delete(parentPtr->left);
					parentPtr->left = NULL;
					swap(siblingPtr->left->color, siblingPtr->color);
					/* right rotate left[w] around w*/
					rightRotate(siblingPtr, siblingPtr);
				}
				
//				if(siblingPtr->right->color == red && siblingPtr->left == NULL){
//					
//				}
			}
		} 
	}
}


int main(){
	
	insert(5);
	insert(3);
	insert(7);
	insert(6);
	insert(2);
	insert(1);
	insert(4);
	
//	cout << "Left most element " << findLeftMost(root)->data << endl;
	
	deleteNode();
	deleteNode();
//	deleteNode(6);
	
	inOrderTraversal(root);
	
	cout << endl;
	
	cout << "root-left-left-data " << root->left->left->data << endl;
	
	return 0;
}
