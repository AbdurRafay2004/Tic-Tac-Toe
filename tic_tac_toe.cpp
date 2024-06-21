#include <iostream>
#include <string>
#include <ctime>
#include <windows.h>
using namespace std;

// Function to change text color
void textcolor(int color) {
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, color);
    // RED = 4, GREEN = 2, BLUE = 1, YELLOW = 6, WHITE = 15
}

string PlayerInput(char tbl[][3], string *, string *);
class player
{
private:
    string name = "Computer"; // player name computer by default for AI player
    int totalmoves;           // moves counter

public:
    player(); // constructor
};
player::player()
{
    totalmoves = 0;
}

class handlePlayerMove : public player
{
private:
public:
};

class handleAiMove : public player
{
};

void drawBoard()
{
    
}
void checkWin()
{
}
void checkTie()
{
}
void playGame()
{
}
char menu(){
    char choice;
    
    
	textcolor(1);   cout << "\t\t\t[1] "; textcolor(6);  cout << "Player vs Player" << endl;
	textcolor(1);   cout << "\t\t\t[2] "; textcolor(6);  cout << "Player vs Computer" << endl;
	textcolor(1);   cout << "\t\t\t[0] "; textcolor(6);  cout << "Quit Game" << endl;
    textcolor(15);
	cin >> choice;
	return choice;
}
void projectMembers()
{
    textcolor(4);
    cout << "\t\t\t\t      ***  TIC - TAC - TOE  ***\n\n";
	cout << "\t\t\t\tWELCOME TO TIC-TAC-TOE BY TEAM ROCKET\n" << endl;
    textcolor(3); //change color to green
    std::cout
    << "\t\t\t                     :: Abdur Rafay      (1013)\n"
    << "\t\t\tContributions        :: Al Abedin Wasee  (1013)\n"
    << "\t\t\t                     :: Younus Ali Molla (1013)\n"
    << "\t\t\t                     \n";
    
    textcolor(15); //reset color

    //shows menu
    char command;
	do {
		command = menu();
		switch (command) {
		case '1':
        //player vs player
			break;
		case '2':
		//player vs AI
			break;
		}
		system("pause");
	} while (command != '0');
	exit(0);
}
void command() {
	
}

int main()
{
    projectMembers();//shows intro informations
    char tbl[3][3]{
       {'-', '-', '-'},
       {'-', '-', '-'},
       {'-', '-', '-'}
    };

    string Plyr1;
    string Plyr2;
    cout << "Enter player 1 name : ";
    getline(cin, Plyr1);
    cout << "Enter player 2 name : ";
    getline(cin, Plyr2);




    return 0;
}