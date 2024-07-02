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
    Game() : totalMoves(0) { fill_board(); } // Constructor to initialize the board

    // Pure virtual functions for game operations
    virtual void displayBoard() const = 0;            
    virtual void getUserMove(char player) = 0;       
    virtual bool checkForWins(char player) const = 0; 
    virtual bool checkForDraw() const = 0;         
    
    // Function to switch players
    char togglePlayer(char player);

    // Functions to play the game
    virtual void playGame();    
    virtual void playVsAI(); 

    // Function to initialize the board
    void fill_board();  

protected:
    static const int BSIZE = 3;         // Board size
    static const int maxMoves = 9;      // Maximum number of moves
    static const int minMovesToWin = 5; // Minimum number of moves to win

    char board[BSIZE][BSIZE];           // Game board
    int totalMoves;                     // Counter for total moves
};

// Function to switch players
char Game::togglePlayer(char player)
{
    return (player == 'X') ? 'O' : 'X';
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

// Function to play the game (to be overridden in derived class)
void Game::playGame()
{
    // This method will be overridden in the derived class.
}

// Function to play against AI (to be overridden in derived class)
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
    void getUserMove(char player) override;      
    bool checkForWins(char player) const override; 
    bool checkForDraw() const override;

    // Override function to play the game
    void playGame() override; 
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

// Function to get user move and place it on the board
void TicTacToe::getUserMove(char player)
{
    string input;
    char char_entered;
    int num_entered, row, col, index;
    int player_turn = (player == 'X') ? 1 : 2;

    while (true)
    {
        cout << "Player " << player_turn << " Where do you want to play? Select a number from 1-9: " << endl;
        getline(cin, input);

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
                    board[row][col] = player;
                    totalMoves++;
                    break;
                }
                else
                {
                    cout << "Wrong move. Position is already taken. Try again" << endl;
                }
            }
            else
            {
                cout << "You must enter a number between 1-9 to make your move. Try again.\n";
            }
        }
        else
        {
            cout << "You must enter something!!" << endl;
        }
    }
    cout << "Total moves: " << totalMoves << endl;
}

// Function to check if a player has won
bool TicTacToe::checkForWins(char player) const
{
    // Check if there are enough moves to win
    if (totalMoves >= minMovesToWin)
    {
        // Check rows and columns
        for (int i = 0; i < BSIZE; ++i)
        {
            if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) || // Rows
                (board[0][i] == player && board[1][i] == player && board[2][i] == player))
            { // Columns
                return true;
            }
        }
        // Check diagonals
        if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) || // Diagonal
            (board[0][2] == player && board[1][1] == player && board[2][0] == player))
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
    char player = 'X';
    bool gameOver = false;
    do
    {
        displayBoard();
        getUserMove(player);
        if (checkForWins(player))
        {
            cout << "\n *********** WE HAVE A WINNER!! ***********\n"
                 << player << " WINS!!\n";
            gameOver = true;
        }
        else if (checkForDraw())
        {
            cout << "IT'S A DRAW! Play again!\n";
            gameOver = true;
        }
        player = togglePlayer(player);
    } while (!gameOver);
    displayBoard();
}

// Derived class for TicTacToe game with AI
class TicTacToeVsAI : public TicTacToe
{
public:
    using TicTacToe::TicTacToe;   // Inherit constructors
    void compMove(char player);   // Function for AI move
    void playVsAI() override;     // Override function to play against AI

    friend void displayWinner(TicTacToeVsAI &game, char player); // Friend function declaration
};

// Friend function definition
void displayWinner(TicTacToeVsAI &game, char player)
{
    if (game.checkForWins(player))
    {
        cout << "\n *********** WE HAVE A WINNER!! ***********\n"
             << player << " WINS!!\n";
    }
}

// Function for AI move
void TicTacToeVsAI::compMove(char player)
{
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
            cout << "Computer will play at: " << computer_choice << endl;
            board[row][col] = player;
            totalMoves++;
            break;
        }
    }
    cout << "Total moves: " << totalMoves << endl;
}

// Function to play against AI
void TicTacToeVsAI::playVsAI()
{
    char player = 'X';
    bool gameOver = false;
    do
    {
        displayBoard();
        getUserMove(player);
        if (checkForWins(player))
        {
            displayWinner(*this, player); // Using the friend function
            gameOver = true;
        }
        else if (checkForDraw())
        {
            cout << "IT'S A DRAW! Play again!\n";
            gameOver = true;
        }

        player = togglePlayer(player);

        compMove(player);
        if (checkForWins(player))
        {
            displayWinner(*this, player); // Using the friend function
            gameOver = true;
        }
        else if (checkForDraw())
        {
            cout << "IT'S A DRAW! Play again!\n";
            gameOver = true;
        }
        player = togglePlayer(player);
    } while (!gameOver);
    displayBoard();
}

// Map to store users and passwords
std::map<string, string> users = {
    {"Wasee", "wasee"},
    {"Rafay", "rafay"},
    {"Younus", "younus"}};

// Function to display the menu and get user choice
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

// Function to check user password
bool Password()
{
    string username, password;
    textcolor(3);
    cout << "Enter username: ";
    textcolor(4);
    cin >> username;
    textcolor(3);
    cout << "Enter password: ";
    textcolor(4);
    cin >> password;
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
    command();
    cin.get();
    return 0;
}
