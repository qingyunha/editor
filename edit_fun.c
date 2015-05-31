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
