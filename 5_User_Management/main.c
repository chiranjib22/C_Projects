#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<termios.h>


#define MAX_USERS 10
#define CREDENTIAL_LENGTH 30

typedef struct
{
  char userName[CREDENTIAL_LENGTH];
  char password[CREDENTIAL_LENGTH];
}User;

User users[MAX_USERS];
int userCount = 0;

void registerUser(); 
int loginUser(); // return user index
void fixFgetsIndex(char*);
void inputCredentials(char*,char*);

int main()
{
  int option;
  int userIndex;
  while(1){
    printf("\nWelcome to User Management.");
    printf("\n1.Register");
    printf("\n2.Login");
    printf("\n3.Exit");
    printf("\nSelect an option: ");
    scanf("%d",&option);
    getchar(); // consume extra enter

    switch (option)
    {
    case 1: // Register
      registerUser();
      break;
    case 2: // login
      userIndex = loginUser();
      if(userIndex>=0)
      {
        printf("\nLogin successful! Welcome %s\n",users[userIndex].userName);
      }
      else
      {
        printf("\nLogin Failed! Incorrect username or password.\n");
      }
      break;
    case 3: // exit
      printf("\nExiting Program!\n");
      return 0;
      break;
    default:
      printf("\nInvalid option. Please try again!!\n");
      break;
    }  
  }
  return 0;
}

void registerUser()
{
  if(userCount == MAX_USERS)
  {
    printf("\nMaximum %d user are registered. No more registration are allowed!!\n",MAX_USERS);
    return;
  }
  int newIndex = userCount;

  printf("\nRegister a new user\n");
  inputCredentials(users[newIndex].userName, users[newIndex].password);

  // increment userCount
  userCount++;
  printf("\nRegistration Successful!\n");
}

int loginUser()
{
  char username[CREDENTIAL_LENGTH];
  char password[CREDENTIAL_LENGTH];

  printf("\nLogin your account\n");
  inputCredentials(username,password);

  // checking in existing users
  for(int i = 0; i<userCount; i++)
  {
    if(strcmp(username,users[i].userName)==0 && strcmp(password,users[i].password)==0)
    {
      return i;
    }
  }
  return -1;
}

void inputCredentials(char* username,char *password)
{
  // input username
  printf("\nEnter Username: ");
  fgets(username,CREDENTIAL_LENGTH,stdin);
  fixFgetsIndex(username);

  // password input with masking
  printf("Enter Password (masking enabled): ");
  fflush(stdout);

  // change terminal properties
  struct termios old_props, new_props;
  tcgetattr(STDIN_FILENO,&old_props);
  new_props = old_props;
  new_props.c_lflag &= ~(ECHO | ICANON);
  tcsetattr(STDIN_FILENO,TCSANOW,&new_props);

  // input password
  char ch;
  int i = 0;
  while((ch = getchar()) !='\n' && ch != EOF)
  {
    if(ch == '\b' || ch == 127)
    {
      if(i>0){
        i--;
        printf("\b \b"); // backspace and delete
      }
    }
    else
    {
      password[i++] = ch;
      printf("*");
    }
  }
  password[i] = '\0';
  tcsetattr(STDIN_FILENO,TCSANOW,&old_props); // again old properties set
}

void fixFgetsIndex(char* string)
{
  int index = strcspn(string,"\n");
  string[index] = '\0';
}

