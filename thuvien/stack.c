#include "stack.h"
Stack push(Stack head, elementtype value)
{
    Stack tmp = (Stack)malloc(sizeof(struct st));
    if(tmp == NULL)
    {
        printf("No memmory available Error!\n");
        exit(0);
    }
    tmp->data = value;
    tmp->next = head;
    head = tmp;
    return head;
}
Stack pop(Stack head, elementtype *value)
{
    if(head == NULL)
    {
        printf("The stack is empty can not pop error!\n");
        exit(0);
    }
    *value = head->data;
    Stack tmp = head;
    head = head->next;
    free(tmp);
    return head;
}