#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int coef;
    int exp;
    struct node *next;
} node;

node *allocate()
{
    node *temp = (node *)malloc(sizeof(node));
    temp->next = NULL;
    return (temp);
}

node *insertLL(node *head, int coef, int exp)
{
    if (head == NULL) // 0 node present in list //
    {
        node *temp = allocate();
        temp->exp = exp;
        temp->coef = coef;
        temp->next = temp;
        head = temp;
        return (head);
    }

    node *p = head;
    if (p->next == head) // 1 node present in list//
    {
        if (p->exp > exp)
        {
            node *temp = allocate();
            temp->exp = exp;
            temp->coef = coef;
            p->next = temp;
            temp->next = p;

            return (head);
        }
        else if (p->exp < exp)
        {
            node *temp = allocate();
            temp->exp = exp;
            temp->coef = coef;
            temp->next = p;
            p->next = temp;
            head = temp;
            return (head);
        }
    }

    if (head->exp < exp) // when insertion is at start //
    {
        node *temp = allocate();
        temp->exp = exp;
        temp->coef = coef;
        while (p->next != head) // after this loop ends p points to last node//
        {
            p = p->next;
        }
        p->next = temp;
        temp->next = head;
        head = temp;
        return (head);
    }
    while (p->next != head) // 2 or more nodes present and insertion will take place after the head node//
    {
        if (p->next->exp < exp)
        {
            node *temp = allocate();
            temp->exp = exp;
            temp->coef = coef;
            temp->next = p->next;
            p->next = temp;
            return (head);
        }
        else
        {
            p = p->next;
            continue;
        }
    }
    if (p->next == head) // means p is last node //
    {
        node *temp = allocate();
        temp->exp = exp;
        temp->coef = coef;
        p->next = temp;
        temp->next = head;
        return (head);
    }
}
void displaypoly(node *head)
{
    node *p = head;
    while (p->next != head)
    {
        printf("%dx^%d + ", p->coef, p->exp);
        p= p->next;
    }

    printf(" %dx^%d\n", p->coef, p->exp);
}

