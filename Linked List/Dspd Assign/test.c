#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//constants
#define FLIGHT 5
#define FLIGHT_ID 5 //AI266
#define TICKET_ID 8    //AI266014
#define MAX_SIZE 250
#define NEXT_ROW -1
#define END_INPUT -2
#define ROW 3
#define COLUMNS 10

typedef enum {FAILURE, SUCCESS} statuscode;
typedef int ItemType;
typedef enum{FALSE,TRUE} Bool;
// typedef enum {JA, AI, IN, }

//Flight Data Structure
typedef struct Flight_Node_tag {
	char flight_id[FLIGHT_ID];
	AddressNode *mat;
	struct Flight_Node_tag * next;
} Flight_Node;

//Service window Data Structure
typedef struct ServiceWindow_Node_tag {
    Flight_Node *flight;
    struct ServiceWindow_Node_tag *prev;
    struct ServiceWindow_Node_tag *next;
} SW_Node;

typedef struct MatNodeTag
{
	ItemType val;
	int col;
	int row;
	struct MatNodeTag* next;
	struct MatNodeTag* down;
}MatNode;

typedef struct AddressNodeTag	//address node tag
{
	int address;				//either row or col
	struct AddressNodeTag* nextAddress;
	MatNode* rowList;
}AddressNode;

Flight_Node *CreateFlightList(char **Flight_ids){

	Flight_Node *list_ptr, *nptr;
	list_ptr = NULL;
	//int len = sizeof(Flight_ids)/sizeof(Flight_ids[0]);
	//printf("%d", len);
	for (int i = 0; i < 4 ; i++)
	{
		nptr = (Flight_Node *)malloc(sizeof(Flight_Node));
		strcpy(nptr->flight_id, Flight_ids[i]);
		nptr->next = list_ptr;
		list_ptr = nptr;
	}
	return list_ptr;
}

SW_Node *MakeNode(char **Flight_ids){
    SW_Node *nptr;

    nptr = (SW_Node *)malloc(sizeof(SW_Node));

    nptr->flight = CreateFlightList(Flight_ids);
    nptr->prev = NULL;
    nptr->next = NULL;
    return nptr;
}

SW_Node *InsertAtEnd(SW_Node *swptr, char **Flight_ids){
    SW_Node *nptr, *ptr;
    nptr = MakeNode(Flight_ids);
    ptr = swptr;
    if(swptr == NULL) swptr = nptr;
    else
    {
        while(ptr->next){
            ptr = ptr->next;
        }
        ptr->next = nptr;
        nptr->prev = ptr;
        nptr->next = NULL;
    }
    return swptr;
}

SW_Node *addFlightServiceWindow(char **Flight_ids) {
    SW_Node *swptr = NULL;
    swptr = InsertAtEnd(swptr, Flight_ids);
    return swptr;
}

void Traverse_SW(SW_Node *swptr) {
    SW_Node *nptr;
    Flight_Node *ptr;
    nptr = swptr;
    while(nptr != NULL) {
        ptr = nptr->flight;
        while(ptr != NULL) {
            printf("Flight: %s \n", ptr->flight_id);
            ptr = ptr->next;
        }
        nptr = nptr->next;
    }
}

//==============SPARSE MATRIX==================
MatNode* MakeMatNode(ItemType val,int row,int col)
{
	MatNode* nptr;
	nptr=(MatNode*)malloc(sizeof(MatNode));
	if(nptr!=NULL)
	{
		nptr->val=val;
		nptr->col=col;
		nptr->row=row;
		nptr->next=NULL;
		nptr->down=NULL;
	}
	return nptr;
}

AddressNode* MakeAddressNode(int val_add,MatNode* nextRowList)
{
	AddressNode* nptr;
	nptr=(AddressNode*)malloc(sizeof(AddressNode));
	if(nptr!=NULL)
	{
		nptr->address=val_add;
		nptr->rowList=nextRowList;
		nptr->nextAddress=NULL;
	}
	return nptr;
}

void InsertAddressNode(AddressNode** finalHead,int add,MatNode* head,AddressNode** finalTail)
{
	AddressNode* nptr=MakeAddressNode(add,head);
	if(*finalHead==NULL)
	{
		*finalHead=nptr;
		*finalTail=nptr;
	}
	else
	{
		(*finalTail)->nextAddress=nptr;
		(*finalTail)=nptr;
	}
	nptr->nextAddress=NULL;
	return;
}

