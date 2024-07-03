#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <windows.h>
#include <map>

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
    Game() : TotalMoves(0) { fill_board(); } // Constructor to initialize the board
    int totalMoves = TotalMoves;
    // Pure virtual functions for game operations
    virtual void displayBoard() const = 0;
    virtual void getUserMove(char players_O_X) = 0;
    virtual bool checkForWins(char players_O_X) const = 0;
    virtual bool checkForDraw() const = 0;

    // Functions to play the game
    virtual void playGame();
    virtual void playVsAI();

    // Function to switch players
    char togglePlayer(char players_O_X);

    // Function to initialize the board
    void fill_board();

protected:
    static const int BSIZE = 3;         // Board size
    static const int maxMoves = 9;      // Maximum number of moves
    static const int minMovesToWin = 5; // Minimum number of moves to win

    char board[BSIZE][BSIZE]; // Game board
private:
    int TotalMoves; // Counter for total moves
};

// Function to switch players
char Game::togglePlayer(char players_O_X)
{
    return (players_O_X == 'X') ? 'O' : 'X';
}

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

// # Function to play the game (to be overridden in derived class)
void Game::playGame()
{
    // This method will be overridden in the derived class.
}

// # Function to play against AI (to be overridden in derived class)
void Game::playVsAI()
{
    // This method will be overridden in the derived class.
}

// Derived class for TicTacToe game
class TicTacToe : public Game
{
public:
    // Constructor to initialize the board
    TicTacToe()
    {
        totalMoves = 0;
        fill_board();
    }

    // Override functions for game operations
    void displayBoard() const override;
    void getUserMove(char players_O_X) override;
    bool checkForWins(char players_O_X) const override;
    bool checkForDraw() const override;

    // Override function to play the game
    void playGame() override;

    string playerName_X;
    string playerName_O;

    string getUserName(string name, char mark);
};

// Function to display the game board
void TicTacToe::displayBoard() const
{
    // Loop through the board and display its contents
    char x = 'X';
    char o = 'O';

    for (int row = 0; row < 3; row++)
    {
        cout << "\t\t"; // Adds tab spacing for each row
        for (int col = 0; col < 3; col++)
        {
            cout << " ";
            // << board[row][col];
            if (board[row][col] == x)
            {
                textcolor(4);//red
            }
            else if (board[row][col] == o)
            {
                textcolor(2);//green
            }
            cout << board[row][col];

            textcolor(15);
            if (col < 2)
                cout << " |";
        }

        // guide board (will iterate 3 times)
        cout << "\t\t " << (row * 3) + 1 << " | " << (row * 3) + 2 << " | " << (row * 3) + 3;

        // guide board lines
        if (row < 2)
            cout << endl
                 << "\t\t-----------\t\t-----------";
        cout << endl;
    }
    cout << endl;
}

// Function to get names of the players
string TicTacToe::getUserName(string name, char mark)
{

    cout << "Who will play ";

    //to colorise X or O
    if (mark == 'X')
    {
        textcolor(4);//red
    }
    else
    {
        textcolor(2);//green
    }
    cout << mark;
    textcolor(15); // white
    cout << " (Enter name): ";

    //to colorise username
    if (mark == 'X')
    {
        textcolor(4);
    }
    else
    {
        textcolor(2);
    }
    getline(cin, name);
    textcolor(15); // white

    return name;
}
// Function to get user move and place it on the board
void TicTacToe::getUserMove(char players_O_X)
{
    string input;
    char char_entered;
    int num_entered, row, col, index;

    // switch player
    string player_turn = (players_O_X == 'X') ? playerName_X : playerName_O;

    while (true)
    {
        if (players_O_X == 'X')
        {
            textcolor(4);
            cout << playerName_X;
        }
        else
        {
            textcolor(2);
            cout << playerName_O;
        }
        textcolor(15); // white
        cout << " Where do you want to play? Select a number from 1-9: ";
        textcolor(4); // red

        getline(cin, input);
        textcolor(15); // white

        if (/*input != ""*/ !input.empty())
        {
            char_entered = input.c_str()[0];
            if (char_entered >= '1' && char_entered <= '9')
            {
                num_entered = char_entered - '0';
                index = num_entered - 1;
                row = index / 3;
                col = index % 3;

                char b_pos = board[row][col];
                if (b_pos != 'X' && b_pos != 'O')
                {
                    board[row][col] = players_O_X;
                    totalMoves++;
                    break;
                }
                else
                {
                    textcolor(4); // red
                    cout << "Wrong move. Position is already taken. Try again" << endl;
                    textcolor(15); // white
                }
            }
            else
            {
                textcolor(4); // red
                cout << "You must enter a number between 1-9 to make your move. Try again.\n";
                textcolor(15); // white
            }
        }
        else
        {
            textcolor(4); // red
            cout << "You must enter something!!" << endl;
            textcolor(15); // white
        }
    }
    cout << "Total moves: " << totalMoves << endl;
}

