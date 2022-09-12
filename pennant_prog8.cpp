/*
Name: St George Pennant


Description: number guessing game with a random number generator
dynamic array to store game results.

*************************************************************/
#include <iostream> //standard library for i/o
#include <string> // always include this when you use the string class
#include <ctime> //random number generator
#include <fstream> //for file output
#include <cctype> //for toupper and tolower
using namespace std;

/*********************************************************
//Following is the declaration of a round of the guessing game
**********************************************************/
class guessGame
{
public:
	int upper_range = 0;
	int max_guesses = 0;
	int current_guess = 0;
	int random_number = 0;
	bool guessTooLow = 0; //NOT REQUIRED
	bool guessTooHigh = 0; //NOT REQUIRED
	string name = "";
	bool wonOrLost = 0;
	int level = 0;
};


//Declaration/ Prototypes for your functions will go here
//BE SURE TO ADD COMMENTS TO THE FUNCTION PROTOTYPES AND THE FUNCTION DEFINITIONS

void TestAndDouble(guessGame*& gameList, int& gameCount, int& size);
//Precondition: State what is true before the function is called.
//Postcondition: State what is true after the function has executed.
//Description:  Describe what the function does. 

void DoubleSize(guessGame*& gameList, int gameCount, int& size);
//Precondition: State what is true before the function is called.
//Postcondition: State what is true after the function has executed.
//Description:  Describe what the function does. 

void UpdateNames(guessGame gameList[], int gameCount);
//Precondition: State what is true before the function is called.
//Postcondition: State what is true after the function has executed.
//Description:  Describe what the function does. 

void PrintGameResults(guessGame gameList[], int gameCount);
//Precondition: State what is true before the function is called.
//Postcondition: State what is true after the function has executed.
//Description:  Describe what the function does.

void SetUpperRange(guessGame&, int);
//Precondition: State what is true before the function is called.
//Postcondition: State what is true after the function has executed.
//Description:  Describe what the function does. 

int  GetUpperRange(int);
//Precondition: State what is true before the function is called.
//Postcondition: State what is true after the function has executed.
//Description:  Describe what the function does.

void SetNumGuesses(guessGame&, int);
//Precondition: State what is true before the function is called.
//Postcondition: State what is true after the function has executed.
//Description:  Describe what the function does.

int  GetNumGuesses(int);
//Precondition: State what is true before the function is called.
//Postcondition: State what is true after the function has executed.
//Description:  Describe what the function does.

void PlayOneRound(guessGame&);
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
	string yesOrNo = "y";

	guessGame* gameList;//declare dynamic array
	
	int gameCount = 0;//count is 0 no games have been played yet
	
	int size = 1; //size of the array starts at 1
	
	gameList = new guessGame[size]; //array of size one

	cout << "Do you want to play the guessing game? (y or n): ";
	cin >> yesOrNo;

	while (yesOrNo == "y" || yesOrNo == "Y")
	{
		//The user wants to play, make sure there is enough room in the array
		//by calling TestAndDouble
		TestAndDouble(gameList, gameCount, size);

		//ask for the name here, it may be a different player
		cout << "Enter your first name: ";
		//ask and get the name of the user
		cin >> gameList[gameCount].name;

		//call Play one round function
		PlayOneRound(gameList[gameCount]);

		//Play again (Y or n)?
		cout << "Do you want to play another round? (y or n): ";
		cin >> yesOrNo;

		//add one to the gameCount
		gameCount++;

	}
	//Print Results function
	PrintGameResults(gameList, gameCount);
	
	//Update Names function
	UpdateNames(gameList, gameCount);

	//Print Results function
	PrintGameResults(gameList, gameCount);

	return  0;
}

//if the gameList is full it calls double to increase capacity
void TestAndDouble(guessGame*& gameList, int& gameCount, int& size)
{
	//check if the gameCount equals the size 
	if (gameCount == size)
	{
		//call double size function
		DoubleSize(gameList, gameCount, size);
	}
	//test the size and the count
	cout << "\n\n-------------count is " << gameCount;
	cout << "\n-------------size is " << size << endl << endl;
}

//doubles the size capacity of gameList
void DoubleSize(guessGame*& gameList, int count, int& size)
{
	//see the dynamic_array_example8.cpp file
	size *= 2;
	
	guessGame* t = new guessGame[size];

	for (int i = 0; i < count; i++)
	{
		t[i] = gameList[i];
	}

	delete[] gameList;

	gameList = t;
}

//changes all the names in the gameList to have
//an uppercase first letter and lowercase remaining letters
//example: tAMi would become Tami
void UpdateNames(guessGame gameList[], int gameCount)
{
	//loop through the gameList array
	for(int i = 0; i < gameCount; i++)
	{
		//get the length of each name
		int len = gameList[i].name.length();

		//sets the first letter to uppercase
		gameList[i].name[0] = toupper(gameList[i].name[0]);

		//loop through letters 1 through len-1
		for(int j = 1; j < len; j++)
		{
			//change letters to lowercase
			gameList[i].name[j] = tolower(gameList[i].name[j]);
		}
	}

}

