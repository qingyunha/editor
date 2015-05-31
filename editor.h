void init();
void read_line();
void write_line();
void input();
void go_edit();
void connect();
void insert_chain();

void enter();
void quit();

void top();
void up();
void next();
void list();
int get_number();

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

TextL bp, tp;
TextL kp, qp;
TextL fp;
TextL xp, yp;

int ctr;
int num;
