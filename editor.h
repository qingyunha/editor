void init();
void read_line();
void write_line();
void input();
void go_edit();
void connect();
void insert_chain();

void enter();
void quit();

int get_number();
void top();
void up();
void next();
void list();
void delete();
void delete_line();
void copy_line();
void copy();
int get_string();
int get_string1();
int get_string2();

void test();

#define LINESIZE 70
#define MAXLINE 1000

typedef struct Text
{
  struct Text *pre;
  struct Text *next;
  char text[LINESIZE];
}*TextL;

int cmp, chg, err;
int ind;
char in[LINESIZE];
int i;

char buf[LINESIZE];
char mat[LINESIZE];
char rep[LINESIZE];

TextL bp, tp; //current, text 
TextL kp, qp; //work first line, work last line
TextL fp;     //free 


TextL xp, yp; //temp  
TextL sp;     //temp

int ctr;
int num;
