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

//insert into RBT
void insert(node* rootNode, node* z){
	
	node* y = NULL;
	node* x = rootNode;
	
	while(x != NULL){
		y = x;
		if(z->val < x->val){
			
		}
	}
}

int main(){
	
	return 0;
}
