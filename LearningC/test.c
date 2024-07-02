#include <stdio.h>
#include<stdlib.h>

struct node
{
    int key;
    struct node* left;
    struct node* right;
};

struct node* root;

struct node* new_node(int a)
{
    struct node* new;
    new = (struct node*)malloc(sizeof(struct node));
    new->key = a;
    new->left = NULL;
    new->right = NULL;
    return new;
}
struct node* insert(struct node* root, int key)
{
    if (root == NULL)
    {
        root = new_node(key);
        return root;
    }
    else
    {
        if (key < root->key)
        {
            root->left = insert(root->left, key);
        }
        else
        {
            root->right = insert(root->right, key);
        }
        return root;
    }
}

void inorder(struct node* root)
{
    if (root != NULL)
    {
        inorder(root->left);
        printf("%d-", root->key);
        inorder(root->right);
    }
}

void main()
{
    struct node* root;
    root = NULL;
    int choice, n, n1, n2;
    printf("First Select Insert\n Enter 1\n");
    printf("Insert All value (4 ,9 ,11, 4, 5)\n");
    printf("Then Select 2 ( Inorder ) option");
    do
    {
        printf("\n\t******Main-Menu******");
        printf("\n\t1.Insert \n\t2.Inorder \n\t3.Exit");
        printf("\nEnter Choice: ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            printf("Enter key to be entered: ");
            scanf("%d", &n);
            root = insert(root, n);
            break;
        case 2:
            printf("In-order of Following Tree\n");
            inorder(root);
            break;
        case 3:
            exit(1);
            break;
        default:
            printf("invalid..");
            break;
        }
    } while (1);
}