//prints the information in the array on the screen and into an output file
//the name, level, and whether or not they won or lost that round
void PrintGameResults(guessGame gameList[], int gameCount)
{
	ofstream out;
	char filename[16];
	//user should enter filename with .txt extension
	//ask and get the file name
	cout << "\nPlease enter the filename: ";
	cin >> filename;
	//add to the file if the user enters the same file name
	out.open(filename, ios::app); //use ios::app to add to the file

	cout << "\n***********************************\n";
	cout << "Name\t" << "Level\t" << "Won or Lost\n";
	//use a loop to output the results onto the screen
	for (int i = 0; i < gameCount; i++)
	{
		cout << gameList[i].name << "\t";
		cout << gameList[i].level << "\t";
		cout << gameList[i].wonOrLost << endl;
	}

	out << "\n***********************************\n";
	out << "Name\t" << "Level\t" << "Won or Lost\n";
	
	//use a loop to output the results into the file
	for (int i = 0; i < gameCount; i++)
	{
		out << gameList[i].name << "\t";
		out << gameList[i].level << "\t";
		out << gameList[i].wonOrLost << endl;
	}

	out.close();
}

void PlayOneRound(guessGame& currentGame)
//Description:  Play one round of the guess game
{
	int upper;
	int numGuesses;
	currentGame.wonOrLost = 0; //REQUIRED, keeps track if the user won or lost the round
	currentGame.guessTooLow = 0; //OPTIONAL FEATURE
	currentGame.guessTooHigh = 0; //OPTIONAL FEATURE

	//Display the levels and ask the user to pick the level
	cout << "What level?" << endl;
	cout << "(1) Beginning - 4 guessess, numbers 1 through 10" << endl;
	cout << "(2) Intermediate - 5 guessess, numbers 1 through 50" << endl;
	cout << "(3) Advanced - 6 guessess, numbers 1 through 100:" << endl;
	//Get the level, it is now a member function 
	cin >> currentGame.level;

	//get and set the currentGame.max_guesses and currentGame.upper_range
	upper = GetUpperRange(currentGame.level);
	SetUpperRange(currentGame, upper);

	numGuesses = GetNumGuesses(currentGame.level);
	SetNumGuesses(currentGame, numGuesses);

	//generate the solution(random_number)
	GenerateRandomNumber(currentGame);

	//counting loop for the maximum number of guesses
	for (int i = 0; i < currentGame.max_guesses; i++)
	{
		//let the user know the guess number
		cout << "\nThis is guess number (" << i + 1 << ")";
		
		//Get the Next Guess
		GetNextGuess(currentGame);

		currentGame.guessTooLow = 0; //OPTIONAL FEATURE
		currentGame.guessTooHigh = 0;//OPTIONAL FEATURE
		
		if (InterpretGuess(currentGame))
		{
			cout << "\nYou won that round, " << currentGame.name << "!\n";
			
			//stop the loop WITHOUT a break statement
			i = numGuesses;
			
			currentGame.wonOrLost = true; //the user won this round
		}
	}
	//Let the user know if they did not win
	if (currentGame.wonOrLost != true)
	{
		cout << "\nYou did not win that round, " << currentGame.name << "!" << endl;
	}
	
	cout << "\nTHE SOLUTION WAS " << currentGame.random_number << endl;
}

void SetUpperRange(guessGame& currentGame, int upper)
//Description:  sets the upper range for the random number generator. 
{
	//sets the upper range value in the current game
	currentGame.upper_range = upper;
}

int  GetUpperRange(int level)
//Description:  Gets the upper range.
{
	//returns the upper range value based on the level
	if (level == 1) return 10;
	//add the other conditions
	else if (level == 2) return 50;
	else if (level == 3) return 100;
	else return 0;
}

void SetNumGuesses(guessGame& currentGame, int numGuesses)
//Description:  Sets the number of guesses for the current round.
{
	//set maximum number of guesses
	currentGame.max_guesses = numGuesses;
}

int  GetNumGuesses(int level)
//Description:  Gets the number of guesses for the current round
{
	//returns the number of guesses based on the level
	if (level == 1) return 4;
	//add the other conditions
	else if (level == 2) return 5;
	else if (level == 3) return 6;
	else return 0;
}

void GetNextGuess(guessGame& currentGame)
//Description: Get the next guess from the user
{
	////OPTIONAL FEATURES
	if (currentGame.guessTooLow)
	{
		cout << endl << "Enter a guess above " << currentGame.current_guess << " : ";
		cin >> currentGame.current_guess;
	}
	else if (currentGame.guessTooHigh)
	{
		cout << endl << "Enter a guess below " << currentGame.current_guess << " : ";
		cin >> currentGame.current_guess;
	}
	else
	{
		cout << endl << "Enter a guess between 1 and " << currentGame.upper_range << " : ";
		cin >> currentGame.current_guess;
	}
	//cout << "\nEnter a guess: ";
	//cin >> currentGame.current_guess;
}

bool InterpretGuess(guessGame& currentGame)
//Description:  Describe what the function does.
{
	if (currentGame.current_guess == currentGame.random_number)
	{
		return true;
	}
		
	else if (currentGame.current_guess > currentGame.random_number)
	{
		cout << "\nYour guess was too high.";
		cout << "\n-----------------------";
		currentGame.guessTooHigh = true; ////OPTIONAL FEATURE
		return false;
	}
	//add the other condition
	else
	{
		cout << "\nYour guess was too low.";
		cout << "\n-----------------------";
		currentGame.guessTooLow = true; //guess was too low
		return false;//guess was not correct
	}
}

void GenerateRandomNumber(guessGame& currentGame)
//Precondition: State what is true before the function is called.
//Postcondition: State what is true after the function has executed.
//Description:  Describe what the function does.
{
	srand((unsigned)time(0));
	currentGame.random_number = 1 + rand() % currentGame.upper_range;
	//cout << "\nSolution is " << currentGame.random_number << endl;
}

