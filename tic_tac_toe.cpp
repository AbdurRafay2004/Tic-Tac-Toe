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

// Base class representing the general structure of a game
class Game
{
public:
    Game() : totalMoves(0) { fill_board(); }
    void fill_board();
    virtual void displayBoard() const = 0;            // Pure virtual function for displaying the board
    //need to get user input
    //checkwin
    //checkdraw
    //switch player
    virtual void playGame() = 0;                      // Function to play the game
    //ai
protected:
    static const int BSIZE = 3; // Board size
    int maxMoves = 9;           // Maximum number of moves
    int minMovesToWin = 5;      // Minimum number of moves to win
    char board[BSIZE][BSIZE];   // Game board
    int totalMoves;             // Counter for total moves
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
public:
    // Constructor to initialize the board
    TicTacToe()
    {
        totalMoves = 0;
        fill_board();
    }
    void displayBoard() const override;            // Override function to display the board
    void playGame() override;           // Override function to
};

void TicTacToe::displayBoard() const
{
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
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            cout << " " << board[row][col];
            if (col < 2) cout << " |";
        }
    cout << "\t\t " << (row * 3) + 1 << " | " << (row * 3) + 2 << " | " << (row * 3) + 3;
    if (row < 2) cout << endl << "-----------\t\t-----------";
    cout << endl;
    }
    cout << endl;
}

void TicTacToe::playGame(){
    displayBoard();
}
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
    Game *game = nullptr;
    do
    {
        command = menu();
        switch (command)
        {
        case '1':
            // player vs player
            game = new TicTacToe();
            game->playGame();

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