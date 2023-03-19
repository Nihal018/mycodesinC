#include <stdio.h>
#include <stdlib.h>
int z = 0;
typedef struct node
{
    struct node *left;
    struct node *right;
    struct node *parent;
    int data;
} node;
int getcount(node *root)
{
    if (root != NULL)
    {
        z = z + 1;
        getcount(root->left);
        getcount(root->right);
    }
    return (z);
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
        printf("%d ", root->data);
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

int isEmpty(node *t)
{
    if (t == NULL)
    {
        return (1);
    }
    else
        return (0);
}

node *gettreeinpre(int in[], int insize, int pre[], int presize)
{
    node *root = createnode(pre[0]);
    int i = 2, j, k = 1, n, rindex;

    for (j = 0; j < insize; j++)
    {
        if (pre[0] == in[j])
        {
            rindex = j;
            break;
        }
    }
    node *rleft = createnode(pre[1]);
    rleft->parent = root;
    root->left = rleft;

    node *x = rleft;

    // forming the left subtree//
    while (i <= rindex)
    {
        node *temp = createnode(0);
        while (1)
        {
            if (x->data > pre[i] && x->left == NULL)
            {
                temp->data = pre[i];
                x->left = temp;
                temp->parent = x;
                x = rleft;
                i++;
                break;
            }
            else if (x->data > pre[i] && x->left != NULL)
            {
                x = x->left;
                continue;
            }
            else if (x->data < pre[i] && x->right == NULL)
            {
                temp->data = pre[i];
                x->right = temp;
                temp->parent = x;
                x = rleft;
                i++;
                break;
            }
            else if (x->data < pre[i] && x->right != NULL)
            {
                x = x->right;
                continue;
            }
        }
    }
    // now formin right subtree//
    node *rright = createnode(pre[i]);
    rright->parent = root;
    root->right = rright;
    i++;

    x = rright;
    while (i < presize)
    {
        node *temp = createnode(0);
        while (1)
        {
            if (x->data > pre[i] && x->left == NULL)
            {
                temp->data = pre[i];
                x->left = temp;
                temp->parent = x;
                x = rright;
                i++;
                break;
            }
            else if (x->data > pre[i] && x->left != NULL)
            {
                x = x->left;
                continue;
            }
            else if (x->data < pre[i] && x->right == NULL)
            {
                temp->data = pre[i];
                x->right = temp;
                temp->parent = x;
                x = rright;
                i++;
                break;
            }
            else if (x->data < pre[i] && x->right != NULL)
            {
                x = x->right;
                continue;
            }
        }
    }

    return (root);
}

node *gettreeinpost(int in[], int insize, int post[], int postsize)
{
    node *root = createnode(post[postsize - 1]);
    int i, j, k = 1, n, rindex;

    for (j = 0; j < insize; j++)
    {
        if (root->data == in[j])
        {
            rindex = j;
            break;
        }
    }
    node *rleft = createnode(post[rindex - 1]);
    rleft->parent = root;
    root->left = rleft;

    node *x = rleft;
    i = rindex - 2;
    // forming the left subtree//
    while (i >= 0)
    {
        node *temp = createnode(0);
        while (1)
        {
            if (x->data > post[i] && x->left == NULL)
            {
                temp->data = post[i];
                x->left = temp;
                temp->parent = x;
                x = rleft;
                i--;
                break;
            }
            else if (x->data > post[i] && x->left != NULL)
            {
                x = x->left;
                continue;
            }
            else if (x->data < post[i] && x->right == NULL)
            {
                temp->data = post[i];
                x->right = temp;
                temp->parent = x;
                x = rleft;
                i--;
                break;
            }
            else if (x->data < post[i] && x->right != NULL)
            {
                x = x->right;
                continue;
            }
        }
    }
    // now formin right subtree//
    node *rright = createnode(post[postsize - 2]);
    rright->parent = root;
    root->right = rright;
    i = postsize - 3;

    x = rright;
    while (i >= rindex)
    {
        node *temp = createnode(0);
        while (1)
        {
            if (x->data > post[i] && x->left == NULL)
            {
                temp->data = post[i];
                x->left = temp;
                temp->parent = x;
                x = rright;
                i--;
                break;
            }
            else if (x->data > post[i] && x->left != NULL)
            {
                x = x->left;
                continue;
            }
            else if (x->data < post[i] && x->right == NULL)
            {
                temp->data = post[i];
                x->right = temp;
                temp->parent = x;
                x = rright;
                i--;
                break;
            }
            else if (x->data < post[i] && x->right != NULL)
            {
                x = x->right;
                continue;
            }
        }
    }

    return (root);
}
int main()
{
    int n;
    int a[15] = {3, 32, 64, 66, 70, 72, 74, 81, 82, 88, 90, 95, 99, 100, 102};
    int b[15] = {81, 72, 66, 64, 32, 3, 70, 74, 88, 82, 90, 99, 95, 100, 102};
    int c[15] = {3, 32, 64, 70, 66, 74, 72, 82, 95, 102, 100, 99,90, 88, 81};
    node *head = gettreeinpre(a, 15, b, 15);
    inorder(head);
    printf("\n");
    postorder(head);
    printf("\n");
    node *head2 = gettreeinpost(a, 15, c, 15);
    inorder(head2);
    printf("\n");
    preorder(head2);

    return 0;
}
