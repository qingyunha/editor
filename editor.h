void init();
void read_line();
void write_line();
void input();
void go_edit();
void connect();
void insert_chain();

void enter();
void quit();

void test();

#define LINESIZE 70

typedef struct Text
{
  struct Text *pre;
  struct Text *next;
  char text[LINESIZE];
}*TextL;

