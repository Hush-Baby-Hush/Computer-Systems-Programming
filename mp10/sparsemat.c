
#include "sparsemat.h"

#include <stdio.h>
#include <stdlib.h>





sp_tuples * load_tuples(char* input_file)
{
    FILE* stream = fopen(input_file,"r");
    sp_tuples* tuples = (sp_tuples*)malloc(sizeof(sp_tuples));
    fscanf(stream,"%d %d",&tuples->m,&tuples->n);
    fgetc(stream);
    tuples->nz=0;
    tuples->tuples_head = NULL;
    int row,col;
    double value;
    while(fscanf(stream,"%d %d %lf",&row,&col,&value)!=EOF)
    {
        insert_tuples(tuples,row,col,value);
        fgetc(stream);
    }
    fclose(stream);
    return tuples;
}



double gv_tuples(sp_tuples * mat_t,int row,int col)

{
    sp_tuples_node* target = search_tuples(mat_t,row,col);
    if (target && target->row==row && target->col == col)
    {
        return target->value;
    }
    
    return 0;
}

void delete_tuples(sp_tuples * mat_t, int row, int col)
{
    sp_tuples_node* target = search_tuples(mat_t,row,col);
    //if exist
    if (target && target->row==row && target->col == col)
    {
        if (target == mat_t->tuples_head)
        {
            mat_t->tuples_head = target->next;
            target->next = NULL;
            free(target);
            mat_t->nz--;
            return;
        }
        
        sp_tuples_node* temp = mat_t->tuples_head;
        while (temp->next!=target)
        {
            temp = temp->next;
        }
        temp->next = target->next;
        target->next=NULL;
        free(target);
        target = NULL; 
        mat_t->nz--;
    }
    return;
}

sp_tuples_node* search_tuples(sp_tuples * mat_t, int row, int col)
{
    sp_tuples_node* target = mat_t->tuples_head;
    sp_tuples_node* temp = mat_t->tuples_head;
    while (target && target->row<row)
    {
        temp = target;
        target = target->next;
    }
    if (target && target->row==row)
    {
        while (target && target->row==row && target->col<col)
        {
            temp = target;
            target = target->next;
        }
        if (target && target->row==row && target->col==col)
        {
            return target;
        }
        
    }
    return temp;
}

void insert_tuples(sp_tuples * mat_t, int row, int col, double value)
{
    if (!value)
    {
        delete_tuples(mat_t,row,col);
        return;
    }
    
    sp_tuples_node* target = search_tuples(mat_t,row,col);

    //if mat_t is empty
    if (target==NULL)
    {
        sp_tuples_node* new = (sp_tuples_node*)malloc(sizeof(sp_tuples_node));
        new->value = value;
        new->row = row;
        new->col = col;
        mat_t->nz++;
        mat_t->tuples_head = new;
        new->next = NULL;
        return;
    }

    //if already exist
    if (target->row==row && target->col == col)
    {
        target->value = value;
        return;
    }

    //if not exist
    //if target is head
    if (target==mat_t->tuples_head)
    {
        //if before head
        if (target->row>row || (target->row==row && target->col>col))
        {
            sp_tuples_node* new = (sp_tuples_node*)malloc(sizeof(sp_tuples_node));
            new->value = value;
            new->row = row;
            new->col = col;
            mat_t->nz++;
            mat_t->tuples_head = new;
            new->next = target;
            return;
        }
        
    }
    
    //normal situation, insert behind
    sp_tuples_node* new = (sp_tuples_node*)malloc(sizeof(sp_tuples_node));
    new->value = value;
    new->row = row;
    new->col = col;
    mat_t->nz++;
    if (target->next)
    {
        sp_tuples_node* temp = target->next;
        target->next = new;
        new->next = temp;
        return;
    }

    target->next = new;
    new->next = NULL;
    
    return;
}

void set_tuples(sp_tuples * mat_t, int row, int col, double value)
{
    if (value==0)
    {
        delete_tuples(mat_t,row,col);
        return;
    }

    insert_tuples(mat_t,row,col,value);

    return;
}



void save_tuples(char * file_name, sp_tuples * mat_t)
{
    if (!mat_t)
    {
        return;
    }
    
    FILE* stream = fopen(file_name,"w");
    fprintf(stream,"%d %d\n",mat_t->m,mat_t->n);
    sp_tuples_node* temp = mat_t->tuples_head;
    while (temp)
    {
        fprintf(stream,"%d %d %lf\n",temp->row,temp->col,temp->value);
        temp = temp->next;
    }
    fclose(stream);
	return;
}



sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB)
{
    if (matA->m!=matB->m || matA->n!=matB->n)
    {
        return NULL;
    }
    //initialize
    sp_tuples* matC = (sp_tuples*)malloc(sizeof(sp_tuples));
    matC->nz=0;
    matC->tuples_head = NULL;
    matC->m = matA->m;
    matC->n = matA->n;

    //copy A
    sp_tuples_node* tempa = matA->tuples_head;
    while(tempa)
    {
        insert_tuples(matC,tempa->row,tempa->col,tempa->value);
        tempa = tempa->next;
    } 

    //add B
    sp_tuples_node* tempb = matB->tuples_head;
    while(tempb)
    {
        sp_tuples_node* target = search_tuples(matC,tempb->row,tempb->col);
        //if exist
        if (target && target->row==tempb->row && target->col == tempb->col)
        {
            target->value +=tempb->value;
        }
        else
        {
            insert_tuples(matC,tempb->row,tempb->col,tempb->value);
        }
        tempb = tempb->next;
        
    }



	return matC;
}



sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB)
{ 
    if (matA->n!=matB->m)
    {
        return NULL;
    }

    //initialize
    sp_tuples* matC = (sp_tuples*)malloc(sizeof(sp_tuples));
    matC->nz=0;
    matC->tuples_head = NULL;
    matC->m = matA->m;
    matC->n = matB->n;

    //loop through every node in A
    sp_tuples_node* tempa = matA->tuples_head;
    while(tempa)
    {
        sp_tuples_node* tempb = matB->tuples_head;
        while (tempb)
        {
            if(tempb->row==tempa->col)
            {
                sp_tuples_node* target = search_tuples(matC,tempa->row,tempb->col);
                if (target && target->row==tempa->row && target->col==tempb->col)
                {
                    target->value+=(tempa->value*tempb->value);
                }
                else
                {
                    insert_tuples(matC,tempa->row,tempb->col,tempa->value*tempb->value);
                }
                
                
            }
            else if (tempb->row>tempa->col)
            {
                break;
            }
            
            tempb = tempb->next;
        }

        tempa = tempa->next;
        
    }


    return matC;

}


	
void destroy_tuples(sp_tuples * mat_t)
{
	if (!mat_t)
    {
        return;
    }
    if (!mat_t->tuples_head)
    {
        free(mat_t);
        return;
    }

    sp_tuples_node* curr = mat_t->tuples_head;
    sp_tuples_node* temp = curr->next;
    while (!temp)
    {
        free(curr);
        curr = temp;
        temp = temp->next;
    }
    free(curr);
    free(mat_t);
    
    
    return;
}  