// Function to check if a player has won
bool TicTacToe::checkForWins(char players_O_X) const
{
    // Check if there are enough moves to win
    if (totalMoves >= minMovesToWin)
    {
        // Check rows and columns
        for (int i = 0; i < BSIZE; ++i)
        {
            if ((board[i][0] == players_O_X && board[i][1] == players_O_X && board[i][2] == players_O_X) || // Rows
                (board[0][i] == players_O_X && board[1][i] == players_O_X && board[2][i] == players_O_X))
            { // Columns
                return true;
            }
        }
        // Check diagonals
        if ((board[0][0] == players_O_X && board[1][1] == players_O_X && board[2][2] == players_O_X) || // Diagonal
            (board[0][2] == players_O_X && board[1][1] == players_O_X && board[2][0] == players_O_X))
        { // Anti-diagonal
            return true;
        }
    }
    return false;
}

// Function to check if the game is a draw
bool TicTacToe::checkForDraw() const
{
    return totalMoves == maxMoves;
}

// Function to play the game
void TicTacToe::playGame()
{
    char players_O_X = 'X';
    bool gameOver = false;
    playerName_X = getUserName(playerName_X, 'X');
    playerName_O = getUserName(playerName_O, 'O');
    do
    {
        displayBoard();
        getUserMove(players_O_X);
        if (checkForWins(players_O_X))
        {
            textcolor(2); // green
            cout << "\n *********** WE HAVE A WINNER!! ***********\n";
            // cout << ((players_O_X == 'X') ? playerName_X : playerName_O);

            //condition to colorise winners name
            if (players_O_X == 'X')
            {
                textcolor(4);
                cout << playerName_X;
            }
            else
            {
                textcolor(2);
                cout << playerName_O;
            }

            textcolor(2); // green
            cout << " WINS!!\n";
            textcolor(15); // white
            gameOver = true;
            break;
        }
        else if (checkForDraw())
        {
            textcolor(2); // green
            cout << "IT'S A DRAW! Play again!\n";
            textcolor(15); // white
            gameOver = true;
            break;
        }
        players_O_X = togglePlayer(players_O_X);
    } while (!gameOver);
    displayBoard();
}

// Derived class for TicTacToe game with AI
class TicTacToeVsAI : public TicTacToe
{
public:
    using TicTacToe::TicTacToe;      // Inherit constructors
    void compMove(char players_O_X); // Function for AI move
    void playVsAI() override;        // Override function to play against AI

    friend void displayWinner(TicTacToeVsAI &game, char players_O_X, string playerName_X); // Friend function declaration
};

// Friend function definition(used this to showcase the implementation of friend functions)
void displayWinner(TicTacToeVsAI &game, char players_O_X, string playerName_X)
{
    if (game.checkForWins(players_O_X))
    {
        // textcolor(2);//green
        // cout << "\n *********** WE HAVE A WINNER!! ***********\n"
        //      << ((players_O_X == 'X') ? playerName_X : "Computer") << " WINS!!\n";
        // textcolor(15);//white

        textcolor(2); // green
        cout << "\n *********** WE HAVE A WINNER!! ***********\n";

        if (players_O_X == 'X')
        {
            textcolor(4);
            cout << playerName_X;
        }
        else
        {
            textcolor(2);
            cout << "Computer";
        }
        textcolor(2);
        cout << " WINS!!\n";
        textcolor(15); // white
    }
}

