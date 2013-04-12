/* Process control block algorithm */
/* March 5, 2008 - CS421 - TS      */
/* By Jeremy VillEgAS              */

/* Different states of each PCB */
enum stateType{    
  ready,
  running,
  blocked
};

enum wait_state{
  busy,
  waiting
};

/* Waiting_list for RCB's */
struct rcb_waiting_list{
  int pid;
  struct rcb_waiting_list *next;
};

/* Resources */
struct rcb_t{
  int RID;
  enum wait_state status;
  struct rcb_waiting_list* wait_list; 
  struct rcb_t *rcb_next;
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
  
};

/* prototype declaration */
struct queue_t* enqueue(struct queue_t*,struct pcb_t*);
struct queue_t* dequeue(struct queue_t*,struct pcb_t*);
struct queue_t* insert(struct queue_t*,struct pcb_t*);
struct queue_t* delete(struct queue_t*,struct pcb_t*);
struct queue_t* create_operation(struct queue_t*,int,int);
struct queue_t* suspend_operation(struct queue_t*,struct pcb_t*);
struct queue_t* activate_operation(struct queue_t*,struct pcb_t*);
struct queue_t* destroy_operation(struct queue_t*,int);
int request_operation(struct rcb_t*,int);
int release_opeartion(struct pcb_t*,int);
struct rcb_t* build_resources();
struct queue_t *set_pcb_status(struct queue_t*,enum stateType);
int empty(struct queue_t*);
int display(struct queue_t*);
int invoke_scheduler();
char *strip_newline(char *str);
void doShell();

