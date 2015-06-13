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


void store(){
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
  yp->pre = qp;
  if(qp == NULL)
    kp = yp;
  else
    qp->next = yp;

  xp->next = NULL;
}

int get_string(){
  if(in[i] != ' '){
    strcpy(in, "?!");
    i = 2;
    write_line();
    return 1;
  }
  
  strcpy(mat,in+i+1);
  return 0;
}

int get_string1(){
  if(in[i] != ' '){
    strcpy(in, "?!");
    i = 2;
    write_line();
    return 1;
  }
  
  int j;
  for(j=0, i++; in[i] != 0 && in[i] != '/' && j < LINESIZE; j++,i++)
    mat[j] = in[i];
  mat[j+1] = '\0';
  return 0;
 }

int get_string2(){
  if(in[i] != '/'){
    strcpy(in, "?!");
    i = 2;
    write_line();
    return 1;
  }
  int j;
  for(j=0, i++; in[i] != 0 && in[i] != '/' && j < LINESIZE; j++,i++)
    rep[j] = in[i];

  rep[j+1] = '\0';
  in[i] = ' ';
  return 0;
}

int  comp(){
  return strncmp(mat, in+i, strlen(mat));
}


void find(){
  if(get_string()==1)
    return;

  if(tp == NULL){
    strcpy(in, "notext");
    i = 6;
    write_line();
    return;
  }

  if(bp == NULL)
    bp = tp;

  while(1){
    strcpy(in, bp->text);
    i = 0;

    while(1){
      if(comp()==0){
	i = strlen(in);
	write_line();
	return;
      }else
	i++;
      
      if(i >= LINESIZE)
	break;
    }

    if(bp->next != NULL)
      bp = bp->next;
    else
      break;
  }
  strcpy(in, "eof");
  i = 3;
  write_line();
}


void replace()
{
  if(get_string1()==1 || get_string2()==1 || get_number()==1)
    return;

  if(bp == NULL){
    if(tp == NULL){
      strcpy(in,"notext");
      i = 6;
      write_line();
      return;
    }
    else
      bp = tp;
  }

  int j, k;
  char temp[LINESIZE];
  ctr = num;
  while(ctr > 0){
    strcpy(in, bp->text);
    i = 0;
    k = strlen(mat);
    j = strlen(in);
    while(j - i >= strlen(mat)){
      if(comp()==0){
	strcpy(temp, in+i+k);
	strcpy(bp->text+i, rep);
	strcat(bp->text+i+strlen(rep),temp);
	ctr--;
	i = j;
	write_line();
	break;
      }else
	i++;
    }

    bp = bp->next;
    if(bp == NULL){
        strcpy(in, "eof");
	i = 3;
	write_line();
	return;
    }
    
  }
}
