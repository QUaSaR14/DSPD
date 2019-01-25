#include<stdio.h>
#include<stdlib.h>

typedef enum {FAILURE, SUCCESS} statuscode;
typedef int Item_type;

typedef struct Node_tag {
    Item_type data;
    struct Node_tag * next;
} Node_type;

typedef struct Stack_tag {
    Node_type *top ;
} Stack_type;

void Init(Stack_type *stck_ptr) {
    stck_ptr->top = NULL;
}

Node_type *MakeNode(Item_type d){

    Node_type *nptr;
    nptr = (Node_type *)malloc(sizeof(Node_type));
    if(nptr != NULL){
        nptr->data = d;
        nptr->next = nptr;
    }
    return nptr;
}

statuscode Push(Stack_type *stck_ptr, Item_type d){
    Node_type *nptr;
    statuscode retval = SUCCESS;
    nptr = MakeNode(d);
    if(nptr == NULL){
        retval = FAILURE;
    }
    else {
        nptr->next = stck_ptr->top;
        stck_ptr->top = nptr;
    }
    return retval;
}

statuscode Pop(Stack_type *stck_ptr, Item_type *dptr){
    Node_type *ptr;
    statuscode retval;
    if(stck_ptr->top == NULL){
        retval = FAILURE;
    }
    else {
        ptr = stck_ptr->top;
        stck_ptr->top = stck_ptr->top->next;
        *dptr = ptr->data;
        free(ptr);
    }
    return retval;
}

int main(){
    Stack_type stck;
    Item_type d;

    Init(&stck);

    Push(&stck, 10);
    Push(&stck, 20);
    Push(&stck, 30);
    Push(&stck, 40);

    Pop(&stck, &d);
    printf("%d\n", d);
    Pop(&stck, &d);
    printf("%d\n", d);
    Pop(&stck, &d);
    printf("%d\n", d);

    return 0;
}
