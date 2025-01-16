#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>


const int BAR_LENGTH = 50;
const int MAX_TASKS = 5;
typedef struct
{
  int id;
  int progress;
  int step;
}Task;


void printBar(Task);
void clearScreen();


int main()
{
  Task tasks[MAX_TASKS];
  srand(time(NULL));

  // all tasks initialization
  for(int i = 0; i<MAX_TASKS; i++)
  {
    tasks[i].id = i + 1;
    tasks[i].progress = 0;
    tasks[i].step = rand()% 5 + 1; // give them random step
  }

  // task progress tracking
  int task_incomplete = 1;
  while(task_incomplete)
  {
    clearScreen();
    task_incomplete = 0;
    for(int i = 0; i<MAX_TASKS; i++)
    {
      tasks[i].progress += tasks[i].step;
      if(tasks[i].progress > 100)
      {
        tasks[i].progress = 100;
      }else if(tasks[i].progress < 100)
      {
        task_incomplete = 1;
      }
      printBar(tasks[i]);
    }
    sleep(1);
  }
  printf("All task completed.\n");
  return 0;
}

void clearScreen()
{
  system("clear");
}

void printBar(Task task)
{
  int bar_to_show = task.progress * BAR_LENGTH/100;

  printf("\nTask %d:[",task.id);

  for(int i = 0;i<BAR_LENGTH; i++)
  {
    if(i<bar_to_show)
    {
      printf("=");
    }else{
      printf(" ");
    }
  }
  printf("] %d%%\n",task.progress);
}