void freepoly(node *head)
{
    node *p = head;
    node *pnext;
    pnext = p->next;
    while (pnext->next != head)
    {
        p->next = pnext->next;
        free(pnext);
        pnext = p->next;
    }
    free(pnext);
    free(p);
}
node *polyadd(node *clist1, node *clist2)
{
    node *clist3 = (node *)malloc(sizeof(node));
    clist3->next = clist3;
    node *p1, *p2, *p3;
    p1 = clist1;
    p2 = clist2;
    p3 = clist3;

    while (p1->next != clist1 && p2->next != clist2)
    {
        if (p1->exp == p2->exp)
        {
            int coef = p1->coef + p2->coef;
            int exp = p1->exp;
            p3->exp = exp;
            p3->coef = coef;
            p1 = p1->next;
            p2 = p2->next;
            node *temp = allocate();
            p3->next = temp;
            temp->next = clist3;
            p3 = p3->next;
        }
        else if (p1->exp > p2->exp)
        {
            p3->exp = p1->exp;
            p3->coef = p1->coef;
            p1 = p1->next;
            node *temp = allocate();
            p3->next = temp;
            temp->next = clist3;
            p3 = p3->next;
        }
        else if (p1->exp < p2->exp)
        {
            p3->exp = p2->exp;
            p3->coef = p2->coef;
            p2 = p2->next;
            node *temp = allocate();
            p3->next = temp;
            temp->next = clist3;
            p3 = p3->next;
        }
    }

    if (p1->next == clist1 && p2->next == clist2)
    {
        if (p1->exp == p2->exp)
        {
            int coef = p1->coef + p2->coef;
            int exp = p1->exp;
            p3->exp = exp;
            p3->coef = coef;
            return (clist3);
        }
        else if (p1->exp > p2->exp)
        {
            p3->exp = p1->exp;
            p3->coef = p1->coef;

            node *temp = allocate();
            p3->next = temp;
            temp->next = clist3;
            p3 = p3->next;
            p3->exp = p2->exp;
            p3->coef = p2->coef;
            return (clist3);
        }
        else if (p1->exp < p2->exp)
        {
            p3->exp = p2->exp;
            p3->coef = p2->coef;

            node *temp = allocate();
            p3->next = temp;
            temp->next = clist3;
            p3 = p3->next;
            p3->exp = p1->exp;
            p3->coef = p1->coef;
            return (clist3);
        }
    }
    if (p1->next == clist1)
    {
        while (p1 != clist1)
        {
            if (p1->exp == p2->exp)
            {
                int coef = p1->coef + p2->coef;
                int exp = p1->exp;
                p3->exp = exp;
                p3->coef = coef;
                p1 = p1->next;
                p2 = p2->next;
                node *temp = allocate();
                p3->next = temp;
                temp->next = clist3;
                p3 = p3->next;
            }
            else if (p1->exp > p2->exp)
            {
                p3->exp = p1->exp;
                p3->coef = p1->coef;
                p1 = p1->next;

                node *temp = allocate();
                p3->next = temp;
                temp->next = clist3;
                p3 = p3->next;
            }
            else if (p1->exp < p2->exp)
            {

                p3->exp = p2->exp;
                p3->coef = p2->coef;
                p2 = p2->next;
                node *temp = allocate();
                p3->next = temp;
                temp->next = clist3;
                p3 = p3->next;
            }
        }

        while (p2 != clist2)
        {
            p3->exp = p2->exp;
            p3->coef = p2->coef;
            p2 = p2->next;
            if (p2 != clist2)
            {
                node *temp = allocate();
                p3->next = temp;
                temp->next = clist3;
                p3 = p3->next;
            }
        }

        return (clist3);
    }

    if (p2->next == clist2)
    {
        while (p2 != clist2)
        {
            if (p1->exp == p2->exp)
            {
                int coef = p1->coef + p2->coef;
                int exp = p1->exp;
                p3->exp = exp;
                p3->coef = coef;
                p1 = p1->next;
                p2 = p2->next;
                node *temp = allocate();
                p3->next = temp;
                temp->next = clist3;
                p3 = p3->next;
            }
            else if (p1->exp > p2->exp)
            {
                p3->exp = p1->exp;
                p3->coef = p1->coef;
                p1 = p1->next;
                node *temp = allocate();
                p3->next = temp;
                temp->next = clist3;
                p3 = p3->next;
            }
            else if (p1->exp < p2->exp)
            {

                p3->exp = p2->exp;
                p3->coef = p2->coef;
                p2 = p2->next;
                node *temp = allocate();
                p3->next = temp;
                temp->next = clist3;
                p3 = p3->next;
            }
        }

        while (p1 != clist1)
        {
            p3->exp = p1->exp;
            p3->coef = p1->coef;
            p1 = p1->next;
            if (p1 != clist1)
            {
                node *temp = allocate();
                p3->next = temp;
                temp->next = clist3;
                p3 = p3->next;
            }
        }

        return (clist3);
    }
}

void main()
{
    node *head1 = NULL, *head2 = NULL, *head3 = NULL;
    int exp, coef, i, n, j, k;
    printf("enter the polynomials in the format : coefficient exponent \n");
    printf("enter the number of terms in first polynomial\n");
    scanf("%d", &n);
    printf("enter the polynomial\n");
    for (i = 0; i < n; i++)
    {
        scanf("%d%d", &coef, &exp);
        head1 = insertLL(head1, coef, exp);
    }

    printf("enter the number of terms in second polynomial\n");
    scanf("%d", &n);
    printf("enter the polynomial\n");
    for (i = 0; i < n; i++)
    {
        scanf("%d%d", &coef, &exp);
        head2 = insertLL(head2, coef, exp);
    }
    printf("the first polynomial is :");
    displaypoly(head1);
    printf("the second polynomial is :");
    displaypoly(head2);
    printf("now adding both the polynomials gives us : ");
    head3 = polyadd(head1, head2);
    displaypoly(head3);
    freepoly(head1);
    freepoly(head2);
    freepoly(head3);
}