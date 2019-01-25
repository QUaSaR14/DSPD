#include<stdio.h>
#include<stdlib.h>

typedef enum {FAILURE, SUCCESS} statuscode;
typedef int Item_type;

typedef struct Node_tag {
    Item_type data;
    struct Node_tag *next;
} Node_type;

typedef struct Queue_tag {
    Node_type *front;
    Node_type *rear;
} Queue_type;

void InitQ(Queue_type *qptr){
    qptr->front = qptr->rear = NULL;
}

int isQueueEmpty(Queue_type *qptr){
    int retval = 0;
    if(qptr->front == qptr->rear == NULL ){
        retval = 1;
    }
    return retval;
}

Node_type *MakeNode(Item_type *d){

    Node_type *nptr;
    nptr = (Node_type *)malloc(sizeof(Node_type));
    if(nptr != NULL){
        nptr->data = d;
        nptr->next = NULL;
    }
    return nptr;
}

statuscode InsertQ(Queue_type *qptr, Item_type d){

    Node_type *nptr;
    statuscode sc = SUCCESS;
    nptr = MakeNode(d);
    if(nptr == NULL){
        sc = FAILURE;
    }
    else {
        //0 node case
        if(isQueueEmpty(qptr)){
            qptr->front = qptr->rear = nptr;
        }
        //1 or more Node case
        else
        {
            qptr->rear->next = nptr;
            qptr->rear = nptr;
        }
    }
    return sc;
}

statuscode DeleteQ(Queue_type *qptr, Item_type *dptr){

    Node_type *nptr;
    statuscode sc = SUCCESS;
    if(isQueueEmpty(qptr)){
        sc = FAILURE;
    }
    else {
        nptr = qptr->front;
        qptr->front = qptr->front->next;
        *dptr = nptr->data;
        free(nptr);
        //If now queue is empty
        if(qptr->front == NULL){
            qptr->rear = NULL;
        }
    }
    return sc;
}

int main() {

    Queue_type queue;
    Item_type d;

    InsertQ(&queue, 10);
    InsertQ(&queue, 20);
    InsertQ(&queue, 30);

    DeleteQ(&queue, &d);
    printf("%d", d);


    return 0;
}
