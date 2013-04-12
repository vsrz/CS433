/* Kernel1.C kernel project        */
/* March 5, 2008 - CS421 - TS      */
/* By Jeremy VillEgAS              */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"kernel2.h"

#define SYSTEM_QUEUE_THRESHOLD 1000

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
  if(q->pcb_item->priority>p->priority)return(que_new->que_next=q);  
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

/* Deletes a PCB by pid  */
struct queue_t* delete(struct queue_t *q,struct pcb_t *p){
  struct queue_t *que_cur=q,*que_next=NULL,*que_prev=NULL;
  /* no items in the queue */
  if(empty(q))return(NULL);
  /* not empty, is there only one item in the list? */
  if(que_cur->que_next==NULL){
    /* yes so do the PID's match? */
    if(q->pcb_item->pid==p->pid){
      /* delete this PID */
      free(q->pcb_item);
      q->pcb_item=NULL;
      return(q);
    } else return(NULL);  // item was not found in this list
  }

  /* there is more than one item in the list */
  while(que_cur!=NULL){
    /* does it match this one? */
    if(que_cur->pcb_item->pid==p->pid){
      if(que_prev==NULL)                /* Are we at the beginning? */
        q=que_cur->que_next;                /* Make a new head */
      else if(que_cur->que_next!=NULL)   // make sure we're not at the end
        que_cur=que_cur->que_next; 
      else if(que_cur->que_next==NULL)
        que_prev->que_next=NULL;      /* end of the list? */
      else                            /* we're somewhere in the middle */
        que_prev->que_next=que_cur->que_next;
      free(que_cur->pcb_item);
      free(que_cur);
      return(q);
    }
    /* the previous one's next should be the new item */
    que_cur=que_cur->que_next;
  }
  return(NULL);
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

void invoke_scheduler(struct queue_t* UL,struct queue_t* SL,struct queue_t* WL){
    
}
 
char* strip_newline(char *str){
  int i=0,sz=strlen(str);
  for(i;i<sz;++i)
    if(str[i]=='\n')
      str[i]='\0';
  return(str);
}

struct queue_t* create_operation(struct queue_t *q,int priority,int pcb_pid){
  struct pcb_t *p;
#ifdef DEBUG
  printf("Mem location of q: %d\n",q);
#endif
  /* Make the PCB to put in the queue */
  p=malloc(sizeof(struct pcb_t));
  p->pid=pcb_pid;
  p->priority=priority;
  p->pcb_status=ready;

  /* Insert the process into the Ready List (RL) */
  /* Call Scheduler process */
  return(insert(q,p));
}

struct queue_t* destroy_operation(struct queue_t *q,int pid){
  struct pcb_t *p;
  p=malloc(sizeof(struct pcb_t));
  p->pid=pid;
  p->priority=0;
  p->pcb_status=blocked;
 
  /* Find the correct pcb given the pid */
  /* Call Schedule process */
  return(delete(q,p));
}

int request_operation(struct rcb_t *r,int res){
  struct rcb_t *t;
#ifdef DEBUG
  printf("==REQUEST OPEARTION==\n");
#endif
  /* Check if the requested resource exists */
  while(r!=NULL){
    if(r->RID==res){
      t=r;
      r=NULL;
    }
#ifdef DEBUG
  printf("==Not here, try the next one==\n");
#endif
    r=r->rcb_next;
  }
  if(t==NULL)return(0);  // was the res found?
  /* is this resource busy? */
  if(t->status==busy){
#ifdef DEBUG
    printf("Requested resource %d was busy.\n",res);
#endif
    return(0);
  }
  /* allocate this resource */
  t->status=busy;
#ifdef DEBUG
  printf("Request for resource %d was successful!\n",res);   
#endif
  return(1);
}

struct queue_t* release_opeartion(struct queue_t *q,struct pcb_t *p){
  return(q);
}


struct rcb_t* build_resources(){
#ifdef DEBUG
  printf("==Building resources==\n");
#endif
  struct rcb_t *r1,*r2,*r3;
  r1=malloc(sizeof(struct rcb_t));
  r2=malloc(sizeof(struct rcb_t));
  r3=malloc(sizeof(struct rcb_t));
 
  /* resource 1 */
  r1->RID=1;
  r1->status=waiting;
  r1->wait_list=NULL;
  r1->rcb_next=r2; 

  /* resource 2 */
  r2->RID=1;
  r2->status=waiting;
  r2->wait_list=NULL;
  r2->rcb_next=r3; 

  /* resource 3 */
  r3->RID=1;
  r3->status=waiting;
  r3->wait_list=NULL;
  r3->rcb_next=NULL; 

#ifdef DEBUG
  printf("==Returning resources==\n");
#endif
  return(r1);
}

void doShell(){
  char str0[128],str1[128],str2[128];
  struct queue_t *q=NULL,*SL=NULL,*UL=NULL,*WL=NULL;
  struct rcb_t *RL=NULL;
  int pcb_pid=1000;
  printf("Loading vfkernel...\n\n");
  RL=build_resources(RL);  // build resources
#ifdef DEBUG
  printf("Memory address of RL's: %d, %d, %d",RL,RL->rcb_next,RL->rcb_next->rcb_next);
#endif
  do{
    int x=0;
    printf(">");
    scanf("%s",str0);
    /* Create Process */
    if(strncmp(str0,"cr",2)==0){
      scanf("%s",str1); 
      scanf("%s",str2);
      printf("* Creating %s with priority %s...\n",str1,str2);
#ifdef DEBUG
      printf("Mem location of UL: %d\n",UL);
#endif
      if(atoi(str2)>SYSTEM_QUEUE_THRESHOLD)SL=create_operation(SL,atoi(str2),pcb_pid++);
      else UL=create_operation(UL,atoi(str2),pcb_pid++);
#ifdef DEBUG
      printf("Mem location of UL: %d\n",UL);
#endif
      fflush(stdin);
    }else if(strncmp(str0,"di",2)==0){
#ifdef DEBUG
      printf("Last PID used: %d\n\n",pcb_pid-1);
#endif
      printf("WL Queue\n");
      display(WL);
      printf("\nUL Queue\n");
#ifdef DEBUG
      printf("*** pid of first item: %d\n",UL->pcb_item->pid); 
#endif
      display(UL);
      printf("\nSL Queue\n");
      display(SL);
    }else if(strncmp(str0,"de",2)==0){
      /* Destroy Process */
      scanf("%s",str1);
      printf("* Kill process with pid %s...\n",str1);
      UL=destroy_operation(UL,atoi(str1));
      SL=destroy_operation(SL,atoi(str1));
      fflush(stdin); 
    }else if(strncmp(str0,"r",1)==0){
      scanf("%s",str1);
      printf("* Requesting resource %d\n",atoi(str1));
      if(request_operation(RL,atoi(str1))==0)
        printf("Resource %d is unavailable\n",atoi(str1));
      fflush(stdin);
    }else if(strcmp(str0,"quit")!=0)printf("Bad command or file name\n");
  }while(strcmp(str0,"quit")!=0);
}

