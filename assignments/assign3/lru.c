#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_TABLE_SIZE 4
#define MAX_PAGE_SIZE 16

int ptable[MAX_TABLE_SIZE]={-1,-1,-1,-1},fault=0,hit=0,n=0,pref[MAX_PAGE_SIZE];
int pcount[MAX_TABLE_SIZE]={0,0,0,0};
int main(int argc, char *argv[]){
  int x=0,curr=0;
  if(argc!=2){
    printf("Usage: %s <paging-ref>\n",argv[0]);
    exit(1);
  }
  for(x=0;(x<MAX_PAGE_SIZE)&&(x<strlen(argv[1]));x++){
    switch(argv[1][x]){
      case 48:
        pref[x]=0;
        break;
      case 49:
        pref[x]=1;
        break;
      case 50:
        pref[x]=2;
        break;
      case 51:
        pref[x]=3;
        break;
      case 52:
        pref[x]=4;
        break;
      case 53:
        pref[x]=5;
        break;
      case 54:
        pref[x]=6;
        break;
      case 55:
        pref[x]=7;
        break;
      case 56:
        pref[x]=8;
        break;
      case 57:
        pref[x]=9;
        break;
      default:
        pref[x]=-1;
        break;
    } 
  }
  for(x=0;x<MAX_PAGE_SIZE;x++){
    if(ptable[0]<0||ptable[x]==pref[curr]){  //load into first if empty
      ptable[0]=pref[curr];
      fault++;
    } else if(ptable[0]==pref[x]) hit++;
    pcount[x]++;
  } 
  printf("Number of faults: %d\nNumber of hits: %d\n",fault,hit);
  return(0);
}

