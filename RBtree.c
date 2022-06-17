#include <stdio.h>
#include <stdlib.h>

int n = 6, i;
int a[6][2];

struct node 
{
	int value[2];
	int color; // -1 red 0 black
	int max;
	struct node* parent;
	struct node* right;
	struct node* left;
};

struct node* findNode(struct node* node, int left)
{
	if(node == NULL){
		return NULL;
	}
	if(node->value[0] == left){
		return node;
	}
	if(node->value[0] < left){
		findNode(node->right, left);
	}
	else{
		findNode(node->left, left);
	}
}

void findMax(struct node* root, struct node* node, int localMax)
{
	if (node == NULL) {
		return;
	}
	if (localMax < node->value[1]){
		localMax = node->value[1];
		root->max = localMax;
	}
	findMax(root, node->left, localMax);
	findMax(root, node->right, localMax);
}

struct node* root = NULL;

void leftRotate(struct node* node)
{
	struct node* Right = node->right;
	node->right = Right->left;
	if(node->right == NULL){
		node->right->parent = node;
	}
	Right->parent = node->parent;
	if(node->parent != NULL){
		root = Right;
	}
	else if(node == node->parent->left){
		node->parent->left = Right;
	}
	else{
		node->parent->right = Right;
	}
	Right->left = node;
	node->parent = Right;
}

void rightRotate(struct node* node)
{
	struct node* Left = node->left;
	node->left = Left->right;
	if(node->left == NULL){
		node->left->parent = node;
	}
	Left->parent = node->parent;
	if(node->parent != NULL){
		root = Left;
	}
	else if(node == node->parent->right){
		node->parent->right = Left;
	}
	else{
		node->parent->left = Left;
	}
	Left->right = node;
	node->parent = Left;
}

struct node* insertRB(struct node* root, struct node* node)
{
	if(root == NULL){
		return node;
	}
	
	if(node->value[0] < root->value[0]){
		root->left = insertRB(root->left, node);
		root->left->parent = root;
	}
	else if(node->value[0] > root->value[0]){
		root->right = insertRB(root->right, node);
		root->right->parent = root;
	}
	
	return root;
}

void format(struct node* root, struct node* node)
{
	struct node* Parent = NULL;
	struct node* grandParent = NULL;
	
	while(node != root && node->color != 0 && node->parent->color == -1){
		Parent = node->parent;
		grandParent = node->parent->parent;
		
		if(Parent == grandParent->left){				//parent - left child grandPa
			struct node* uncle = grandParent->right;		
			if(uncle != NULL && Parent->color == -1){		//uncle - red
				grandParent->color = -1;
				Parent->color = 0;
				uncle->color = 0;
				node = grandParent;
			}
			
			else{											
				if(node == Parent->right){					//node - right child
					leftRotate(Parent);
					node = Parent;
					Parent = node->parent;
				}
				
				rightRotate(grandParent);					//node - left child
				int pom = Parent->color;
				Parent->color = grandParent->color;
				grandParent->color = pom;
				node = Parent;
			}	
		}
		else{											//parent - right child grandPa
			struct node* uncle = grandParent->left;
			if(uncle != NULL && Parent->color == -1){		//uncle - red
				grandParent->color = -1;
				Parent->color = 0;
				uncle->color = 0;
				node = grandParent;
			}
			else{
				if(node == Parent->left){					//node - left child
					rightRotate(grandParent);
					node = Parent;
					Parent = node->parent;
				}
				leftRotate(grandParent);					//node - right child
				int pom = Parent->color;
				Parent->color = grandParent->color;
				grandParent->color = pom;
				node = Parent;
			}
		}
	}
	root->color = 0;
}

void preOrder(struct node* root)
{
    if (root == NULL) return;
    printf("[%d, %d], %d\n", root->value[0], root->value[1], root->color);
    preOrder(root->left);
    preOrder(root->right);
}

void inOrder(struct node* root)
{
    if (root == NULL) return;
    inOrder(root->left);
    printf("[%d, %d], %d, %d\n", root->value[0], root->value[1], root->max, root->color);
    inOrder(root->right);
}

void postOrder(struct node* root)
{
    if (root == NULL) return;
    postOrder(root->left);
    postOrder(root->right);
    printf("[%d, %d], %d, %d\n", root->value[0], root->value[1], root->max, root->color);
}

