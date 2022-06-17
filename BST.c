#include <stdio.h>
#include <stdlib.h>

struct node {
    int key;
    struct node* left, * right;
};

struct node* newNode(int item)
{
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}

void inOrder(struct node* root)
{
    if (root != NULL) {
        inOrder(root->left);
        printf("%d ", root->key);
        inOrder(root->right);
    }
}

void preOrder(struct node* root)
{
    if (root != NULL) {
        printf("%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}

void postOrder(struct node* root)
{
    if (root != NULL) {
        postOrder(root->left);
        postOrder(root->right);
        printf("%d ", root->key);
    }
}

void level(struct node* root, int h)
{
    if (h == 1)
    {
        printf("%d ", root->key);
    }
    else if (h > 1 && root != NULL)
    {
        level(root->left, h - 1);
        level(root->right, h - 1);
    }
}

void levelOrder(struct node* root)
{
    int i, h = hBST(root);
    for (i = 1; i <= h; i++)
    {
        level(root, i);
    }
}

int countLevBST(struct node* root, int lev) 
{
	if (root == 0)
	{
		return 0;
	}
    if (lev == 1)
    {
        return 1;
    }
    return countLevBST(root->left, lev - 1) + countLevBST(root->right, lev - 1);
}

struct node* insertBST(struct node* node, int key)
{
    if (node == NULL)
    {
        return newNode(key);
    }
    if (key < node->key)
    {
        node->left = insertBST(node->left, key);
    }
    else if (key > node->key)
    {
        node->right = insertBST(node->right, key);
    }
    return node;
}

void printBST(struct node* root, int op)
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

int hBST(struct node* root)
{
    if (root != NULL)
    {
        int heightl = hBST(root->left);
        int heightr = hBST(root->left);

        if (heightl > heightr)
        {
            return heightl + 1;
        }
        else
        {
            return heightr + 1;
        }
    }
}

void transBST(struct node* root, struct node* root_d)
{
    if (root_d != NULL) {
        transBST(root, root_d->left);
        transBST(root, root_d->right);
		insertBST(root, root_d->key);
    }
}

struct node* removeBST(struct node* root, int key)
{
    if (key < root->key)
        root->left = removeBST(root->left, key);

    else if (key > root->key)
        root->right = removeBST(root->right, key);

    else {
        if (root->left == NULL) {
            struct node* temp = root->right;
            free(root);
            return temp;
        }
        else if (root->right == NULL) {
            struct node* temp = root->left;
            free(root);
            return temp;
        }

        struct node* temp = root->right;

        while (temp != NULL && temp->left != NULL)
            temp = temp->left;

        root->key = temp->key;

        root->right = removeBST(root->right, temp->key);
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
	
	for (i = 0; i < 100; i++) {
    	int temp = array[i];
    	int randomIndex = rand() % 100;

    	array[i] = array[randomIndex];
    	array[randomIndex] = temp;
	}
    
    struct node* root = NULL;
    root = insertBST(root, array[0]);
    printf("%d \n", array[0]);
    for(i = 1; i < 7; i++){
    	insertBST(root, array[i]);
    	printf("%d \n", array[i]);
	}
	
	printf("Pierwsze drzewo:\n");
    inOrder(root); printf("\n");
    
    printf("Po usunieciu elementu %d \n", array[3]);
    removeBST(root, array[3]);
    inOrder(root); printf("\n");

	printf("Elementy na 4 poziomie: \n");
    printf("%d \n", countLevBST(root, 4));

    struct node* root_d = NULL;
    for(i = 7; i < 12; i++){
	    root_d = insertBST(root_d, array[7]);
	    insertBST(root_d, array[8]);
	    insertBST(root_d, array[9]);
	    insertBST(root_d, array[10]);
	    insertBST(root_d, array[11]);
	}
	
	printf("Drugie drzewo:\n");
    inOrder(root_d);

    transBST(root, root_d);

    printf("\n\n\n");

	printf("Po zlaczeniu drzew:\n");
    inOrder(root);

    removeBST(root, array[4]);

    printf("\n");
	
	printf("Po usunieciu %d elementu:\n", array[4]);
    inOrder(root);


    return 0;
}


