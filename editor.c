#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "editor.h"


int main()
{
  char ch;
  //test();
  init();
  while(1){
    read_line();
    if(ind != 0)
      input();
    else{
      i = 0;
      ch = in[i];
      switch(ch){
      case 't':
	top();
	break;

      case 'u':
	i++;
	up();
	break;

      case 'n':
	i++;
	next();
	break;

      case 'l':
	i++;
	list();
	break;

      case 'c':
	i++;
	copy();
	break;

      case 'i':
	insert();
	break;

      case 'q':
	quit();
	return 0;
	
      case 'e':
	enter();
	break;

      case 'd':
	i++;
	delete();
	break;

      case 'f':
	i++;
	find();
	break;

      case 'r':
	i++;
	replace();
	break;

      default:
	strcpy(in, "?!");
	i = 2;
	write_line();
      }//switch
    }//else
  }//while
  return 0;
}

void init(){
  cmp = chg = err = 0;
  ind = 0;
  i = 5;
  strcpy(in, "EDIT");
  write_line();
  bp = tp = NULL;
  kp = qp = NULL;
  
  fp = (TextL)malloc(MAXLINE*sizeof(struct Text));
  fp[0].pre = NULL;
  fp[MAXLINE-1].next = NULL;
  for(i = 0; i < MAXLINE-1; i++)
    fp[i].next = &fp[i+1];
  
  for(i = MAXLINE-1; i > 0; i--)
    fp[i].pre = &fp[i-1];
}

void read_line(){
  memset(in, 0, LINESIZE);
  i = 0;
  while(1){
    read(0, buf, 1);
    switch(buf[0]){
    case '@':
      if(i != 0)
    	in[--i] = ' ';
      break;

    case '#':
      in[0] = ' ';
      i = 0;
      break;

    case '\n':
      if(i == 0)
    	in[i++] = '\n';
      return;

    default:
      in[i++] = buf[0];
    }
    
  }
}

void write_line()
{
  int j;
  for(j=0; j<i; j++){
    buf[0] = in[j];
    write(1, buf, 1);
  }
  buf[0] = '\n';
  write(1, buf, 1);
}

void input()
{
  char ch = in[0];
  if(ind == 1)
    if(ch == '\n')
      go_edit();
    else
      if(fp == NULL){
	strcpy(in, "nofree");
	i = 6;
	write_line();
      }else{
        xp = fp;
	strncpy(xp->text, in, i);
	ind = 2;
      }
  else
    if(ch == '\n'){
      connect();
      insert_chain();
      go_edit();
    }else
      if(xp->next == NULL){
	connect();
	insert_chain();
	strcpy(in,"nofree");
	i = 6;
	write_line();
	go_edit();
      }else{
	xp = xp->next;
	strncpy(xp->text, in, i);
      }
}


void go_edit()
{
  ind = 0;
  strcpy(in, "EDIT");
  i = 4;
  write_line();
}

void connect()
{
  yp = fp;
  fp = xp->next;
  if(fp)
    fp->pre = NULL;
}

void insert_chain()
{
  TextL sp;
  if(bp == NULL){
    if(tp == NULL)
      sp = tp;
    else{
      tp->pre = xp;
      sp = tp;
    }
    tp = yp;
  }else{
    sp = bp->next;
    yp->pre = bp;
    bp->next = yp;
    if(sp){
      sp->pre = xp;
    }
  }
  xp->next = sp;
}

void enter()
{
  ind = 1;
  strcpy(in, "INPUT");
  i = 6;
  write_line();
}

void quit()
{
  TextL p;
  p = tp;
  while(p){
    write(1, p->text, 70);
    putchar('\n');
    p = p->next;
  }
  return;
}

void test()
{
 
}
