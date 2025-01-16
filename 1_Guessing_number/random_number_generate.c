#include<stdio.h>
#include<stdlib.h>
#include<time.h>
/*
// generate random numbers using rand function
void printRandomNumber(int min, int max, int count)
{
  printf("Random numbers between %d and %d : ",min,max);
  int i;
  for(i = 0; i<count; i++)
  {
    int rd_num = rand()%(max-min+1)+min;
    printf("%d ",rd_num);
  }
}
*/

/*
// generate random number using rand_r()
void printRandomNumber(int min, int max, int count)
{
  unsigned int seed = time(0);
  printf("Random numbers between %d and %d : ",min,max);
  int i;
  for(i = 0; i<count; i++)
  {
    int rd_num = rand_r(&seed)%(max-min+1)+min;
    printf("%d ",rd_num);
  }
}
*/

// generate random number using srand() and rand()
void printRandomNumber(int min, int max, int count)
{
  srand(time(0));
  printf("Random numbers between %d and %d : ",min,max);
  int i;
  for(i = 0; i<count; i++)
  {
    int rd_num = rand()%(max-min+1)+min;

    printf("%d ",rd_num);
  }
}
int main()
{
  int min,max,count;
  printf("Enter the minimum range and maximum range : ");
  scanf("%d %d",&min, &max);
  printf("\nEnter the count of random number: ");
  scanf("%d",&count);
  printRandomNumber(min,max,count);
  return 0;
}