/***********************************************************
Name: St George Pennant
Due Date: March 03, 2020
Course: C0P3014
Assignment: Program 5
Professor: Sorgente

Description: Number guessing game with a random number generator

*************************************************************/
#include <iostream> //standard library for i/o
#include <string> // always include this when you use the string class
#include <ctime> //random number generator
using namespace std;

/*********************************************************
//Following is the declaration of a round of the guessing game
**********************************************************/
class guessGame
{
public:
	int upper_range;
	int max_guesses;
	int current_guess;
	int random_number;
	bool guessTooLow; //NOT REQUIRED
	bool guessTooHigh; //NOT REQUIRED
};


//Declaration/ Prototypes for your functions will go here
//BE SURE TO ADD COMMENTS TO THE FUNCTION PROTOTYPES AND THE FUNCTION DEFINITIONS

void SetUpperRange(guessGame&, int);
//Precondition: State what is true before the function is called.
//Postcondition: State what is true after the function has executed.
//Description:  Describe what the function does. 

int GetUpperRange(int);
//Precondition: State what is true before the function is called.
//Postcondition: State what is true after the function has executed.
//Description:  Describe what the function does.

void SetNumGuesses(guessGame&, int);
//Precondition: State what is true before the function is called.
//Postcondition: State what is true after the function has executed.
//Description:  Describe what the function does.

int GetNumGuesses(int);
//Precondition: State what is true before the function is called.
//Postcondition: State what is true after the function has executed.
//Description:  Describe what the function does.

void PlayOneRound(const string&, guessGame&);
//Precondition: State what is true before the function is called.
//Postcondition: State what is true after the function has executed.
//Description:  Describe what the function does.

void GetNextGuess(guessGame&);
//Precondition: State what is true before the function is called.
//Postcondition: State what is true after the function has executed.
//Description:  Describe what the function does.

bool InterpretGuess(guessGame& currentGame);
//Precondition: State what is true before the function is called.
//Postcondition: State what is true after the function has executed.
//Description:  Describe what the function does.

void GenerateRandomNumber(guessGame&);
//Precondition: State what is true before the function is called.
//Postcondition: State what is true after the function has executed.
//Description:  Describe what the function does.

//HERE IS THE main function, a driver to test your program

int main()
{
	string name;
	string yesOrNo;

	//declare an object variable of type guessGame
	guessGame currentGame;

	//get the users name
	cout << "Enter your first name: " << name;
	cin >> name;

	//ask the user if they want to play
	cout << "Hi " << name << ", do you want to play the guessing game? (y or n): " << yesOrNo;
	cin >> yesOrNo;

	while (yesOrNo == "y" || yesOrNo == "Y")//test the while loop condition
	{
		//call the Play One Round function and pass the currentGame
		PlayOneRound(name, currentGame);

		//play again? 
		cout << "Do you want to play another round? (y or n): ";
		cin >> yesOrNo;
	}

	//say goodbye to the user
	cout << endl << "Thanks for playing, " << name << endl;

	return  0;
}

//Function Implementations will go here

void SetUpperRange(guessGame& currentGame, int upper)
//Description:  sets the upper range for the random number generator. 
{
	//sets the upper range value in the current game
	currentGame.upper_range = upper;
	
}

int GetUpperRange(int level)
//Description:  Gets the upper range.
{
	//returns the upper range value based on the level
	if (level == 1)return 10;
	else if (level == 2) return 50;
	else if (level == 3) return 100;
	else return -1;
}

void SetNumGuesses(guessGame& currentGame, int numGuesses)
//Description:  Sets the number of guesses for the current round.
{
	currentGame.max_guesses = numGuesses;
	//set the max guesses in the current game, see the SetUpperRange function
}

int GetNumGuesses(int level)
//Description:  Gets the number of guesses for the current round
{
	//returns the number of guesses based on the level
	if (level == 1) return 4;
	else if (level == 2) return 5;
	else if (level == 3) return 6;
	else return -1;
}

