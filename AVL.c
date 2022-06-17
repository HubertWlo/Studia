#include<stdio.h>
#include<stdlib.h>

struct Node
{
    int key;
    struct Node *left;
    struct Node *right;
    int bf;
    int height;
};
 
int max(int a, int b);

int height(struct Node *N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

int max(int a, int b)
{
	if(a > b) return a;
	else return b;
}

struct Node* newNode(int key)
{
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return(node);
}

struct Node *rightRotate(struct Node *y)
{
    struct Node *x = y->left;
    struct Node *z = x->right;
 
    // Perform rotation
    x->right = y;
    y->left = z;
 
    // Update heights
    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;
 
    // Return new root
    return x;
}

struct Node *leftRotate(struct Node *x)
{
    struct Node *y = x->right;
    struct Node *z = y->left;

    y->left = x;
    x->right = z;
 
    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;

    return y;
}

int bfAVL(struct Node *N)
{
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

struct Node* insertAVL(struct Node* node, int key)
{
    if (node == NULL)
        return(newNode(key));
 
    if (key < node->key)
        node->left  = insertAVL(node->left, key);
    else if (key > node->key)
        node->right = insertAVL(node->right, key);
    else
        return node;
 
    node->height = 1 + max(height(node->left),height(node->right));
 
    node->bf = bfAVL(node);
 	
 	//Left Left
    if (node->bf > 1 && key < node->left->key)
        return rightRotate(node);
 	//Right Right
    if (node->bf < -1 && key > node->right->key)
        return leftRotate(node);
 
 	//Left Right
    if (node->bf > 1 && key > node->left->key)
    {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }
 
 	//Right Left
    if (node->bf < -1 && key < node->right->key)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
 
    return node;
}

void preOrder(struct Node *root)
{
    if(root == NULL)
    {
        return;
    }
    printf("%d ", root->key);
    preOrder(root->left);
    preOrder(root->right);
}

void inOrder(struct Node *root)
{
    if(root == NULL)
    {
        return;
    }
    preOrder(root->left);
    printf("%d ", root->key);
    preOrder(root->right);
}

void postOrder(struct Node *root)
{
    if(root == NULL)
    {
        return;
    }
    preOrder(root->left);
    preOrder(root->right);
    printf("%d ", root->key);
}

void levelPrint(struct Node* root, int h)
{
	if(h == 1)
	{
		printf("%d ", root->key);
	}
	else if(h > 1 && root != NULL)
	{
		levelPrint(root->left, h - 1);
		levelPrint(root->right, h - 1);
	}
}

void levelOrder(struct Node* root)
{
	int i;
	for(i = 1; i <= root->height; i++)
	{
		levelPrint(root, i);
	}	
} 

void printAVL(struct Node *root, int op)
{
	switch (op)
	{
		case 1:
			inOrder(root);
		break;
		case 2:
			preOrder(root);
		break;
		case 3:
			postOrder(root);
		break;
		case 4:
			levelOrder(root);
		break;
	}
}

struct Node* remAVL(struct Node* root, int key)
{ 
    if (root == NULL)
        return root;

    if ( key < root->key )
        root->left = remAVL(root->left, key);

    else if( key > root->key )
        root->right = remAVL(root->right, key);
 
    else
    {
        // node with only one child or no child
        if( (root->left == NULL) || (root->right == NULL) )
        {
        	struct Node *temp = root->left ? root->left : root->right;
 
            //No child
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else //One child
             *root = *temp;
            free(temp);
        }
        else
        {
            //inorder succesor
            struct Node* temp = root->right;
            while (temp->left != NULL)
        		temp = temp->left;

            root->key = temp->key;

            root->right = remAVL(root->right, temp->key);
        }
    }

    if (root == NULL)
      return root;

    root->height = 1 + max(height(root->left),height(root->right));
 
    root->bf = bfAVL(root);
 
    //Left Left
    if (root->bf > 1 && bfAVL(root->left) >= 0)
        return rightRotate(root);
 
    //Left Right
    if (root->bf > 1 && bfAVL(root->left) < 0)
    {
        root->left =  leftRotate(root->left);
        return rightRotate(root);
    }
 
    //Right Right
    if (root->bf < -1 && bfAVL(root->right) <= 0)
        return leftRotate(root);
 
    //Right Left
    if (root->bf < -1 && bfAVL(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
 
    return root;
}

struct Node* remALL(struct Node* root)
{
	while(root != NULL){
		root = remAVL(root, root->key);
	}
	return root;
}


int main()
{
	int array[100], i;
	for (i = 0; i < 100; i++)
	{
    	array[i] = i;
	}
	
	for (i = 0; i < 100; i++) {    // shuffle array
    	int temp = array[i];
    	int randomIndex = rand() % 100;

    	array[i] = array[randomIndex];
    	array[randomIndex] = temp;
	}
	
  	struct Node *root = NULL;
	
	for(i = 0; i < 6; i++){
		root = insertAVL(root, array[i]);
		printf("%d\n", array[i]);
	}

	preOrder(root);
	printf("\n\n");
	
	root = remAVL(root, array[2]);
	printf("Po usunieciu %d elementu: \n", array[2]);
	inOrder(root);
	printf("\n\n");
	root = remAVL(root, array[0]);
	printf("Po usunieciu %d elementu: \n", array[0]);
	inOrder(root);
	printf("\n\n");
	printf("Wspolczynnik zbalansowania wierzcholka %d\n\n",bfAVL(root));
	
	root = remALL(root);
	if(root == NULL) printf("Usunieto drzewo\n");
 
  return 0;
}

