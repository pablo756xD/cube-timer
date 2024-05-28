#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <string.h>

#define MAX 6
#define MAXM 3
#define SIZE1 5
#define SIZE2 12
 
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

/*void append(float time, float *arr, int *num, int size, int *num2){
  arr[*num] = time;
  (*num)++;
  if(*num > size -1){
    *num = 0;   
  }
  (*num2)++;
}*/

void shift_array(float *arr, int size, float time, int *num2){
  for(int i = size - 1; i > 0;i--){
    arr[i] = arr[i -1];
  }
  arr[0] = time;
  (*num2)++;
}

void print_array(float *arr, int size, char message[]){
  printf("%s:", message);
  for(int i = 0; i <= size - 1;i++){
    printf(" %.2f ", arr[i]);
  }
  printf("\n");
}

void copy_array(float *src, float *dest, int size){
  memcpy(dest,src,5*sizeof(float));
}
void sort(float *avg5){
  int size = 5;	
  for(int i = 0;i < size; i++){
    for(int j = 0;j < size - i - 1;j++){
      if(avg5[j] > avg5[j+1]){
        float temp = avg5[j];
	avg5[j] = avg5[j+1];
	avg5[j+1] = temp;
      }
    }
  }
}

void average(float *arr, int *num){
  // for five
  if(*num > 4){
    float total = (arr[1] + arr[2] + arr[3]) / 3.0;
    printf("AVG 5:   %.2f \n", total);
  }

}

void loop(float *avg5, float *savg5){
  int counter = 0;	 
  int counter2 = 0;
  int counter3 = 0;
  while(1){
    scramble();
    float current_time = timer();
    shift_array(avg5, SIZE1, current_time, &counter2);
    print_array(avg5,SIZE1,"last solves: ");
    copy_array(avg5,savg5, SIZE1);
    sort(savg5);
    average(savg5, &counter2);
  }

}

int main(){
  float average_of_five[5] = {0};
  float sorted_of_five[5] = {0};
  srand(time(NULL));
  loop(average_of_five, sorted_of_five);
  return 0;

}
