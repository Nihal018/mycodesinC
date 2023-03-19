#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node
{
    struct node *left;
    struct node *right;
    struct node *parent;
    int data;
} node;
int getcount(node *root, int *z)
{

    if (root != NULL)
    {
        (*z)++;
        getcount(root->left, &(*z));
        getcount(root->right, &(*z));
    }
    return (*z);
}
int maximum(int a, int b)
{
    if (a >= b)
        return (a);
    else
        return (b);
}
node *createnode(int d)
{
    node *n = (node *)malloc(sizeof(node));
    n->parent = NULL;
    n->data = d;
    n->left = NULL;
    n->right = NULL;
    return (n);
}

int preorder(node *root)
{
    if (root == NULL)
        return 0;
    if (root != NULL)
    {

        printf("%d ", root->data);

        preorder(root->left);
        preorder(root->right);
    }
    return (1);
}
int inorder(node *root)
{
    if (root == NULL)
        return (0);

    if (root != NULL)
    {
        inorder(root->left);
        printf(" %d ", root->data);
        inorder(root->right);
    }
    return (1);
}

int postorder(node *root)
{
    if (root == NULL)
        return (0);

    if (root != NULL)
    {

        postorder(root->left);

        postorder(root->right);
        printf("%d ", root->data);
    }
    return (1);
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

node *inordersuccessor(node *root)
{
    if (root->right == NULL)
    {
        return (NULL);
    }
    node *p = root->right;
    while (p->left != NULL)
    {
        p = p->left;
    }
    return (p);
}
node *insertnode(node *root, int d)
{
    node *temp = createnode(0);
    if (root == NULL)
    {
        temp->data = d;
        return (temp);
    }

    if (d < root->data)
    {
        root->left = insertnode(root->left, d);
        root->left->parent = root;
    }
    else
    {
        root->right = insertnode(root->right, d);
        root->right->parent = root;
    }

    return (root);
}

node *deletenode(node *root, int d)
{
    if (root == NULL)
    {
        return (NULL);
    }

    if (root->left == NULL && root->right == NULL && root->data == d) // deletion of leaf node //
    {
        free(root);
        return (NULL);
    }

    // deletion of node wth one child//
    if (root->left != NULL && root->right == NULL || root->right != NULL && root->left == NULL)
    {
        if (root->data == d && root->left != NULL)
        {
            node *innode = inorderpredecessor(root);
            root->data = innode->data;
            root->left = deletenode(root->left, innode->data);

            return (root);
        }
        else if (root->data == d && root->right != NULL)
        {
            node *temp = inordersuccessor(root);
            root->data = temp->data;
            root->right = deletenode(root->right, temp->data);
            return (root);
        }
    }
    if (d < root->data)
    {
        root->left = deletenode(root->left, d);
    }
    else if (d > root->data)
    {
        root->right = deletenode(root->right, d);
    }
    else // deletion of node with two children //
    {
        node *innode = inorderpredecessor(root);
        root->data = innode->data;
        root->left = deletenode(root->left, innode->data);
    }

    return (root);
}
int height(node *t)
{
    if (t == NULL)
        return (0);
    else if (t->left == NULL && t->right == NULL)
        return (0);
    else
        return (maximum(height(t->left), height(t->right)) + 1);
}
int max(node *t)
{
    if (t->right == NULL)
        return (t->data);
    node *rright;
    rright = t->right;
    while (rright->right != NULL)
    {
        rright = rright->right;
    }
    return (rright->data);
}

int min(node *t)
{
    if (t->left == NULL)
        return (t->data);
    node *rleft;
    rleft = t->left;
    while (rleft->left != NULL)
    {
        rleft = rleft->left;
    }
    return (rleft->data);
}

void inordertraversal(node *t, int *a, int *x)
{

    if (t != NULL)
    {
        inordertraversal(t->left, a, &(*x));
        a[*x] = t->data;

        (*x)++;
        inordertraversal(t->right, a, &(*x));
    }
}

void preordertraversal(node *t, int *b, int *x)
{

    if (t != NULL)
    {
        b[*x] = t->data;

        (*x)++;
        preordertraversal(t->left, b, &(*x));
        preordertraversal(t->right, b, &(*x));
    }
}

int equal(node *t1, node *t2)
{

    int i = 0, j = 0, n = 0, m = 0;
    n = getcount(t1, &n);
    m = getcount(t2, &m);
    if (n != m)
    {
        return (0);
    }
    int *pre1 = (int *)malloc(1000 * sizeof(int));
    int *pre2 = (int *)malloc(1000 * sizeof(int));
    int *in1 = (int *)malloc(1000 * sizeof(int));
    int *in2 = (int *)malloc(1000 * sizeof(int));
    inordertraversal(t1, in1, &i);
    printf("\n");
    i = 0;
    inordertraversal(t2, in2, &i);
    printf("\n");
    i = 0;

    preordertraversal(t1, pre1, &i);
    printf("\n");
    i = 0;
    preordertraversal(t2, pre2, &i);
    printf("\n");
    i = 0;

    while (i < n)
    {
        if (in1[i] == in2[i])
        {
            i++;
            continue;
        }
        else
            return (0);
    }

    while (j < n)
    {
        if (pre1[j] == pre2[j])
        {
            j++;
            continue;
        }
        else
            return (0);
    }

    return (1);
}

int isEmpty(node *t)
{
    if (t == NULL)
    {
        return (1);
    }
    else
        return (0);
}


int main()
{
    int n, i = 0;
    node *p = NULL, *q, *t = NULL;
    p = insertnode(p, 50);
    p = insertnode(p, 41);
    p = insertnode(p, 87);
    p = insertnode(p, 86);
    p = insertnode(p, 34);
    p = insertnode(p, 100);
    p = insertnode(p, 47);
    p = insertnode(p, 69);

    inorder(p);
    printf("\n");
    n = getcount(p, &i);
    i = 0;
    printf("number of nodes in tree 1 = %d\n", n);

    p = deletenode(p, 86);
    inorder(p);
    int h = height(p);
    printf("\nheight of tree = %d \n", h);
    int m = max(p);
    int a = min(p);
    printf("minimum key = %d\n maximum key = %d", a, m);
    t = insertnode(t, 50);
    t = insertnode(t, 41);
    t = insertnode(t, 87);

    t = insertnode(t, 34);
    t = insertnode(t, 100);
    t = insertnode(t, 47);
    t = insertnode(t, 69);

    printf("\n");
    inorder(t);

    n = getcount(t, &i);
    i = 0;
    printf("\nnumber of nodes in tree 2= %d\n", n);
    int e = equal(p, t);

    if (e == 1)
        printf("\n the trees are equal");
    else if (e == 0)
        printf("\nthe trees are not equal");

    return 0;
}