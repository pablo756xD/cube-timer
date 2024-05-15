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

    if (ch != EOF)
    {
        ungetc(ch, stdin);
        return 1;
    }

    return 0;
}

// timer functions

void scramble(void)
{
    char moves[] = {'R', 'L', 'F', 'B', 'U', 'D'};
    char mods[3] = {'2', '`', ' '};

    // create scramble
    int num = 0;
    while (num < 20)
    {
        int random_number = rand() % MAX;
        int temp;
        if (random_number != temp)
        {
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

float timer()
{
    float time = 0.00;
    printf("%s", "type Enter Key to start the timer...");
    getchar();
    getchar();
    while (!kbhit())
    {
        usleep(10000);
        time += 0.01;
        printf("\t\t\t\r%.2f ", time);
        fflush(stdout);
    }
    printf("\n");
    printf("solved in... %.2f\n", time);

    return time;
}

void updateAverage(float current_time, float *average_of_five, int *counter)
{
    average_of_five[*counter] = current_time;
    (*counter)++;
    if (*counter == 5)
    {
        *counter = 0;
    }
}

void loop(float *average_of_five)
{
    int counter = 0;
    while (1)
    {
        float current_time = timer();
        scramble();
        updateAverage(current_time, average_of_five, &counter);
    }
}

int main()
{
    float average_of_five[5] = {0};
    srand(time(NULL));
    loop(average_of_five);

    return 0;
}
