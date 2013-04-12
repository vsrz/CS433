/* Kernel test module */

#include<stdio.h>
#include<stdlib.h>
#include"kernel1.h"

int main(void){
  struct pcb_t p1,p2,p3,p4,p5,p6,p7,p8,p9;
  /* Initalize test priority list */
  p1.priority=1;
  p1.pid=15970;
  p2.priority=3;
  p2.pid=9177;
  p3.priority=2;
  p3.pid=2344;
  p4.priority=9;
  p4.pid=18203;
  p5.priority=8;
  p5.pid=13911;
  p6.priority=7;
  p6.pid=9001;
  p7.priority=5;
  p7.pid=6667;
  p8.priority=4;
  p8.pid=27010;
  p9.priority=6;
  p9.pid=31337;

  /* Begin tests WL Queue */
  printf("Enqueuing 9 items into the WL Queue\n");
  WL=enqueue(WL,&p1);
  WL=enqueue(WL,&p2);
  WL=enqueue(WL,&p3);
  WL=enqueue(WL,&p4);
  WL=enqueue(WL,&p5);
  WL=enqueue(WL,&p6);
  WL=enqueue(WL,&p7);
  WL=enqueue(WL,&p8);
  WL=enqueue(WL,&p9);
  display(WL);
  printf("Dequeuing 2 items from the WL Queue\n");
  WL=dequeue(WL,&p9);
  WL=dequeue(WL,&p9);
  display(WL); 
  printf("Dequeuing 2 more items from the WL Queue\n");
  WL=dequeue(WL,&p9);
  WL=dequeue(WL,&p9);
  display(WL); 
  printf("Press enter to continue...");
  getchar();

  /* Begin tests SL Queue */
  printf("\nInserting 9 items by priority into the SL Queue\n");
  SL=insert(SL,&p1);
  SL=insert(SL,&p2);
  SL=insert(SL,&p3);
  SL=insert(SL,&p4);
  SL=insert(SL,&p5);
  SL=insert(SL,&p6);
  SL=insert(SL,&p7);
  SL=insert(SL,&p8);
  SL=insert(SL,&p9);
  display(SL);
  printf("Deleting 3 items from the SL Queue\n");
  SL=delete(SL,&p7);
  SL=delete(SL,&p7);
  SL=delete(SL,&p7);
  display(SL); 
  printf("Press enter to continue...");
  getchar();

  /* Begin tests UL Queue */
  printf("\nEnqueuing 9 items into the UL Queue\n");
  UL=enqueue(UL,&p1);
  UL=enqueue(UL,&p2);
  UL=enqueue(UL,&p3);
  UL=enqueue(UL,&p4);
  UL=enqueue(UL,&p5);
  UL=enqueue(UL,&p6);
  UL=enqueue(UL,&p7);
  UL=enqueue(UL,&p8);
  UL=enqueue(UL,&p9);
  display(UL);
  printf("Dequeuing 5 items from the UL Queue\n");
  UL=dequeue(UL,&p7);
  UL=dequeue(UL,&p7);
  UL=dequeue(UL,&p7);
  UL=dequeue(UL,&p7);
  UL=dequeue(UL,&p7);
  display(UL); 
  printf("Press enter to continue...");
  getchar();

  printf("\nFinally, display ALL queues\nWL Queue\n");
  display(WL);
  printf("SL Queue\n");
  display(SL);
  printf("UL Queue\n");
  display(UL);

  /* Clean up */
  while(UL=dequeue(UL,&p7));
  while(WL=dequeue(WL,&p7));
  while(SL=dequeue(SL,&p7)); 
  free(UL);
  free(WL);
  free(SL);
  return(0);
}
