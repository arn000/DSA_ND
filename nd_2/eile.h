#ifndef HEAD_H_INCLUDED
#define HEAD_H_INCLUDED

typedef struct node
{
    int data;
    struct node *next;
} Node;

typedef struct queue
{
    int count;
    Node *front;
    Node *rear;
}Queue;

void init (Queue *q); /* Sukuria eile */
void enqueue (Queue *q, int data); /* Elemento idejimas */
void dequeue(Queue *q); /* Elemento isemimas */
void print_list (Queue *q); /* Atspausdina eile */
void delete_list (Queue *q); /* Istrina eile*/
void print_front (Queue *q); /* Atspausdina pirma eiles elementa*/
int is_empty(Queue *q); /* Patikrina ar eile tuscia*/
int is_full(Queue *q); /* Patikrina ar eile pilna */

#endif
