#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<unistd.h>

int inputFormat();
void clearScreen();
char * fillTime(int);
char * fillDate();

int main()
{
  char *time;
  char *date;
  int format = inputFormat();

  while(1){
    time = fillTime(format);
    date = fillDate();
    clearScreen();
    printf("Current Time : %s\n",time);
    printf("Date : %s\n",date);
    sleep(1); // sleep for 1 second
  }
  return 0;
}

void clearScreen()
{
  system("clear");
}

int inputFormat()
{
  int format;
  printf("\nChoose the time format:");
  printf("\n1. 24 Hour Format:");
  printf("\n2. 12 Hour Format (default):");
  printf("\nMake a choice(1/2):");
  scanf("%d",&format);
  return format;
}

char * fillTime(int format)
{
  time_t raw_time;
  struct tm *current_time;
  char *buffer = (char *)malloc(sizeof(char)*50);

  time(&raw_time); // seeding current time
  current_time = localtime(&raw_time); // create an object of localtime of current time
  if(format == 1){
    strftime(buffer,sizeof(char)*50,"%H:%M:%S",current_time);
  }else{
    strftime(buffer,sizeof(char)*50,"%I:%M:%S %p",current_time);
  }
  return buffer;
}

char * fillDate()
{
  time_t raw_time;
  struct tm *current_time;
  char *buffer = (char *)malloc(sizeof(char)*100);

  time(&raw_time); // seeding current time
  current_time = localtime(&raw_time); // create an object of localtime of current time
  strftime(buffer,sizeof(char)*100,"%A %B %d %Y",current_time);
  return buffer;
}