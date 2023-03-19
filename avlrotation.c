#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    struct node *left;
    struct node *right;
    int data;
    int height;
} node;

node *createnode(int d)
{
    node *n = (node *)malloc(sizeof(node));
    n->data = d;
    n->left = NULL;
    n->right = NULL;
    n->height = 1;
    return (n);
}

int max(int a, int b)
{
    if (a > b)
        return (a);
    else
        return (b);
}
int getheight(node *root)
{
    if (root == NULL)
        return 0;

    return root->height;
}

int balancefactor(node *root)
{
    if (root == NULL)
        return (0);

    return (getheight(root->left) - getheight(root->right));
}

node *rightrotate(node *y)
{
    node *x = y->left;
    node *t2 = x->right;

    x->right = y;
    y->left = t2;

    y->height = max(getheight(y->left), getheight(y->right)) + 1;
    x->height = max(getheight(x->left), getheight(x->right)) + 1;

    return (x);
}

node *leftrotate(node *x)
{
    node *y = x->right;
    node *t2 = y->left;

    y->left = x;
    x->right = t2;

    y->height = max(getheight(y->left), getheight(y->right)) + 1;
    x->height = max(getheight(x->left), getheight(x->right)) + 1;

    return (y);
}

node *insert(node *root, int key)
{
    if (root == NULL)
    {
        return (createnode(key));
    }

    if (key > root->data)
    {
        root->right = insert(root->right, key);
    }
    else
    {
        root->left = insert(root->left, key);
    }

    root->height = max(getheight(root->left), getheight(root->right)) + 1;
    int bf = balancefactor(root);

    // l-l insertion//
    if (bf > 1 && key < root->left->data)
    {
        return rightrotate(root);
    }
    else if (bf < -1 && key > root->right->data)
    {
        return leftrotate(root);
    }
    // l-r
    if (bf > 1 && key > root->left->data)
    {
        root->left = leftrotate(root->left);
        return rightrotate(root);
    }
    // r-L
    if (bf < -1 && key < root->right->data)
    {
        root->right = rightrotate(root->right);
        return leftrotate(root);
    }

    return root;
}
void preordertraversal(node *root)
{
    if (root != NULL)
    {

        printf("%d ", root->data);

        preordertraversal(root->left);
        preordertraversal(root->right);
    }
}
void inordertraversal(node *root)
{
    if (root != NULL)
    {
        inordertraversal(root->left);
        printf("%d ", root->data);
        inordertraversal(root->right);
    }
}

void postordertraversal(node *root)
{
    if (root != NULL)
    {

        postordertraversal(root->left);

        postordertraversal(root->right);
        printf("%d ", root->data);
    }
}
node *bstsearch(node *root, int d)
{
    if (root == NULL)
    {
        printf("number is not present in the BST\n");
        return (NULL);
    }
    if (root->data == d)
    {
        return (root);
    }
    else if (d < root->data)
    {
        return (bstsearch(root->left, d));
    }
    else
    {
        return (bstsearch(root->right, d));
    }
}
node *inorderpredecessor(node *root)
{
    if (root->left == NULL)
    {
        return (NULL);
    }
    node *p = root->left;
    while (p->right != NULL)
    {
        p = p->right;
    }
    return (p);
}
node *insertioninbst(node *root, int d)
{
    node *temp = createnode(0);

    if (root->data == d)
    {
        return (NULL);
    }

    if (d < root->data && root->left == NULL)
    {
        temp->data = d;
        root->left = temp;
    }
    if (d > root->data && root->right == NULL)
    {
        temp->data = d;
        root->right = temp;
    }
    if (d < root->data)
    {
        insertioninbst(root->left, d);
    }
    else
    {
        insertioninbst(root->right, d);
    }
}

node *deletioninbst(node *root, int d)
{

    if (root == NULL)
    {
        return (NULL);
    }

    if (root->left == NULL && root->right == NULL)
    {
        free(root);
        return (NULL);
    }

    if (d < root->data)
    {
        root->left = deletioninbst(root->left, d);
    }
    else if (d > root->data)
    {
        root->right = deletioninbst(root->right, d);
    }
    else
    {
        node *innode = inorderpredecessor(root);
        root->data = innode->data;
        root->left = deletioninbst(root->left, innode->data);
    }

    return (root);
}

int height(node *root)
{
    if (root == NULL)
        return (0);

    node *rootl, *rootr;
    rootl = root->left;
    rootr = root->right;

    int i, j, k, n, a, b;
    a = height(rootl);
    b = height(rootr);
    if (a >= b)
        return (a + 1);
    else
        return (b + 1);
}

int main()
{
    node *root = NULL;

    root = insert(root, 1);
    root = insert(root, 2);
    root = insert(root, 4);
    root = insert(root, 5);
    root = insert(root, 6);
    root = insert(root, 3);
    preordertraversal(root);
    printf("\n");
    inordertraversal(root);
    int c= height(root);
    printf("\n%d",c);
    return 0;
}