void InsertMatNode(MatNode** head,ItemType val,MatNode** tail,int rows,int cols)
{
	//can return status
	MatNode* nptr=MakeMatNode(val,rows,cols);
	nptr->next=NULL;
	nptr->down=NULL;
	if(*head==NULL)
	{
		*head=nptr;
		*tail=*head;

	}
	else
	{
		(*tail)->next=nptr;
		*tail=nptr;

	}
	return;
}

void TraverseMatrix(AddressNode* start)
{
	AddressNode* head=start;
	MatNode* mat;
	while(head!=NULL)
	{
		mat=head->rowList;
		while(mat!=NULL)
		{
			printf("%3d ",mat->val);
			mat=mat->next;
		}
		head=head->nextAddress;
		printf("\n");
	}
	return;
}

AddressNode* Read()
{
	Bool isEmpty;
	AddressNode* finalHead1=NULL,*finalTail1=NULL;
	AddressNode* finalHead2=NULL,*finalTail2=NULL;
	MatNode* head,*tail;
	//printf("ENTER THE ELEMENTS(non-negative) IN THE MATRIX\nIF DONE ENTER -1 TO JUMP TO NEXT ROW AND -2 TO TERMINATE GIVING INPUTs\nENTER IN ROW MAJOR FORM\n");
    for(int i=0; i<ROW; i++){
        head=NULL;
        tail=NULL;
        isEmpty=TRUE;
        for(int j=0; j<COLUMNS; j++){
            int seat = (j)* ROW + (i+1);
            InsertMatNode(&head,seat,&tail,i,j);
            if(i==0)
            {
                InsertAddressNode(&finalHead2,j,head,&finalTail2);
            }
            isEmpty=FALSE;
        }
        if(!isEmpty)
        {
                InsertAddressNode(&finalHead1,i,head,&finalTail1);
        }
    }

	printf("THE SPARSE MATRIX LOOKS LIKE:\n");
	TraverseMatrix(finalHead1);
	return finalHead1;
}

MatNode *Delete(MatNode *p){
	MatNode *q ;
	if(p!=NULL){
		q = p->next;
		p->next = q->next;
		free(q);
	}
	return p;
}

void DeleteNode(AddressNode* mat, int row, int colmn){

	AddressNode *head;
	MatNode *curr, *prev=NULL;
	int flag=0;
	if(mat!=NULL) {
		head = mat;
		while(head!=NULL && flag==0){
			if(head->address == row){
				flag=1;
				curr = head->rowList;
			}
			else{
				head = head->nextAddress;
			}
		}
		if(flag){
			if(curr->col == colmn){
				MatNode *nptr;
				nptr = curr;
				curr = curr->next;
				free(nptr);
				head->rowList = curr;
			}
			else {
				while(curr!=NULL && flag==1){
					if(curr->col == colmn){
						flag=0;
						curr = Delete(prev);
					}
					else {
						prev = curr;
						curr = curr->next;
					}
				}
			}
		}
		else {
			printf("Node Not Found !!");
		}
	}
    return;
}

//=======================END OF SPARSE MATRIX=======================



int main() {
    SW_Node *swptr=NULL;
    Flight_Node *flt_ptr;
    int x;
    // swptr = NULL;
	statuscode sc;
	// list_ptr = NULL;
	char *flt_ids[FLIGHT_ID] = { "AI101", "AI102", "AI103" ,"AI103" };

	/*printf("How many Flights do you want to add : \n");
	scanf("%d", &x);
	if(x<=FLIGHT){
        for(int i=0; i<x; i++){
            //flt_ids[i] = malloc(FLIGHT_ID);
            printf("Flight %d : ", i);
            scanf("%ms", &flt_ids[i]);
        }
	}*/

    swptr = addFlightServiceWindow(flt_ids);
    Traverse_SW(swptr);

    //SEAT CHART
    AddressNode* mat1;
	mat1=Read();

	//DELETE NODE
	DeleteNode(mat1, 1, 2);
	TraverseMatrix(mat1);

	//TICKET ID

    return 0;
}











