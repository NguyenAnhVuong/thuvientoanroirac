#ifndef QUEUE_H_INCLUDED
#define QUEUE_H_INCLUDED
#define Max 100000
typedef int elementtype;
typedef struct
{
    elementtype data[Max];
    int rear;
    int front;
}Queue;
void makeNullQueue(Queue *q);
int isEmpty(Queue q);
int fullQueue(Queue q);
void enQueue(Queue *q, elementtype value);
void deQueue(Queue *q, elementtype *value);
#endif // QUEUE_H_INCLUDED
