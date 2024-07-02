#include <iostream>
#include <windows.h>
using namespace std;
// Function to change text color
void textcolor(int color)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, color);
    // RED = 4, GREEN = 2, BLUE = 1, YELLOW = 6, WHITE = 15
}
int main()
{
    static const int BSIZE = 3; // Board size
    // char board[BSIZE][BSIZE];
    char x = 'X';
    char o = 'O';
    // fill board
    /*for (int row = 0; row < BSIZE; row++)
    {
        for (int col = 0; col < BSIZE; col++)
        {
            board[row][col] = '-';
        }
    }*/

    /*
    cout << " --------------\n";
    for (int row = 0; row < BSIZE; row++)
    {
        cout << " | ";
        for (int col = 0; col < BSIZE; col++)
        {
            cout << board[row][col] << "  |";
        }
        cout << "\n --------------\n";
    }
    */

    /*
    cout << " " << board[0][0] << " | " << board[0][1] << " | " << board[0][2];
        cout << "\t\t 1 | 2 | 3 " << endl;
        cout << " " << board[1][0] << " | " << board[1][1] << " | " << board[1][2];
        cout << "\t\t 4 | 5 | 6 " << endl;
        cout << " " << board[2][0] << " | " << board[2][1] << " | " << board[2][2];
        cout << "\t\t 7 | 8 | 9 " << endl
             << endl;
    */
    char board[BSIZE][BSIZE] = {{'X', 'O', 'X'}, {' ', 'O', 'X'}, {'O', ' ', ' '}};

    for (int row = 0; row < 3; row++)
    {
        cout << "\t\t"; // Adds tab spacing for each row
        for (int col = 0; col < 3; col++)
        {
            cout << " ";
            // << board[row][col];
            if (board[row][col] == x)
            {
                textcolor(4);
            }
            else if (board[row][col] == o)
            {
                textcolor(2);
            }
            cout << board[row][col];

            textcolor(15);
            if (col < 2) cout << " |";
        }
    
        //guide board (will iterate 3 times)
        cout << "\t\t " << (row * 3) + 1 << " | " << (row * 3) + 2 << " | " << (row * 3) + 3;

        //guide board lines
        if (row < 2)
            cout << endl
                 << "\t\t-----------\t\t-----------";
        cout << endl;
    }
    cout << endl;
}