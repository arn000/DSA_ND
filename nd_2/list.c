#include <stdio.h>
#include <stdlib.h>
#include "eile.h"

void init (Queue *q) // sukuriam eile
{

    q->count = 0;
    q->front = NULL;
    q->rear = NULL;
}
void enqueue (Queue *q, int data) // idedam elementus i eile
{
    Node *tmp = malloc(sizeof(Node));
    tmp->data=data;
    tmp->next=NULL;

    if (q->rear!=NULL)
    {
        q->rear->next = tmp;
        q->rear = tmp;
    }
    else
    {
        q->front = q->rear = tmp;
    }
    q->count++;
    printf("%d\n",q->count);
}
void dequeue (Queue *q)     //elementu isemimas is eiles
{
    if(!is_empty(q))
    {
        return;
    }
    Node *tmp = q->front;
    q->front = tmp->next;
    free(tmp);
    q->count--;
    printf("%d\n",q->count);
}
void print_list(Queue *q)   //eiles atspaudinimas
{
    Node *cursor = q->front;
    while (cursor!=NULL)
    {
        printf("%d ",cursor->data);
        cursor=cursor->next;
    }
    printf("\n");
}
void delete_list(Queue *q)  // eiles istrinimas
{
  int counter = q->count;
  for(int i=0; i<counter; i++)
  {
      dequeue(q);
  }

  free(q);
}
int is_empty(Queue *q)  //patrinkinam ar eile tuscia
{
    if (q->front==NULL)
    {
        return 1;   // programos pabaiga
    }
}
int is_full(Queue *q)  //patrinkinam ar eile pilna
{
    Node *tmp = malloc(sizeof(Node));
    if(tmp==NULL)   // tikrinam ar eile pilna
        return 1;
}
void print_front(Queue *q) // atspaudinam pirma eiles elementa
{
    printf("%d",q->front->data);
}
