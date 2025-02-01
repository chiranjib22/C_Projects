#include <stdio.h>
#include <string.h>

typedef struct
{
  char name[50];
  int accNo;
  float balance;
} Account;

void createAccount();
void depositMoney();
void withdrawMoney();
void checkBalance();

const char *ACCOUNT_FILE = "account.dat";

int main()
{
  int choice;

  while (1)
  {
    printf("\n\n***Bank Management System***");
    printf("\n1. Create Account");
    printf("\n2. Deposit Money");
    printf("\n3. Withdraw Money");
    printf("\n4. Check balance");
    printf("\n5. Exit");
    printf("\nEnter Your choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1: // create account
      createAccount();
      break;
    case 2: // Deposit money
      depositMoney();
      break;
    case 3: // Withdraw money
      withdrawMoney();
      break;
    case 4: // check balance
      checkBalance();
      break;
    case 5: // close
      printf("\nClosing the bank. Thanks for your visit!!\n");
      return 0;
      break;
    default:
      printf("\nInvalid option!");
      break;
    }
  }
  return 0;
}

void createAccount()
{
  Account acc;

  // file checking
  FILE *fp;
  fp = fopen(ACCOUNT_FILE, "ab+");
  if (fp == NULL)
  {
    printf("\nUnable to open file!!");
    return;
  }

  // newline flushing
  char ch;
  do
  {
    ch = getchar();
  } while (ch != '\n' && ch != EOF);

  printf("\nEnter your name: ");
  fgets(acc.name, sizeof(acc.name), stdin);
  int newLineIndex = strcspn(acc.name, "\n");
  acc.name[newLineIndex] = '\0';
  printf("\nEnter your account no: ");
  scanf("%d", &acc.accNo);
  acc.balance = 0;

  // storing in file
  fwrite(&acc, sizeof(acc), 1, fp);
  fclose(fp);
  printf("\nAccount created successfully!!");
}

void depositMoney()
{
  int accountNo;
  float money;
  Account accRead;
  // file checking
  FILE *fp;
  fp = fopen(ACCOUNT_FILE, "rb+");
  if (fp == NULL)
  {
    printf("\nUnable to open file!!");
    return;
  }

  printf("\nEnter your account no: ");
  scanf("%d", &accountNo);
  printf("\nEnter amount to deposit: ");
  scanf("%f", &money);

  // scanning file
  while (fread(&accRead, sizeof(accRead), 1, fp))
  {
    // compare read account no with input account no
    if (accRead.accNo == accountNo)
    {
      accRead.balance += money;

      // move fp at one account backword
      fseek(fp, -sizeof(accRead), SEEK_CUR);
      // overwrite the account with new balance
      fwrite(&accRead, sizeof(accRead), 1, fp);
      fclose(fp);
      printf("Successfully deposited %.2f Tk. New Balance is %.2f Tk.", money, accRead.balance);
      return;
    }
  }
  fclose(fp);
  printf("\nMoney could not be deposited as account no %d was not found in records.", accountNo);
}

void withdrawMoney()
{
  int accountNo;
  Account accRead;
  float money;

  // file check
  FILE *fp = fopen(ACCOUNT_FILE, "rb+");
  if (fp == NULL)
  {
    printf("\nUnable to open file!!");
    return;
  }
  printf("\nEnter your account no: ");
  scanf("%d", &accountNo);
  printf("\nEnter the amount you wish to withdraw: ");
  scanf("%f", &money);

  // scanning in the file
  while (fread(&accRead, sizeof(accRead), 1, fp))
  {
    if (accRead.accNo == accountNo)
    {
      if (accRead.balance >= money)
      {
        accRead.balance -= money;
        fseek(fp, -sizeof(accRead), SEEK_CUR);
        fwrite(&accRead, sizeof(accRead), 1, fp);
        printf("\nSuccessfully withdrawn %.2f Tk. Remaining balance is %.2f Tk.", money, accRead.balance);
      }
      else
      {
        printf("\nInsufficient Balance.");
      }
      fclose(fp);
      return;
    }
  }
  fclose(fp);
  printf("\nMoney could not be withdrawn as account no %d was not found in records.", accountNo);
}

void checkBalance()
{
  int accountNo;
  Account accRead;
  // file checking
  FILE *fp;
  fp = fopen(ACCOUNT_FILE, "rb");
  if (fp == NULL)
  {
    printf("\nUnable to open file!!");
    return;
  }

  printf("\nEnter your account no: ");
  scanf("%d", &accountNo);

  // scanning file
  while (fread(&accRead, sizeof(accRead), 1, fp))
  {
    // compare read account no with input account no
    if (accRead.accNo == accountNo)
    {
      printf("\nYour account balance is %.2f Tk.", accRead.balance);
      fclose(fp);
      return;
    }
  }
  fclose(fp);
  printf("\nAccount No : %d was not found.", accountNo);
}