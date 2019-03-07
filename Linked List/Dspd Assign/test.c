#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//constants
#define FLIGHT 5
#define FLIGHT_ID 5 //AI266
#define TICKET_ID 8    //AI266014

typedef enum {FAILURE, SUCCESS} statuscode;
// typedef enum {JA, AI, IN, }

//Flight Data Structure
typedef struct Flight_Node_tag {
	char flight_id[FLIGHT_ID];
	struct Flight_Node_tag * next;
} Flight_Node;

//Service window Data Structure
typedef struct ServiceWindow_Node_tag {
    Flight_Node *flight;
    struct ServiceWindow_Node_tag *prev;
    struct ServiceWindow_Node_tag *next;
} SW_Node;

Flight_Node *CreateFlightList(char **Flight_ids){

	Flight_Node *list_ptr, *nptr;
	list_ptr = NULL;
	int len = sizeof(Flight_ids)/sizeof(Flight_ids[0]);
	for (int i = 0; i <= len ; i++)
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



int main() {
    SW_Node *swptr=NULL;
    Flight_Node *flt_ptr;
    int x;
    // swptr = NULL;
	statuscode sc;
	// list_ptr = NULL;
	char *flt_ids[FLIGHT] = { "AI101", "AI102", "AI103" ,"AI103" };

	/*printf("How many Flights do you want to add : \n");
	scanf("%d", &x);
	if(x<=FLIGHT){
        for(int i=0; i<x; i++){
            printf("Flight 1 : ");
            scanf("%s", flt_ids[i]);
        }
	}*/

    swptr = addFlightServiceWindow(flt_ids);

    Traverse_SW(swptr);

    return 0;
}











