# Tic Tac Toe using Minimax Algorithm
## A Terminal-based C++ Implementation

### Person 1: Project Structure and Base Game Implementation (Slides 1-5)

#### Slide 1: Title and Team Introduction
- Project: Tic Tac Toe using Minimax Algorithm
- Team Members: [Your Names]
- Course: [Your Course Name]

#### Slide 2: Project Architecture
- Explain the class hierarchy:
  - `Game`: Abstract base class
  - `TicTacToe`: Derived class for basic game
  - `TicTacToeVsAI`: Further derived class for AI opponent
- Highlight the use of inheritance and polymorphism

#### Slide 3: Game Class Implementation
```cpp
class Game {
public:
    Game() : TotalMoves(0) { fill_board(); }
    int totalMoves = TotalMoves;
    virtual void displayBoard() const = 0;
    virtual void getUserMove(char players_O_X) = 0;
    virtual bool checkForWins(char players_O_X) const = 0;
    virtual bool checkForDraw() const = 0;
    virtual void playGame();
    virtual void playVsAI();
    char togglePlayer(char players_O_X);
    void fill_board();

protected:
    static const int BSIZE = 3;
    static const int maxMoves = 9;
    static const int minMovesToWin = 5;
    char board[BSIZE][BSIZE];
private:
    int TotalMoves;
};
```
- Explain the purpose of each virtual function
- Discuss the significance of the `protected` and `private` members

#### Slide 4: TicTacToe Class Key Functions
```cpp
class TicTacToe : public Game {
public:
    TicTacToe() { totalMoves = 0; fill_board(); }
    void displayBoard() const override;
    void getUserMove(char players_O_X) override;
    bool checkForWins(char players_O_X) const override;
    bool checkForDraw() const override;
    void playGame() override;
    string getUserName(string name, char mark);
};
```
- Highlight the overridden functions
- Explain the `getUserName` function for player interaction

#### Slide 5: Game Logic Implementation
- Discuss the `playGame` function in `TicTacToe` class
- Explain the game loop, turn switching, and win/draw checking
- Highlight the use of the `textcolor` function for UI enhancement

### Person 2: AI Implementation and Minimax Algorithm (Slides 6-10)

#### Slide 6: TicTacToeVsAI Class Structure
```cpp
class TicTacToeVsAI : public TicTacToe {
public:
    using TicTacToe::TicTacToe;
    void compMove(char players_O_X, bool isHardMode);
    void playVsAI() override;
private:
    int minimax(char board[3][3], int depth, bool isMaximizing, char aiPlayer, char humanPlayer);
    void findBestMove(char board[3][3], int &row, int &col, char aiPlayer, char humanPlayer);
    char checkWinner(char board[3][3]);
};
```
- Explain the additional functions for AI gameplay
- Discuss the `compMove` function and its `isHardMode` parameter

#### Slide 7: Minimax Algorithm Implementation
```cpp
int TicTacToeVsAI::minimax(char board[3][3], int depth, bool isMaximizing, char aiPlayer, char humanPlayer) {
    char result = checkWinner(board);
    if (result == aiPlayer) return 10 - depth;
    if (result == humanPlayer) return depth - 10;
    if (result == 'T') return 0;

    if (isMaximizing) {
        int bestScore = -1000;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i][j] == '-') {
                    board[i][j] = aiPlayer;
                    int score = minimax(board, depth + 1, false, aiPlayer, humanPlayer);
                    board[i][j] = '-';
                    bestScore = std::max(score, bestScore);
                }
            }
        }
        return bestScore;
    } else {
        // Minimizing player logic (similar to maximizing)
    }
}
```
- Explain the recursive nature of the algorithm
- Discuss the scoring system and depth consideration

#### Slide 8: Finding the Best Move
```cpp
void TicTacToeVsAI::findBestMove(char board[3][3], int &row, int &col, char aiPlayer, char humanPlayer) {
    int bestScore = -1000;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == '-') {
                board[i][j] = aiPlayer;
                int score = minimax(board, 0, false, aiPlayer, humanPlayer);
                board[i][j] = '-';
                if (score > bestScore) {
                    bestScore = score;
                    row = i;
                    col = j;
                }
            }
        }
    }
}
```
- Explain how this function uses minimax to evaluate all possible moves
- Discuss the selection of the best move based on scores

#### Slide 9: AI Move Implementation
```cpp
void TicTacToeVsAI::compMove(char players_O_X, bool isHardMode) {
    if (isHardMode) {
        int row, col;
        findBestMove(board, row, col, players_O_X, (players_O_X == 'X') ? 'O' : 'X');
        board[row][col] = players_O_X;
        totalMoves++;
    } else {
        // Easy mode logic (random moves)
    }
}
```
- Explain the difference between hard mode (minimax) and easy mode (random)
- Discuss how this function integrates with the main game loop

#### Slide 10: PlayVsAI Function
- Explain the game loop for AI gameplay
- Discuss how it alternates between player and AI moves
- Highlight the difficulty selection feature

### Person 3: User Interface, Authentication, and Project Conclusion (Slides 11-15)

#### Slide 11: User Interface Implementation
- Discuss the use of `textcolor` for enhanced visual feedback
- Explain the board display function and its color coding
- Highlight the input handling and validation in `getUserMove`

#### Slide 12: User Authentication System
```cpp
bool registerUser() {
    // Implementation details
}

bool loginUser() {
    // Implementation details
}
```
- Explain the file-based user registration and login system
- Discuss how it integrates with the game menu

#### Slide 13: Menu System and Game Flow
```cpp
char initialMenu() {
    // Implementation details
}

char gameMenu() {
    // Implementation details
}

void command() {
    // Main game loop and menu handling
}
```
- Explain the menu structure and how it controls game flow
- Discuss the integration of authentication and game modes

#### Slide 14: Main Function and Program Entry
```cpp
int main() {
    contributions();
    command();
    return 0;
}
```
- Explain how the program starts and the initial setup
- Discuss the `contributions` function for team information display

#### Slide 15: Challenges, Learnings, and Future Improvements
- Discuss challenges in implementing the minimax algorithm
- Highlight learnings from combining OOP concepts with game theory
- Suggest potential improvements:
  - Implementing alpha-beta pruning for efficiency
  - Expanding to larger board sizes or 3D Tic Tac Toe
  - Adding a graphical user interface
- Conclude with the successful implementation of a classic game with AI capabilities
