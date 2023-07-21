#include <stdio.h>
#include <stdlib.h>
struct node
{
    int data;
    struct node *prev;
    struct node *next;
};
int list(struct node **head, int n)
{
    if (n == 0)
    {
        *head == NULL;
    }
    else if (n > 0)
    {
        struct node *ptr;
        struct node *new_node;
        new_node = (struct node *)malloc(sizeof(struct node));
        *head = new_node;
        ptr = *head;
        printf("Enter the elements is list:\n");
        scanf("%d", &ptr->data);
        int i;
        for (i = 1; i < n; i++)

        {
            new_node = (struct node *)malloc(sizeof(struct node));
            ptr->next = new_node;
            new_node->prev = ptr;
            ptr = new_node;
            scanf("%d", &ptr->data);
        }
        ptr->next = (*head);
        (*head)->prev = ptr;
    }
}
struct node *cir_insertion(struct node **head, struct node **tail, int ele, int pos)
{
    int i;
    struct node *new_node, *temp;

    new_node = (struct node *)malloc(sizeof(struct node));

    new_node->data = ele;
    if (new_node == NULL)
    {
        printf("Dynamic memory allocation failed,insertion cannot be done \n");
        return NULL;
    }
    else
    {
        if (pos < 1)
        {
            printf("Inappropriate position,Choose the position carefully \n");
            return NULL;
        }
        else if (pos == 1)
        {
            new_node->next = *head;
            new_node->prev = *tail;
            (*tail)->next = new_node;
            (*head)->prev = new_node;
            *head = new_node;
        }
        else
        {
            temp = *head;
            i = 1;
            while (i < pos - 1 && temp->next != (*head))
            {
                i++;
                temp = temp->next;
            }
            if (temp->next != (*head))
            {
                new_node->next = temp->next;
                temp->next->prev = new_node;
                new_node->prev = temp;
                temp->next = new_node;

                //     new_node->prev = temp;
                //     new_node->next = temp->next;
            }
            else
            {
                new_node->prev = temp;
                new_node->next = *head;
                temp->next = new_node;
            }
        }
    }
}
int cir_deletion(struct node **head, struct node **tail, int *ele, int pos)
{
    int i;
    struct node *temp, *prev, *temp1;
    if (*head == NULL)
    {
        printf("As list is empty so,deletion is not possible \n");
        return -1;
    }
    else if (pos < 1)
    {
        printf("Invalid position,Please choose appropriate position\n");
        return -1;
    }
    else if (pos == 1)
    {
        temp = *head;
        *head = (*head)->next;
        (*tail)->next = *head;
        (*head)->prev = *tail;

        //  (*head)->prev = NULL;
        *ele = temp->data;
        free(temp);
        return 0;
    }
    else
    {
        temp = *head;
        i = 1;
        while (i < pos - 1 && temp->next != *head)
        {
            temp = temp->next;
            i++;
        }
        if (temp->next == *head)
        {
            printf("Deletion is not possible as postion exceeds the limit \n");
            return -1;
        }
        else
        {
            temp1 = temp->next;
            if (temp1->next != *head)
            {

                temp1->next->prev = temp;
                temp->next = temp1->next;
            }
            else
            {
                *tail = temp;
                temp->next = *head;
            }
            *ele = temp1->data;
            free(temp1);
            printf("\n%d is the deleted element", *ele);

            return 0;
        }
    }
}
void printElement(struct node **head)
{
    struct node *ptr;
    ptr = (*head);
    printf("\nElements in the linked list are: ");
    printf("%d ", ptr->data);
    ptr = ptr->next;
    while (ptr != *head)
    {
        printf("%d ", ptr->data);
        ptr = ptr->next;
    }
}
int main()
{
    int ele, pos, user_ch, n;
    struct node *head = NULL;
    struct node *tail = NULL;
    do
    {
        printf("Enter how many element you want to insert in doubly linked list:  ");
        scanf("%d", &n);
        if (n < 0)
        {
            printf("Please choose the positive integer\n");
        }
    } while (n < 0);
    list(&head, n);

    do
    {
        printf("\nEnter 1 for Insertion in doubly linked list\n");
        printf("Enter 2 for Deletion in doubly linked list\n");
        printf("Enter 0 to exit the Program\n");
        printf("Please Enter your choice: ");
        scanf("%d", &user_ch);

        if (user_ch == 1)
        {
            printf("Enter the Elements in linked list: ");
            scanf("%d", &ele);
            printf("Enter the position where you want to insert:");
            scanf("%d", &pos);
            cir_insertion(&head, &tail, ele, pos);
            printElement(&head);
        }
        else if (user_ch == 2)
        {
            printf("Enter the position where you want to delete:");
            scanf("%d", &pos);
            cir_deletion(&head, &tail, &ele, pos);
            printElement(&head);
        }
    } while (user_ch != 0);
    return 0;
}
