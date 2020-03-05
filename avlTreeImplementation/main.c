#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>

int isAvailable = 0;

struct node{

    int data;
    struct node* left;
    struct node* right;
    int height;
};

int height(struct node* nodet){
    if(nodet == NULL){
        return 0;
    }

    return nodet->height;
}

int findMax(int a, int b){

    if(a>b){
        return a;
    }else{
        return b;
    }
}

struct node* newNode(int data){

    struct node* newOne = (struct node*)malloc(sizeof(struct node));

    newOne->data = data;
    newOne->left = NULL;
    newOne->right = NULL;
    newOne->height = 1;

    return newOne;
}

struct node* rotateRight(struct node* sRoot){

    struct node* x = sRoot->left;
    struct node* y = x->right;

    x->right = sRoot;
    sRoot->left = y;

    x->height = findMax(height(x->left), height(x->right)) + 1;
    sRoot->height = findMax(height(sRoot->left), height(sRoot->right)) + 1;

    return x;
}

struct node* rotateLeft(struct node* sRoot){

    struct node* x = sRoot->right;
    struct node* y = x->left;

    x->left = sRoot;
    sRoot->right = y;

    x->height = findMax(height(x->left), height(x->right)) + 1;
    sRoot->height = findMax(height(sRoot->left), height(sRoot->right)) + 1;

    return x;
}

int getBalanceFactor(struct node* noder){

    if(noder == NULL){
        return 0;
    }

    return (height(noder->left) - height(noder->right));
}

struct node* insertData(struct node* noder, int data){

    if(noder == NULL){
        return (newNode(data));
    }

    if(data < noder->data){
        noder->left = insertData(noder->left, data);
    }else if(data > noder->data){
        noder->right = insertData(noder->right, data);
    }else{
        return noder;
    }

    noder->height = findMax(height(noder->left), height(noder->right)) + 1;

    int balFactor = getBalanceFactor(noder);

    if(balFactor > 1 && data < noder->left->data){
        return rotateRight(noder);
    }

    if(balFactor < -1 && data > noder->right->data){
        return rotateLeft(noder);
    }

    if(balFactor > 1 && data > noder->left->data){
        noder->left = rotateLeft(noder->left);
        return rotateRight(noder);
    }

    if(balFactor < -1 && data < noder->right->data){
        noder->right = rotateRight(noder->right);
        return rotateLeft(noder);
    }

    return noder;
}

void preOrder(struct node* noder, int data){

    if(noder != NULL){

        if(noder->data == data){
            isAvailable = 1;
        }
        preOrder(noder->left, data);
        preOrder(noder->right, data);
    }
}


int main(){

    int setA[] = {12,34,11,9,3};
    int setB[] = {2,5,1,3};

    struct node* root = NULL;

    int i;
    for(i=0; i<(sizeof(setA)/4); i++){
        root = insertData(root, setA[i]);
    }

    int flag = 1;

    for(i=0; i<(sizeof(setB)/4); i++){


        preOrder(root, setB[i]);

        if(isAvailable == 1){
            flag = 0;
            break;
        }else{
            flag = 1;
        }
    }

    if(flag == 0){
        printf("False\n");
    }else{
        printf("True\n");
    }

    return 0;
}
