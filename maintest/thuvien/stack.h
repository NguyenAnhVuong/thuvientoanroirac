#include <stdlib.h>
#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED
typedef int elementtype;
struct st
{
    elementtype data;
    struct st *next;
};
typedef struct st *Stack;
Stack push(Stack head, elementtype value);
Stack pop(Stack head, elementtype *value);
#endif // STACK_H_INCLUDED