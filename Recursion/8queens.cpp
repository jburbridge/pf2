#include <iostream>
using namespace std;

const int ROWS = 8;
const int COLS = 8;
char board[ROWS][COLS];

bool safe(int row, int col)
{
    //Check row
    for(int c = 0; c < COLS; c++)
        if(board[row][c] == 'Q')
            return false;

    //Check column
    for(int r = 0; r < ROWS; r++)
        if(board[r][col] == 'Q')
            return false;

    //Check forward diagonal
    for(int r = 0; r < ROWS; r++)
        for(int c = 0; c < COLS; c++)
            if(r + c == row + col && board[r][c] == 'Q')
                return false;

    //Check reverse diagonal
    for(int r = 0; r < ROWS; r++)
        for(int c = 0; c < COLS; c++)
            if(r - c == row - col && board[r][c] == 'Q')
                return false;

    return true;
}

bool solve(int col)
{
    if(col >= COLS)
        return true;

    else
    {
        for(int row = 0; row < ROWS; row++)
        {
            if(safe(row, col))
            {
                board[row][col] = 'Q';
                if(solve(col+1))
                    return true;
                else
                    board[row][col] = '.';
            }
        }
        return false;
    }
}

void print()
{
    for(int i = 0; i < ROWS; i++)
    {
        for(int j = 0; j < COLS; j++)
            cout << board[i][j] << " ";
        cout << "\n";
    }
}

int main()
{
    for(int i = 0; i < ROWS; i++)
        for(int j = 0; j < COLS; j++)
            board[i][j] = '.';

    print();
    cout << solve(0) << "\n";
    print();
    return 0;
}
