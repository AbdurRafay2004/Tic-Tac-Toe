#include <iostream>
#include <string>
#include <ctime>
#include <windows.h>
using std::cin;
using std::cout;
using std::endl;
using std::string;

// Function to change text color
void textcolor(int color)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, color);
    // RED = 4, GREEN = 2, BLUE = 1, YELLOW = 6, WHITE = 15
}
class Game
{
public:
    Game() : totalMoves(0){ fill_board(); }
    void fill_board();
protected:
    static const int BSIZE = 3;         // Board size
    int maxMoves = 9;      // Maximum number of moves
    int minMovesToWin = 5; // Minimum number of moves to win
    char board[BSIZE][BSIZE];           // Game board
    int totalMoves;                     // Counter for total moves

};
// Function to initialize the board
void Game::fill_board()
{
    for (int row = 0; row < BSIZE; row++)
    {
        for (int col = 0; col < BSIZE; col++)
        {
            board[row][col] = '-';
        }
    }
}

class TicTacToe : public Game
{
};

class TicTacToeVsAI : public TicTacToe
{
};

char menu()
{
    char choice;
    textcolor(4);
    cout << "\t\t\t\t      ***  TIC - TAC - TOE  ***\n\n";
    cout << "\t\t\t\tWELCOME TO TIC-TAC-TOE BY TEAM ROCKET\n"
         << endl;
    textcolor(3); // change color to green
    std::cout
        << "\t\t\t                     :: Abdur Rafay      (1013)\n"
        << "\t\t\tContributions        :: Al Abedin Wasee  (1013)\n"
        << "\t\t\t                     :: Younus Ali Molla (1013)\n"
        << "\t\t\t                     \n";

    textcolor(15); // reset color

    textcolor(1);
    cout << "\t\t\t[1] ";
    textcolor(6);
    cout << "Player vs Player" << endl;
    textcolor(1);
    cout << "\t\t\t[2] ";
    textcolor(6);
    cout << "Player vs Computer" << endl;
    textcolor(1);
    cout << "\t\t\t[0] ";
    textcolor(6);
    cout << "Quit Game" << endl;
    textcolor(15);
    cin >> choice;
    return choice;
}

void command()
{
    // shows menu
    char command;
    do
    {
        command = menu();
        switch (command)
        {
        case '1':
            // player vs player

            break;
        case '2':
            // player vs AI
            break;
        }
        system("pause");
    } while (command != '0');
    exit(0);
}

int main()
{
    command(); // shows intro informations
    // char board[3][3]{
    //     {'-', '-', '-'},
    //     {'-', '-', '-'},
    //     {'-', '-', '-'}};

    // string Plyr1;
    // string Plyr2;
    // cout << "Enter player 1 name : ";
    // getline(cin, Plyr1);
    // cout << "Enter player 2 name : ";
    // getline(cin, Plyr2);

    return 0;
}