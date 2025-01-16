#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main()
{
  int random, guess;
  int no_of_guess = 0;
  srand(time(NULL));

  // welcome message
  printf("Welcome to the world of Guessing Numbers.\n");


  random = rand()%(100-1+1) + 1; // Range[1,100] formula: rand()%(max-min+1) + min

  do
  {
    printf("\nPlease Enter Your Guess Between(1 to 100): ");
    scanf("%d",&guess);
    no_of_guess++;

    if(guess < random)
    {
      printf("Guess Larger Number.\n");
    }else if(guess > random) {
      printf("Guess Smaller Number.\n");
    }else {
      printf("Congratulations!!!You have successfully guessed the number in %d attemps.\n",no_of_guess);
    }

  } while (guess != random);
  
  printf("\nBye Bye, Thanks for playing.");
  printf("\nDev: chiranjib22\n");

  return 0;
}