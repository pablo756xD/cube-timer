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
  printf("solved in... %.2f\n", time);
  
  return time;
}

void append(float time, float *arr, int *num){
  arr[*num] = time;
  (*num)++;
  if(*num == 5){
    *num = 0;   
  }

}

void last_solves(float *avg5){
  printf("%s","Last solves:  ");
  for(int i = 0;i < 5;i++){
    printf("%.2f  ", avg5[i]);
  }

  printf("\n");

}

void sort(float *avg5){
  int size = 5;	
  for(int i = 0;i < size - 1; i++){
    for(int j = 0;j < size - i - 1;j++){
      if(avg5[j] > avg5[j+1]){
        float temp = avg5[j];
	avg5[j] = avg5[j+1];
	avg5[j+1] = temp;
      }
    }
  }

}

void foreach(float *avg5){ 
 printf("%s","Debug sort function:  ");
  for(int i = 0;i < 5;i++){
    printf("%.2f  ", avg5[i]);
  }

  printf("\n");
}

void loop(float *avg5){
  int counter = 0;	
  while(1){
    scramble();
    float current_time = timer();
    append(current_time, avg5,&counter);
    last_solves(avg5);
    sort(avg5);
    foreach(avg5);
  }

}


int main(){
  float average_of_five[5] = {0};
  srand(time(NULL));
  loop(average_of_five);
  return 0;

}
