#include<stdio.h>
#include<math.h>

void printMenu()
{
  printf("\n\n===================================");  
  printf("\nWelcome to Simple Calculator.\n");
  printf("\nChoose one of the following option:");
  printf("\n1.Add");
  printf("\n2.Subtract");
  printf("\n3.Multiply");
  printf("\n4.Divide");
  printf("\n5.Modulus");
  printf("\n6.Power");
  printf("\n7.Exit");
  printf("\nNow enter your choice: ");
}

double division(double a, double b)
{
  if(b == 0)
  {
    fprintf(stderr,"Invalid Argument for Division");
    return NAN;
  }else{
    return a/b;
  }
}

double modulus(int a, int b)
{
  if(b == 0)
  {
    fprintf(stderr,"Invalid Argument for Modulus");
    return NAN;
  }else{
    return a%b;
  }

}

int main()
{
  int choice;
  double first, second, result;
  while(1){
    printMenu();
    scanf("%d",&choice);
    if(choice == 7)
      break;
    if(choice < 1 || choice > 7)
    {
      fprintf(stderr,"Invalid Menu Choice.");
      continue;
    }

    printf("\nEnter the first Number: ");
    scanf("%lf",&first);
    printf("Enter the Second Number: ");
    scanf("%lf",&second);

    switch (choice)
    {
      case 1: // Add
        result = first + second;
        break;
      case 2: // subtract
        result = first - second;
        break;
      case 3: // multiply
        result = first * second;
        break;
      case 4: // divide
        result = division(first,second);
        break;
      case 5: // modulus
        result = modulus(first,second);
        break;
      case 6: // power
        result = pow(first,second);
      break;
    }

    if(!isnan(result)){
      printf("\nResult of the operation is : %.2f",result);
    }
  }

  return 0;
}