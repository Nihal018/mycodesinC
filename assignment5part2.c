#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct student
{
    char name[30];
    unsigned int roll;
    unsigned int marks;
    struct student *next;
};

typedef struct student student;

student *addsnodesorted(student *head, char name[], unsigned int roll, unsigned int marks)
{
    int d = 0;
    student *temp = (student *)malloc(sizeof(student));
    strcpy(temp->name, name);
    temp->roll = roll;
    temp->marks = marks;
    student *s = head;

    if (head == NULL)
    {
        temp->next = NULL;
        head = temp;
        return (head);
    }

    student *snext = s->next;
    if (head->marks > marks)
    {
        temp->next = head;
        head = temp;
        return (head);
    }

    while (s->next != NULL)
    {
        if (s->marks <= marks)
        {
            if (snext->marks >= marks)
            {
                s->next = temp;
                temp->next = snext;
                d = 1;
                break;
            }
            else
            {
                s = s->next;
                snext = snext->next;
                continue;
            }
        }
    }

    if (s->next == NULL)
    {
        s->next = temp;
        temp->next = NULL;
        return (head);
    }
    if (d == 1)
    {
        return (head);
    }
}

int ispresentsnodesorted(struct student *head, unsigned int roll)
{
    int position = 0;
    student *s = head;
    if (head->roll == roll)
    {
        position = 1;
        return (position);
    }

    while (s->next != NULL)
    {
        position++;
        if (s->roll == roll)
        {
            return (position);
        }
        else
        {
            s = s->next;
            continue;
        }
    }

    if (s->next == NULL)
    {
        if (s->roll == roll)
        {
            position++;
            return (position);
        }
    }

    return (0);
}

student *deletesnodesorted(student *head, unsigned int roll)
{
    int count = 2;
    int position = ispresentsnodesorted(head, roll);
    if (position == 0)
    {
        printf("\nstudent not present\n");
        return (head);
    }

    student *s = head;
    student *snext = s->next;
    if (position == 1)
    {
        head = head->next;
        free(s);
        return (head);
    }
    while (count != position)
    {
        s = s->next;
        snext = snext->next;
        count++;
    }

    s->next = snext->next;
    free(snext);
    return (head);
}

void printLL(student *head)
{
    if(head ==NULL)
     return;
    student *s = head;
    printf("Name  \tRoll\t\t Marks\n");
    while (s->next != NULL)
    {
        printf("%s  \t%u\t\t %u\n", s->name, s->roll, s->marks);
        s = s->next;
    }

    printf("%s  \t%u\t\t %u\n", s->name, s->roll, s->marks);
}

student *freesnodesorted(student *head)
{
    if (head == NULL)
    {
        printf("all the nodes are free \n");
        return (NULL);
    }
    student *s = head;
    head = head->next;
    free(s);
    return (freesnodesorted(head));
}

student *reversesnodesorted(student *head)
{

    student *s = head;
    student *s1 = s->next;
    student *s2 = s1->next;
    s->next = NULL;
    while (s2 != NULL)
    {
        s1->next = s;
        s = s1;
        s1 = s2;
        s2 = s2->next;
    }
    s1->next = s;
    return (s1);
}
student *sortOnRollSnodesorted(student *head)
{
    student *temp = (student *)malloc(sizeof(student));
    student *ptr1 = head;
    temp->next = NULL;
    while (ptr1->next != NULL)
    {
        student *ptr = head;
        while (ptr->next != NULL)
        {
            if (ptr->roll > ptr->next->roll)
            {
                temp->roll = ptr->next->roll;
                temp->marks = ptr->next->marks;
                strcpy(temp->name, ptr->next->name);
                ptr->next->roll = ptr->roll;
                ptr->next->marks = ptr->marks;
                strcpy(ptr->next->name, ptr->name);

                ptr->roll = temp->roll;
                ptr->marks = temp->marks;
                strcpy(ptr->name, temp->name);
            }
            ptr = ptr->next;
        }
        ptr1 = ptr1->next;
    }
    free(temp);
    return (head);
}
student *mergeSNodeSorted(student *head1, student *head2)
{
    student *s1, *s2;
    student *head3 = NULL;
    s1 = head1;
    s2 = head2;

    if (s1->marks < s2->marks)
    {
        head3 = s1;
        s1 = s1->next;
    }
    else
    {
        head3 = s2;
        s2 = s2->next;
    }

    student *s3 = head3;

    while (s1 != NULL && s2 != NULL)
    {
        if (s1->marks < s2->marks)
        {
            s3->next = s1;
            s3 = s3->next;

            s1 = s1->next;
        }
        else
        {
            s3->next = s2;
            s3 = s3->next;

            s2 = s2->next;
        }
    }
    head1= NULL;
    head2= NULL;

    if (s1 == NULL)
    {
        s3->next = s2;
        return (head3);
    }
    else
    {
        s3->next = s1;
        return (head3);
    }
}

void main()
{
    unsigned int roll, marks;
    int i, j, n;
    char name[30];
    student *head2 = NULL;
    student *head3 = NULL;
    student *head1 = NULL;
    printf("enter the number of students\n");
    scanf("%d", &n);
    printf("enter the student information in the following manner: name ,roll, marks\n");
    for (i = 0; i < n; i++)
    {
        scanf("%s %u %u", name, &roll, &marks);
        head1 = addsnodesorted(head1, name, roll, marks);
    }
    printf("enter the number of students\n");
    scanf("%d", &n);
    printf("enter the student information in the following manner: name ,roll, marks\n");
    for (i = 0; i < n; i++)
    {
        scanf("%s %u %u", name, &roll, &marks);
        head2 = addsnodesorted(head2, name, roll, marks);
    }
    printLL(head1);
    printLL(head2);
    printf("printing head3\n");
    head3 = mergeSNodeSorted(head1, head2);
    head1 =NULL;
    head2 = NULL;
    printLL(head3);
    printf("\n");
    printLL(head1);
    printLL(head2);
    printf("\nnow printing merged list in reverse order\n");
    head3 = reversesnodesorted(head3);
    printLL(head3);
    printf("\nnow printing merged list in increasing order of roll no.\n");
    head3= sortOnRollSnodesorted(head3);
    printLL(head3);
    freesnodesorted(head1);
    freesnodesorted(head2);
    freesnodesorted(head3);
}