// Function for AI move
void TicTacToeVsAI::compMove(char players_O_X)
{
    // AI makes a random move within the available board spaces
    srand(time(NULL));
    while (true)
    {
        int computer_choice = (rand() % 9) + 1;
        int row = (computer_choice - 1) / 3;
        int col = (computer_choice - 1) % 3;
        char bpos = board[row][col];
        if (bpos == 'X' || bpos == 'O')
        {
            continue;
        }
        else
        {
            textcolor(2); // green
            cout << "Computer";
            textcolor(15); // White
            cout << " will play at: " << computer_choice << endl;
            board[row][col] = players_O_X;
            totalMoves++;
            break;
        }
    }
    cout << "Total moves: " << totalMoves << endl;
}

// Function to play against AI
void TicTacToeVsAI::playVsAI()
{
    playerName_X = getUserName(playerName_X, 'X');
    char players_O_X = 'X';
    bool gameOver = false;

    do
    {
        displayBoard();
        getUserMove(players_O_X);
        if (checkForWins(players_O_X))
        {
            displayWinner(*this, players_O_X, playerName_X); // Using the friend function
            gameOver = true;
            break;
        }
        else if (checkForDraw())
        {
            cout << "IT'S A DRAW! Play again!\n";
            gameOver = true;
            break;
        }

        players_O_X = togglePlayer(players_O_X);

        compMove(players_O_X);
        if (checkForWins(players_O_X))
        {
            displayWinner(*this, players_O_X, playerName_X); // Using the friend function
            gameOver = true;
            break;
        }
        else if (checkForDraw())
        {
            cout << "IT'S A DRAW! Play again!\n";
            gameOver = true;
            break;
        }
        players_O_X = togglePlayer(players_O_X);
    } while (!gameOver);
    displayBoard();
}

// Map to store users and passwords
std::map<string, string> users = {
    {"wasee", "wasee"},
    {"rafay", "rafay"},
    {"younus", "younus"},
    {"p", "p"}};

string contributions()
{
    textcolor(4);
    cout << "\t\t\t\t      ***  TIC - TAC - TOE  ***\n\n";
    cout << "\t\t\t\tWELCOME TO TIC-TAC-TOE BY TEAM ROCKET\n"
         << endl;
    textcolor(3); // change color to green
    std::cout
        << "\t\t\t                     :: Abdur Rafay      (1013)\n"
        << "\t\t\tContributions        :: Al Abedin Wasee  (1042)\n"
        << "\t\t\t                     :: Younus Ali Molla (1047)\n"
        << "\t\t\t                     \n";

    textcolor(15); // reset color
}
// Function to display the menu and get user choice
char menu()
{
    char choice;

    textcolor(1);
    cout << "\t\t\tPick your choice" << endl;

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
    textcolor(1); // blue
    cin >> choice;
    textcolor(15); // white
    return choice;
}

// Function to check user password
bool Password()
{
    string username, password;
    textcolor(3);
    cout << "\t\t\tEnter username: ";
    textcolor(4);
    cin >> username;
    textcolor(3);
    cout << "\t\t\tEnter password: ";
    textcolor(4);
    cin >> password;
    cout << endl;
    textcolor(7);
    if (users.find(username) != users.end() && users[username] == password)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Function to execute commands based on user choice
void command()
{
    char command;
    Game *game = nullptr;

    if (!Password())
    {
        textcolor(4);
        cout << "Invalid username or password. Exiting program." << endl;
        textcolor(7);
        exit(0);
    }

    do
    {
        command = menu();
        switch (command)
        {
        case '1':
            cin.ignore();
            game = new TicTacToe();
            game->playGame();
            delete game;
            break;
        case '2':
            cin.ignore();
            game = new TicTacToeVsAI();
            game->playVsAI();
            delete game;
            break;
        }
        system("pause");
    } while (command != '0');
    exit(0);
}

// Main function to start the game
int main()
{
    contributions();
    command();
    cin.get();
    return 0;
}
