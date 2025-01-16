#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 3
#define X 'X'
#define O 'O'

typedef struct
{
  int player;
  int computer;
  int draw;
} Score;

int difficulty;
Score score = {.player = 0, .computer = 0, .draw = 0};
void inputDifficulty();
void clearScreen();
void printBoard(char[SIZE][SIZE]);
int checkWin(char[SIZE][SIZE], char);
int checkDraw(char[SIZE][SIZE]);
void playGame();
void playerMove(char[SIZE][SIZE]);
void computerMove(char[SIZE][SIZE]);
int isValidMove(char[SIZE][SIZE], int, int);

int main()
{

  srand(time(NULL));

  int choice;
  inputDifficulty();
  do
  {
    playGame();
    printf("\nPlay again? (1 for YES, O for NO): ");
    scanf("%d", &choice);
  } while (choice == 1);
  printf("\nBye Bye thanks for playing.\n");
  return 0;
}

void playGame()
{
  char board[SIZE][SIZE] = {{
                                ' ',
                                ' ',
                                ' ',
                            },
                            {
                                ' ',
                                ' ',
                                ' ',
                            },
                            {
                                ' ',
                                ' ',
                                ' ',
                            }};
  char currentPlayer = rand() % 2 == 0 ? X : O;

  printBoard(board);
  while (1)
  {
    if (currentPlayer == X)
    {
      playerMove(board);
      printBoard(board);

      if (checkWin(board, X))
      {
        score.player++;
        printBoard(board);
        printf("\nCongratulations You have won.!!!");
        break;
      }
      currentPlayer = O;
    }
    else
    {
      computerMove(board);
      printBoard(board);

      if (checkWin(board, O))
      {
        score.computer++;
        printBoard(board);

        printf("\nI won!!! But you played well...");
        break;
      }
      currentPlayer = X;
    }

    if (checkDraw(board))
    {
      score.draw++;
      printBoard(board);
      printf("\nIt's a draw!");
      break;
    }
  }
}

int isValidMove(char board[SIZE][SIZE], int row, int col)
{
  return !(row < 0 || col < 0 || row > 2 || col > 2 || board[row][col] != ' ');
}

void playerMove(char board[SIZE][SIZE])
{
  int count = 0, x, y;
  for (int i = 0; i < SIZE; i++)
  {
    for (int j = 0; j < SIZE; j++)
    {
      if (board[i][j] == ' ')
      {
        count++;
        x = i;
        y = j;
      }
    }
  }

  if (count == 1)
  {
    board[x][y] = X;
    return;
  }

  int row, col;

  do
  {
    printf("\nPlayer X's turn.");
    printf("\nEnter row and column (1-3) for X: ");
    scanf("%d %d", &row, &col);
    // converting  to zero based
    row--;
    col--;
  } while (!isValidMove(board, row, col));

  board[row][col] = X;
}

void computerMove(char board[SIZE][SIZE])
{
  // 1.play for immediate win
  for (int i = 0; i < SIZE; i++)
  {
    for (int j = 0; j < SIZE; j++)
    {
      if (board[i][j] == ' ')
      {
        board[i][j] = O;
        if (checkWin(board, O))
        {
          return;
        }
        board[i][j] = ' ';
      }
    }
  }

  // 2.play for immediate block
  for (int i = 0; i < SIZE; i++)
  {
    for (int j = 0; j < SIZE; j++)
    {
      if (board[i][j] == ' ')
      {
        board[i][j] = X;
        if (checkWin(board, X))
        {
          board[i][j] = O;
          return;
        }
        board[i][j] = ' ';
      }
    }
  }

  // GOD MODE
  if (difficulty == 2)
  {
    // 3. Play center if available
    if (board[1][1] == ' ')
    {
      board[1][1] = O;
      return;
    }

    // 4. play corner available
    int corner[4][2] = {{0, 0}, {0, 2}, {2, 0}, {2, 2}};
    for (int i = 0; i < 4; i++)
    {
      if (board[corner[i][0]][corner[i][1]] == ' ')
      {
        board[corner[i][0]][corner[i][1]] = O;
        return;
      }
    }
  }

  // 5. Play first available move
  for (int i = 0; i < SIZE; i++)
  {
    for (int j = 0; j < SIZE; j++)
    {
      if (board[i][j] == ' ')
      {
        board[i][j] = O;
        return;
      }
    }
  }
}

void inputDifficulty()
{
  while (1)
  {
    printf("\nSelect Difficulty Level: ");
    printf("\n1 - Human (Standard)");
    printf("\n2 - God (Impossible to Win)");
    printf("\nEnter your choice: ");
    scanf("%d", &difficulty);

    if (difficulty != 1 && difficulty != 2)
    {
      printf("\nIncorrect choice! Enter (1/2).");
    }
    else
    {
      break;
    }
  }
}

void clearScreen()
{
#ifdef _Win32
  system("cls");
#else
  system("clear");
#endif
}

int checkWin(char board[SIZE][SIZE], char player)
{
  for (int i = 0; i < SIZE; i++)
  {
    // row check if every row contains the same player
    if (board[i][0] == player && board[i][1] == player && board[i][2] == player)
      return 1;

    // check column
    if (board[0][i] == player && board[1][i] == player && board[2][i] == player)
      return 1;
  }

  // check diagonal
  if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) || (board[0][2] == player && board[1][1] == player && board[2][0] == player))
    return 1;
  return 0;
}

int checkDraw(char board[SIZE][SIZE])
{
  for (int i = 0; i < SIZE; i++)
  {
    for (int j = 0; j < SIZE; j++)
    {
      if (board[i][j] == ' ')
        return 0;
    }
  }
  return 1;
}

void printBoard(char board[SIZE][SIZE])
{
  clearScreen();
  printf("\nScore - Player X: %d, Computer: %d, Draws: %d", score.player, score.computer, score.draw);
  printf("\nTic-Tac-Toe\n\n");

  // print board
  for (int i = 0; i < SIZE; i++)
  {
    for (int j = 0; j < SIZE; j++)
    {
      printf(" %c ", board[i][j]);
      if (j < SIZE - 1)
      {
        printf("|");
      }
    }
    if (i < SIZE - 1)
    {
      printf("\n---+---+---\n");
    }
  }
  printf("\n");
}
