/* Kernel1.C kernel project        */
/* March 5, 2008 - CS421 - TS      */
/* By Jeremy VillEgAS              */

#include<stdio.h>
#include<stdlib.h>
#include"kernel1.h"

/* Enqueues PCB to the given queue */
struct queue_t* enqueue(struct queue_t *q,struct pcb_t *p){
  struct queue_t *que_new=NULL;
  que_new=malloc(sizeof(struct queue_t));
  que_new->que_next=NULL;
  que_new->pcb_item=p;
  /* is queue empty? */ 
  if(empty(q))return(que_new);
  /* nope, so stick this on top of the list */
  que_new->que_next=q;
  return(que_new);
}

/* Dequeues the PCB from the given queue */
struct queue_t* dequeue(struct queue_t *q,struct pcb_t *p){
  struct queue_t *que_rm=q;      /* this is the node to remove from queue */
  if(empty(q))return(NULL);        /* Is the list already empty? */
  if(q->que_next==NULL){         /* There was only one item in the list*/
    p=q->pcb_item;
    free(que_rm);               
    return(NULL);
  }                              /* this happens when only 1 item in queue */
  q=q->que_next;                 /* make the second item the next item */
  free(que_rm);                  /* deallocate memory space */
  return(q);
}

/* Inserts a PCB by priority to the given queue */
struct queue_t* insert(struct queue_t *q,struct pcb_t *p){
  struct queue_t *que_new=NULL,*que_cur=NULL,*que_prev=NULL;
  /* get new queue item ready */
  que_new=malloc(sizeof(struct queue_t));
  que_new->pcb_item=p;
  que_new->que_next=NULL;
  //// Case where item will be the first in the list
  /* no items in the queue  */
  if(empty(q))return(que_new); 
  /* not empty, is there only one item in the list? */
  if(q->que_next==NULL){
    /* yes, determine the priority of it */
    if(q->pcb_item->priority<p->priority){
      /* the one in the queue has a lower priority */
      q->que_next=que_new;
      return(q);
    } else return(que_new->que_next=q); 
  }
  //// Case where item will go somewhere in the middle of the list
  /* not empty, there is more than one item in the list */
  /* is it highest priority? */
  if(q->pcb_item->priority>p->priority) return(que_new->que_next=q);  
  que_cur=q->que_next;
  que_prev=q;
  while(que_cur!=NULL){
    /* is the priority of p lower than the priority of current Q? */
    if(que_cur->pcb_item->priority>p->priority){
      /* yes, so make new item and make next the current */
      que_new->que_next=que_cur;
      /* the previous one's next should be the new item */  
      que_prev->que_next=que_new;
      return(q);
    }
    que_prev=que_cur;
    que_cur=que_cur->que_next;
  }
  //// Case where item will go at the end of the list
  /* new item must go at the end */ 
  que_new->que_next=NULL;
  que_prev->que_next=que_new;
  return(q);
}

/* Deletes a PCB by priority from the given queue */
struct queue_t* delete(struct queue_t *q,struct pcb_t *p){
  // List is already sorted by priority, just pull top off the list
  return(dequeue(q,p));
}

/* Checks whether a queue is empty or not */
int empty(struct queue_t *q){
  return(q==NULL);
}

/* Displays PCB's of all processes in the queue */
int display(struct queue_t *q){
  puts("       PID  Priority\n====================");
  if(empty(q))return(0);
  while(q!=NULL){
    printf("%10d  %d\n",q->pcb_item->pid,q->pcb_item->priority);
    q=q->que_next;
  }
  puts("");
  return(1);
}

