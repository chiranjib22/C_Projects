#include <stdio.h>

void printPuzzle(int puzzle[9][9]);
int validMove(int puzzle[9][9], int row, int col, int val);
int solvePuzzle(int puzzle[9][9], int row, int col);
int validPuzzle(int puzzle[9][9]);
int isValidUnit(int array[]);

int puzzle[9][9] = {
    {3, 0, 0, 0, 2, 0, 0, 7, 0},
    {9, 0, 0, 5, 0, 0, 0, 1, 4},
    {0, 1, 6, 3, 7, 0, 0, 0, 8},
    {2, 0, 0, 8, 0, 0, 0, 0, 1},
    {5, 0, 0, 0, 4, 1, 8, 0, 0},
    {0, 8, 9, 0, 0, 0, 0, 5, 0},
    {0, 0, 5, 0, 1, 0, 2, 8, 0},
    {0, 4, 0, 0, 0, 6, 0, 9, 3},
    {7, 3, 1, 0, 8, 2, 0, 0, 0},
};

int main()
{
  printf("\n\tWelcome to SUDOKU solver!!");
  printf("\nOriginal Puzzle:");
  printPuzzle(puzzle);
  if (!validPuzzle(puzzle))
  {
    printf("\nThe puzzle is invalid!\n");
  }
  else if (solvePuzzle(puzzle, 0, 0))
  {
    printf("\nThe puzzle is solved:");
    printPuzzle(puzzle);
  }
  else
  {
    printf("\nThis puzzle is not solvable!");
  }
  return 0;
}

int solvePuzzle(int puzzle[9][9], int row, int col)
{
  if (col == 9)
  {
    if (row == 8)
    {
      return 1; // puzzle solved
    }
    col = 0;
    row++;
  }

  if (puzzle[row][col] > 0)
  {
    return solvePuzzle(puzzle, row, col + 1);
  }

  // using backtracking approach
  for (int i = 1; i <= 9; i++)
  {
    if (validMove(puzzle, row, col, i))
    {
      puzzle[row][col] = i;
      if (solvePuzzle(puzzle, row, col + 1))
      {
        return 1; // valid assumption
      }
      puzzle[row][col] = 0;
    }
  }
  return 0;
}

int validMove(int puzzle[9][9], int row, int col, int val)
{
  // valid row
  for (int i = 0; i < 9; i++)
  {
    if (puzzle[row][i] == val)
      return 0;
  }

  // valid column
  for (int i = 0; i < 9; i++)
  {
    if (puzzle[i][col] == val)
      return 0;
  }

  // valid square
  int r = row - row % 3;
  int c = col - col % 3;

  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 3; j++)
    {
      if (puzzle[r + i][c + j] == val)
        return 0;
    }
  }

  return 1;
}

int isValidUnit(int array[])
{
  int seen[9 + 1] = {0};
  for (int i = 0; i < 9; i++)
  {
    if (array[i] == 0)
      continue;
    if ((array[i] < 1 && array[i] > 9) || seen[array[i]])
      return 0;
    seen[array[i]] = 1;
  }
  return 1;
}

int validPuzzle(int puzzle[9][9])
{
  int unit[9];
  // check all rows
  for (int i = 0; i < 9; i++)
  {
    int index = 0;
    for (int j = 0; j < 9; j++)
    {
      unit[index++] = puzzle[i][j];
    }
    if (!isValidUnit(unit))
    {
      return 0;
    }
  }

  // check all columns
  for (int i = 0; i < 9; i++)
  {
    int index = 0;
    for (int j = 0; j < 9; j++)
    {
      unit[index++] = puzzle[j][i];
    }
    if (!isValidUnit(unit))
    {
      return 0;
    }
  }

  // check all square
  for (int row = 0; row < 9; row += 3)
  {
    for (int col = 0; col < 9; col += 3)
    {
      int index = 0;
      for (int i = row; i < row + 3; i++)
      {
        for (int j = col; j < col + 3; j++)
        {
          unit[index++] = puzzle[i][j];
        }
      }
      if (!isValidUnit(unit))
      {
        return 0;
      }
    }
  }
  return 1;
}

void printPuzzle(int puzzle[9][9])
{
  printf("\n+-------+-------+-------+");
  for (int row = 0; row < 9; row++)
  {
    if (row % 3 == 0 && row != 0)
    {
      printf("\n|-------+-------+-------|");
    }
    printf("\n");
    for (int col = 0; col < 9; col++)
    {
      if (col % 3 == 0)
      {
        printf("| ");
      }
      if (puzzle[row][col] != 0)
      {
        printf("%d ", puzzle[row][col]);
      }
      else
      {
        printf("  ");
      }
    }
    printf("|");
  }
  printf("\n+-------+-------+-------+\n");
}
