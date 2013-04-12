/* Process control block algorithm */
/* March 5, 2008 - CS421 - TS      */
/* By Jeremy VillEgAS              */

/* Different states of each PCB */
enum stateType{    
  ready,
  running,
  blocked
};

/* PCB Status Table */
struct rcb_status{
  enum stateType state;
  /* Ready/Waiting List Process Dependent */ 
};

/* Resources */
struct rcb_t{
  int RID;
  struct rcb_status Status;
  // also a Waiting List  
};
  
/* PCB Creation Tree */
struct pcb_tree{
  int pid_parent;
  struct pcb_t *pcb_child;
};

/* Queue struct */
struct queue_t{
  struct queue_t *que_next;
  struct pcb_t *pcb_item;
};

/* Main PCB struct */
struct pcb_t{
  int pid,priority;
  enum stateType pcb_status;
  struct rcb_t *pcb_resource;
  struct pcb_tree *pcb_ctree;
};

/* prototype declaration */
struct queue_t* enqueue(struct queue_t*,struct pcb_t*);
struct queue_t* dequeue(struct queue_t*,struct pcb_t*);
struct queue_t* insert(struct queue_t*,struct pcb_t*);
struct queue_t* delete(struct queue_t*,struct pcb_t*);
int empty(struct queue_t*);
int display(struct queue_t*);

/* global queue lists */
struct queue_t *WL,*SL,*UL;


