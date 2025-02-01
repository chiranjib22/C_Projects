#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termio.h>
#include <time.h>
#include <sys/select.h>

#define HEIGHT 20
#define WIDTH 60

enum direction
{
  UP,
  DOWN,
  RIGHT,
  LEFT,
  STOP
};

enum direction dir;
int score = 0;
int foodX, foodY;
int headX, headY;
int tailLength;
int tailX[100];
int tailY[100];

struct termios old_props;
void clearScreen();
void setTerminalAttribute();
void resetTerminalAttribute();
void draw();
void input();
void setup();
int inputAvailable();
void gamePlay();

int main()
{
  srand(time(NULL));
  setTerminalAttribute();
  setup();
  while (1)
  {
    draw();
    input();
    gamePlay();
    int sleepTime = 3000000 / ((score != 0) ? score : 10);
    usleep(sleepTime);
    // sleep(1);
  }
  return 0;
}

void input()
{
  if (inputAvailable())
  {
    char ch = getchar();
    switch (ch)
    {
    case 'a':
      dir = LEFT;
      break;
    case 's':
      dir = DOWN;
      break;
    case 'd':
      dir = RIGHT;
      break;
    case 'w':
      dir = UP;
      break;
    case 'x':
      exit(0);
      break;
    }
  }
}

void gamePlay()
{
  for (int i = tailLength - 1; i > 0; i--)
  {
    tailX[i] = tailX[i - 1];
    tailY[i] = tailY[i - 1];
  }
  tailX[0] = headX;
  tailY[0] = headY;
  switch (dir)
  {
  case UP:
    headY--;
    break;
  case DOWN:
    headY++;
    break;
  case RIGHT:
    headX++;
    break;
  case LEFT:
    headX--;
    break;
  case STOP:
    // do nothing
    break;
  }

  if (headX < 0)
  {
    headX = WIDTH - 1;
  }
  else if (headX >= WIDTH)
  {
    headX = 0;
  }

  if (headY < 0)
  {
    headY = HEIGHT - 1;
  }
  else if (headY >= HEIGHT)
  {
    headY = 0;
  }

  for (int i = 0; i < tailLength; i++)
  {
    if (tailX[i] == headX && tailY[i] == headY)
    {
      printf("\nYou have hit your tail... GAME OVER!!!\n");
      exit(0);
    }
  }

  if (headX == foodX && headY == foodY)
  {
    score += 10;
    tailLength++;
    foodX = rand() % WIDTH;
    foodY = rand() % HEIGHT;
  }
}

// is input available from the keyboard
int inputAvailable()
{
  struct timeval tv = {0L, 0L};
  fd_set fds;
  FD_ZERO(&fds);   // Initialize fd_set
  FD_SET(0, &fds); // Add stdin (fd 0) to the set
  return select(1, &fds, NULL, NULL, &tv);
}

void setup()
{
  headX = WIDTH / 2;
  headY = HEIGHT / 2;

  foodX = rand() % WIDTH;
  foodY = rand() % HEIGHT;

  dir = STOP;
  score = 0;
  tailLength = 0;
}

void draw()
{
  clearScreen();
  printf("\tWelcome to The Snake Game!!!");
  printf("\n");
  for (int i = 0; i < WIDTH + 2; i++)
  {
    printf("#");
  }

  for (int i = 0; i < HEIGHT; i++)
  {
    printf("\n#");
    for (int j = 0; j < WIDTH; j++)
    {
      if (i == headY && j == headX)
      {
        printf("O");
      }
      else if (i == foodY && j == foodX)
      {
        printf("F");
      }
      else
      {
        int tailFound = 0;
        for (int k = 0; k < tailLength; k++)
        {
          if (tailX[k] == j && tailY[k] == i)
          {
            printf("o");
            tailFound = 1;
            break;
          }
        }
        if (!tailFound)
        {
          printf(" ");
        }
      }
    }
    printf("#");
  }

  printf("\n");
  for (int i = 0; i < WIDTH + 2; i++)
  {
    printf("#");
  }
  printf("\nScore: %d\n", score);
}

void setTerminalAttribute()
{
  // change terminal properties
  tcgetattr(STDIN_FILENO, &old_props);
  atexit(resetTerminalAttribute);
  struct termios new_props = old_props;
  new_props.c_lflag &= ~(ECHO | ICANON);
  tcsetattr(STDIN_FILENO, TCSANOW, &new_props);
}

void resetTerminalAttribute()
{
  // again old properties set
  tcsetattr(STDIN_FILENO, TCSANOW, &old_props);
}

void clearScreen()
{
#ifdef _Win32
  system("cls");
#else
  system("clear");
#endif
}
