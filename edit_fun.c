#include <stdio.h>
#include <string.h>
#include "editor.h"

int get_number()
{
  err = 0;
  if(in[i] == ' ')
    i++;
  else{
    strcpy(in, "?!");
    i = 3;
    write_line();
    return 1;
  }

  num = atoi(in+i);
  return 0;
}


void top()
{
  bp = NULL;
}

void up()
{
  if(get_number() == 1)
    return;
  ctr = num;

  if(tp == NULL){
    strcpy(in, "notext");
    i = 6;
    write_line();
    return;
  }

  if(bp == NULL){
    strcpy(in, "tof");
    i = 3;
    write_line();
    return;
  }
  
  while(ctr > 0){
    bp = bp->pre;
    ctr--;
    
    if(bp == NULL){
      strcpy(in, "tof");
      i = 3;
      write_line();
      return;
    }
  }//while

  strcpy(in, bp->text);
  i = strlen(bp->text);
  write_line();
 }



void list()
{
  if(get_number()==1)
    return;
  ctr = num;

  if(bp == NULL){
    if(tp == NULL){
      strcpy(in, "notext");
      i = 6;
      write_line();
      return;
    }
    else
      bp = tp;
  }

  strcpy(in, bp->text);
  i = strlen(bp->text);
  ctr--;
  write_line();
  
  while(ctr > 0){
    if(bp->next == NULL){
      strcpy(in, "eof");
      i = 3;
      write_line();
      return;
    }
    bp = bp->next;
    strcpy(in, bp->text);
    i = strlen(bp->text);
    //    printf("ctr : %d\n", ctr);
    ctr--;
    write_line();
  }//while
}


void next()
{
  if(get_number() == 1)
    return;
  ctr = num;

  if(bp == NULL){
    if(tp == NULL){
      strcpy(in, "notext");
      i = 6;
      write_line();
      return;
    }
    bp = tp;
    ctr--;
  }//if
  
  while(ctr > 0){
    if(bp->next == NULL){
      strcpy(in,"eof");
      i = 3;
      write_line();
      return;
    }
    bp = bp->next;
    ctr--;
  }

  strcpy(in, bp->text);
  i = strlen(bp->text);
  write_line();
}

void delete_link()
{
  yp = bp;
  xp = bp;
  ctr--;
  while(ctr > 0 && xp->next != NULL){
    xp = xp->next;
    ctr--;
  }

  if(xp->next == NULL){
    if(ctr > 0){
      strcpy(in, "eof");
      i = 3;
      write_line();
    }
    
    if(yp->pre == NULL){
      tp = NULL;
      bp = NULL;
    }else{
      bp = yp->pre;
      bp->next = NULL;
    }
  }
  else{
    bp = xp->next;
    if(yp->pre == NULL){
      tp = bp;
      bp->pre = NULL;
    }else{
      yp->pre->next = bp;
      bp->pre = yp->pre;
    }
  }
}


void delete()
{
  if(get_number()==1)
    return;
  ctr = num;

  if(bp == NULL){
    if(tp == NULL){
      strcpy(in, "notext");
      i = 6;
      write_line();
      return;
    }
    else
      bp = tp;
  }

  delete_link();
  xp->next = fp;
  if(fp != NULL)
    fp->pre = xp;

  yp->pre = NULL;
  fp = yp;
    
}


void copy(){

  
  if(get_number()==1)
    return;
  ctr = num;

  if(bp == NULL){
    if(fp == NULL){
      strcpy(in, "notext");
      i = 6;
      write_line();
      return;
    }
    else
      bp = tp;
  }
  
  yp = bp;
  xp = bp;
  sp = fp;

  if(sp == NULL){
    strcpy(in, "nofree");
    i = 6;
    write_line();
    return;
  }

  copy_line();

  if(sp == NULL)
    return;

  if(qp == NULL)
    kp = fp;
  else{
    fp->pre = qp;
    qp->next = fp;
  }

  qp = sp;
  fp = sp->next;
  qp->next = NULL;

  if(fp != NULL)
    fp->pre = NULL;
}


void copy_line(){
  while(1){
    strcpy(sp->text, xp->text);
    ctr--;
    if( ctr != 0 && xp->next != NULL)
      xp = xp->next;
    else
      break;

    if(sp->next == NULL){
      strcpy(in, "nofree");
      i = 6;
      sp = NULL;
      write_line();
      return;
    }
    
    sp = sp->next;
  }//while

  if(xp->next == NULL){
    if(ctr > 0){
      strcpy(in, "eof");
      i = 3;
      write_line();
    }
    bp = xp;
  }
  else
    bp = xp->next;
}


void insert()
{
  if(kp == NULL)
    return;
  
  yp = kp;
  xp = qp;
  kp = qp = NULL;
  
  insert_chain();
}