void PlayOneRound(const string& name, guessGame& currentGame)
//Description:  Play one round of the guess game
{
	int level;
	//int upper;
	int numGuesses;

	//reset above and below to 0 for the new round
	currentGame.guessTooLow = 0; //optional feature, not required
	currentGame.guessTooHigh = 0; //optional feature, not required

	//describe the levels to the user
	cout << "What level?" << endl;
	cout << "(1) Beginning - 4 guessess, numbers 1 through 10" << endl;
	cout << "(2) Intermediate - 5 guessess, numbers 1 through 50" << endl;
	cout << "(3) Advanced - 6 guessess, numbers 1 through 100:" << endl;
	cin >> level;

	//get and set the upper range
	SetUpperRange(currentGame, GetUpperRange(level));
	//get and set the number of guesses
	SetNumGuesses(currentGame, GetNumGuesses(level));

	//generate the random number to be guessed
	GenerateRandomNumber(currentGame);

	//loop header, counting loop for the number of guesses
	//currentGame.max_guesses
	numGuesses = 1;//number of guesses
	bool correct = false;
	do 
	{
		//tell the user what guess number they are on
		cout << endl << "This is guess number (" << numGuesses++ << ")" << endl;

		//get the next guess
		GetNextGuess(currentGame);

		//reset above and below to 0
		currentGame.guessTooLow = 0;
		currentGame.guessTooHigh = 0;

		//check if the guess is correct
		if (InterpretGuess(currentGame))
		{
			cout << "\nYou won that round, " << name << "!\n";
			//stop the loop, do not use a break statement to stop the loop
			correct = true;
		}	
	}
	while (numGuesses <= currentGame.max_guesses && !correct);
	//tell the user the solution after the round of the game is done
	cout << "\nTHE SOLUTION WAS " << currentGame.random_number << endl;
}

void GetNextGuess(guessGame& currentGame)
//Description:  get the next guess from the user
{
	//display the information to the user and get the next guess
	//optional feature, not required for this assignment
	if (currentGame.guessTooLow) //the guess was below the solution
	{
		cout << "\nEnter a guess above " << currentGame.current_guess << " : ";
	}
	//add more conditions 
	else if (currentGame.guessTooHigh) //the guess was above the solution
	{
		cout << "Enter a guess below " << currentGame.current_guess << " : ";
	}
	else //guess entry within the specified range
	{
		cout << "Enter a guess between 1 and " << currentGame.upper_range << " : ";
	   
	}
	//ask and get the next guess 
	cin >> currentGame.current_guess;	
}

bool InterpretGuess(guessGame& currentGame)
//Description:  Describe what the function does.
{
	//check if the guess is correct and return true 
	//else tell the user if it was too high and return false
	//too low and return true
	//example
	if (currentGame.current_guess < currentGame.random_number)
	{
		cout << "\nYour guess was too low.";
		cout << "\n-----------------------";
		currentGame.guessTooLow = true; //guess was too low
		//currentGame.guessTooHigh = false; //guess was too high
		return false;//guess was not correct
	}
	//add more conditions
	else if (currentGame.current_guess > currentGame.random_number)
	{
		cout << "\nYour guess was too high.";
		cout << "\n-----------------------";
		currentGame.guessTooHigh = true; //guess was too high
		//currentGame.guessTooLow = false; //guess was too low
		return false;//guess was not correct
	}
	else
	{
		return true;//guess was correct
	}
}

void GenerateRandomNumber(guessGame& currentGame)
//Precondition: State what is true before the function is called.
//Postcondition: State what is true after the function has executed.
//Description:  Describe what the function does.
{
	//generate a random number based on the 
	srand((unsigned)time(0));
	currentGame.random_number = 1 + rand() % currentGame.upper_range;
	//cout << "\nSolution is " << currentGame.random_number << endl;
}

