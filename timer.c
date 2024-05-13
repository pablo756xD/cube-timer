#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#define MAX 6
#define MAXM 3


 
int kbhit(void)
{
  struct termios oldt, newt;
  int ch;
  int oldf;
 
  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
 
  ch = getchar();
 
  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);
 
  if(ch != EOF)
  {
    ungetc(ch, stdin);
    return 1;
  }
 
  return 0;
}


// timer functions

void scramble(void){
  char moves[] = {'R', 'L','F', 'B', 'U','D'};
  char mods[3] = {'2', '`', ' '};

  // create scramble
  int num = 0;
  while(num < 20){
    int random_number = rand() % MAX;
    int temp;
    if(random_number != temp){
      printf("%c", moves[random_number]);
      printf("%c", mods[rand() % MAXM]);
      printf("  ");
      num++;
      temp = random_number;
    }
  }
  printf("\n");
  printf("\n");
}

float timer(){
  float time = 0.00;
  printf("%s", "type Enter Key to start the timer...");
  getchar();
  getchar();
  while(!kbhit()){
    usleep(10000);
    time += 0.01;
    printf("\t\t\t\r%.2f ", time);
    fflush(stdout);
  }
  printf("\n");
  return time;
}

void loop(float time){
  while(1){
    scramble();
    time = timer();
  }

}

int main(){
  float currentTime = 0;
  srand(time(NULL));
  loop(currentTime);
  
  return 0;

}
