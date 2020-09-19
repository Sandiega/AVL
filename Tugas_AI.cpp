#include <stdio.h>
#include <stdlib.h>
int flag=0;
struct Tree{
	int key;
	int height;
	Tree *left, *right;
}*root = NULL;

int getMax(int height1, int height2){
	if(height1 > height2){
		return height1;
	}else{
		return height2;
	}
}

int getHeight( Tree *curr ){
	if( curr == NULL){
		return 0;
	}else{
		return curr->height;
	}
}

int getBalanceFactor(Tree *curr){
	if(curr == NULL){
		return 0;
	}else{
		return getHeight(curr->left)-getHeight(curr->right);
	}
}

struct Tree *leftRotation(Tree *curr){
	Tree *child = curr->right;
	Tree *grandChild = child->left;
	
	//child->right = curr;
	child->left = curr;
	curr->right = grandChild;
	
	curr->height = getMax(getHeight(curr->left),getHeight(curr->right))+1;
	child->height = getMax(getHeight(child->left), getHeight(child->right))+1;
	
	return child;
}

struct Tree *rightRotation(Tree *curr){
	Tree *child = curr->left;
	Tree *grandChild = child->right;
	
	child->right = curr;
	curr->left = grandChild;
	
	curr->height = getMax(getHeight(curr->left),getHeight(curr->right))+1;
	child->height = getMax(getHeight(child->left), getHeight(child->right))+1;
	
	return child;
}




struct Tree *insertNode(Tree *curr, int value){
	if(curr == NULL){
		curr = (Tree*) malloc (sizeof(struct Tree));
		curr->key = value;
		curr->height = 1;
		curr->left = curr->right = NULL;
		return curr;
	}
	
	else if(value < curr->key){
		curr->left = insertNode(curr->left, value);
	}
	else if(value > curr->key){
		curr->right = insertNode(curr->right, value);
	}
	
	curr->height = getMax(getHeight(curr->left), getHeight(curr->right))+1;
	int balanceFactor = getBalanceFactor(curr);
	
	if(balanceFactor < -1 && value > curr->right->key){ //RR
		return leftRotation(curr);
	}
	
	if(balanceFactor < -1 && value < curr->right->key){ //RL
		curr->right = rightRotation(curr->right);
		return leftRotation(curr);
		
	}
	
	if(balanceFactor > 1 && value < curr->left->key){ //LL
		return rightRotation(curr);
	}
	
	if(balanceFactor > 1 && value > curr->left->key){ //LR
		curr->left = leftRotation(curr->left);
		return rightRotation(curr);
	}
	return curr;
}

struct Tree *preDecessor(Tree *curr){
	curr = curr->left;
	while(curr->right != NULL){
		curr = curr->right;
	}
	return curr;
}


struct Tree *deleteNode(Tree *curr, int value){
	
	if (curr == NULL){
		return curr;
	}
	else if(value < curr->key){
		curr->left = deleteNode(curr->left, value);
	}
	else if(value > curr->key){
		curr->right = deleteNode(curr->right, value);
	}
	else{ 
		Tree *temp = NULL;
		if(curr->left == NULL || curr->right == NULL){ 
			if(curr->left == NULL){
				temp = curr->right;
			}
			else{
				temp = curr->left;
			}
			
			if(temp == NULL){ 
				temp = curr;
				curr = NULL;
			}else{ 
				*curr = *temp;
			}
			free(temp);
		}
		else{
			temp = preDecessor(curr);
			curr->key = temp->key; 
			curr->left = deleteNode(curr->left, temp->key);
		}
	}
	

	
	if(curr == NULL){
		return curr;
	}
	
	curr->height = getMax(getHeight(curr->left), getHeight(curr->right))+1;
	int balanceFactor = getBalanceFactor(curr);
	
	if(balanceFactor > 1 && getBalanceFactor(curr->left) < 0){ 
	curr->left = leftRotation(curr->left);
	return rightRotation(curr);
	}
	
	if(balanceFactor > 1 && getBalanceFactor(curr->left) > 0){ 
	return rightRotation(curr);
	}
	
	if(balanceFactor < -1 && getBalanceFactor(curr->right) < 0){ 
		return leftRotation(curr);
	}
	 
	if(balanceFactor < -1 && getBalanceFactor(curr->right) > 0){ 
		curr->right = rightRotation(curr->right);
		return leftRotation(curr);
	}
	
	return curr; 
	
}

void print(Tree *curr){
	if(curr!= NULL){
		print(curr->left);
			printf("%d ", curr->key);
		print(curr->right);
	}
}

void cari(Tree *curr,int number){
	if(curr== NULL)return;
	
		cari(curr->left,number);
		if(curr->key==number){
			printf("Found\n");
			flag=1;
			return;
		}
		cari(curr->right,number);
	
}

void menu(){
	print(root);
	printf("\nMenu\n");
	printf("===========\n");
	printf("Insert Key\n");
}



int main(){
	int inputNumber;
	root=insertNode(root,12);
	root=insertNode(root,13);
	root=insertNode(root,15);
	root=insertNode(root,16);
	root=insertNode(root,17);
	root=insertNode(root,14);
	root=insertNode(root,18);
	root=insertNode(root,19);
	menu();
	scanf("%d",&inputNumber);
	getchar();
	cari(root,inputNumber);
	if(flag==0){
		printf("Not Found\n");
	}
	return 0;
}