struct node* delRB(struct node* root, int left)
{
	struct node* rootn = NULL;
	for(i = 0; i < n; i++){
		if(a[i][0] != left && a[i][0] != -1){
			struct node* temp = (struct node*)malloc(sizeof(struct node));
			temp->right = NULL;
    		temp->left = NULL;
 		   	temp->parent = NULL;
 		   	temp->value[0] = a[i][0];
 		   	temp->value[1] = a[i][1];
 		   	temp->color = -1;
 		   	temp->max = 0;
 		   	
 		   	rootn = insertRB(rootn, temp);
 		   	
 		   	format(rootn, temp);
 		   	rootn->color = 0;
		}
		else a[i][0] = -1;
	}
	if(rootn != NULL){
		for (i = 0; i < n; i++) {
			if(a[i][0] != left){
    			findMax(findNode(rootn, a[i][0]), findNode(rootn, a[i][0]), 0);
    		}
		}	
	}
	return rootn;
}

struct node* delBRinter(struct node* root)
{
	struct node* rootn = NULL;
	int j, k = 0, temp[n];
	for(i = 0; i < n; i++){
		for(j = 0; j < n; j++){
			if(i != j){
				if((a[i][0] <= a[j][0] && a[i][1] >= a[j][1])||(a[i][0] <= a[j][0] && a[i][1] <= a[j][1])
				|| (a[i][0] >= a[j][0] && a[i][1] >= a[j][1])||(a[i][0] >= a[j][0] && a[i][1] <= a[j][1])){
					temp[k] = a[i][0];
					k++;
					break;
				}
			}
		}
	}
	k = 0;
	for(i = 0; i < n; i++){
		if(temp[k] == a[i][0]){
			printf("usun %d", a[i][0]);
			rootn = delRB(root, a[i][0]);
		} 
		else{
			k++;
		}
	}
	return root;
}

struct node* findRB(struct node* root, int number)
{
	if(root == NULL) return NULL;
	if(root != NULL){
		if(root->value[0] <= number && root->value[1] >= number){
			return root;
		}
		if(root->left->max > number){
			findRB(root->left, number);
		}
			else{
		findRB(root->right, number);
		}
	}
}

struct node* find(struct node* root, int number)
{
	if(root == NULL) return NULL;
	else{
		if(root->value[0] == number) return root;
		if(root->value[0] > number) return find(root->left, number);
		else return find(root->right, number);
	}
}

void print(struct node* root, int num[2])
{
	if(root == NULL) return;
	if(((root->value[0] <= num[0] && root->value[1] >= num[1])||(root->value[0] <= num[0] && root->value[1] <= num[1])
	 || (root->value[0] >= num[0] && root->value[1] >= num[1])||(root->value[0] >= num[0] && root->value[1] <= num[1]))){
		if(num[0] != root->value[0])
		{
			printf("node = %d, value <%d, %d> \n", root, root->value[0], root->value[1]);
		}
	}
	print(root->right, num);
	print(root->left, num);
}

void interRB(struct node* root, int num)
{
	int temp[2] = {findNode(root, num)->value[0], findNode(root, num)->value[1]};
	print(root, temp);
}

int main()
{ 
	for(i = 0; i < n; i++)
	{
		int randomIndexOne = rand() % 300;
		int randomIndexTwo = rand() % 300;
		if(randomIndexOne < randomIndexTwo){
			a[i][0] = randomIndexOne;
			a[i][1] = randomIndexTwo;
		}
		else{
			a[i][0] = randomIndexTwo;
			a[i][1] = randomIndexOne;
		}
	}
	
	printf("Wygenerowano: \n");
	for(i = 0; i < n; i++){
		printf("<%d, %d> \n", a[i][0], a[i][1]);
	}	
	
    for (i = 0; i < n; i++) {
        struct node* temp = (struct node*)malloc(sizeof(struct node));
        temp->right = NULL;
        temp->left = NULL;
        temp->parent = NULL;
        temp->value[0] = a[i][0];
        temp->value[1] = a[i][1];
        temp->color = -1;
        temp->max = 0;
 		
 		root = insertRB(root, temp);
        
        format(root, temp);
    }
	
    for (i = 0; i < n; i++) {
    	findMax(findNode(root, a[i][0]), findNode(root, a[i][0]), 0);
	}    

    postOrder(root);
 	printf("\n\n");
 	
 	printf("Usunieto node o kluczu %d\n", a[3][0]);
 	root = delRB(root, a[3][0]);
 	postOrder(root);
 	printf("\n\n");
 	
 	if(findRB(root, 20) != NULL){
 		printf("Znaleziono node majaca w przedziale 20\n");
 		printf("node = %d, value <%d, %d>\n", findRB(root, 20), findRB(root, 20)->value[0], findRB(root, 20)->value[1]);
	}
 	printf("\n\n");
 	
 	printf("Przedzialy nachodzace na node o kluczu %d\n", a[4][0]);
 	interRB(root, a[4][0]);
 	 	
    return 0;
}
