#include <stdio.h>
#include <stdlib.h>

typedef struct node_t {
	int data;
     	struct node_t *next;
} node;

void printList(node * Node) {
	int j = 1;
        printf("data = ");
	while( Node != NULL){
		printf(" %d", Node->data);
		Node = Node->next;
		j++;
	}
        printf("\n");
}

/*Implement this function for Lab 10*/
void reverse(node** head)
{
    node* temp3;
    //if node is empty
    node* temp1 = (*head);
    if (!temp1)
    {
        return;
    }
    
    //if only has one node
    node* temp2 = temp1->next;
    if (!temp2)
    {
        return;
    }
    //if node is more than one
    while (temp2)
    {
        temp3 = temp2->next;
        temp2->next = temp1;
        temp1=temp2;
        temp2=temp3;
    }
    (*head)->next = NULL;
    (*head)=temp1;
    return;

    
    

}

/*Implement this function for Lab 10*/
void removeDuplicates(node* head)
{
    if (!head)
    {
        return;
    }
    
    node* temp = head->next;
    while (temp)
    {
        if (head->data == temp->data)
        {
            head->next = temp->next;
            temp->next = NULL;
            free(temp);
            temp = head->next;
        }
        else
        {
            head = temp;
            temp = temp->next;
        }       
        
    }
    return;

}

int main() {
    node * head = NULL;
    node * temp;
    int i = 0;
    int j = 0;
    //Create Sorted linked list with repeats
    for(i = 9; i > 0; i--) {
        if(i%3==0){
            for(j = 0; j < 3; j++){
                temp = head;
	        head = (node *) malloc(sizeof(node));
	        head->data = i;
	        head->next = temp;     
            }
        }else{
            temp = head;
            head = (node *) malloc(sizeof(node));
            head->data = i;
            head->next = temp;
        }
    }
    printf("Printing the original list:\n");
    printList(head);
    removeDuplicates(head);
    printf("Printing the removeDuplicates list:\n");
    printList(head);
    reverse(&head);
    printf("Printing the reverse list:\n");
    printList(head);
    //free list
    while(head!=NULL){
        temp = head;
        head = head->next;
        free(temp);
    }
    return 0;
}
