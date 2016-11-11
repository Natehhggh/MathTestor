/* -----------------------------------------------------------------------------

FILE:              MathTestor.CPP

DESCRIPTION:		Tests Math skills by giving random problems to solve

COMPILER:          Visual Studio 2013

NOTES:             Final Version

MODIFICATION HISTORY:

Author                  Date               Version
---------------         ----------         --------------
Nathan Blau				2016-10-18				1
Nathan Blau				2016-10-19				2
Nathan Blau				2016-10-20				3
Nathan Blau				2016-10-24				4
Nathan Blau				2016-11-8				5
Nathan Blau				2016-11-9				6
Nathan Blau				2016-11-9				7
Nathan Blau				2016-11-10				8
Nathan Blau				2016-11-10				9
----------------------------------------------------------------------------- */
#include <iostream>
#include <stdio.h>
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <string>
#include <list>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>

using namespace std;

void drawMenu(vector <char>, bool);
void arithmatic(int, char, bool, ofstream&);
void displayAnswers(vector <char>, vector <string>, ofstream&);
void displayEquation(char, int, int, ofstream &);
int getCorrectAnswer();
string getEquation(int, char, int& , int&);
int getRandomNumber(int);
char getChoice(vector <char>);
bool verifyChoice(vector <char>, char);
string getBool(bool);
void swapInt(int&, int&);
bool checkDuplicateAnswers(string, vector <string>);
string getWrongAnswer(int, char, vector <string>, bool);
void output(ofstream&, string);

/* -----------------------------------------------------------------------------
FUNCTION:          main()
DESCRIPTION:       main function, calls other functions based on user input
RETURNS:           int
NOTES:
----------------------------------------------------------------------------- */
int main(){
	time_t currentTime = time(0);
	struct tm * now = localtime(&currentTime);
	string name;
	int difficulty;
	bool allowNegatives = false;
	cout << "Please Enter your Name: ";
	cin >> name;
	replace(name.begin(), name.end(), ' ', '_');
	cout << "Please Choose a difficulty Level between 1 - 5 : ";
	bool failed = false;
	do
	{
		failed = false;
		difficulty = 0;
		cin >> difficulty;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(80, '\n');
			failed = true;
		}
		if (difficulty > 5 || difficulty < 1)
		{
			failed = true;
		}
	} while (failed);
	ofstream file(name + ".txt");
	file << now->tm_mon + 1 << '-';
	file << now->tm_mday << '-';
	file << now->tm_year + 1900 << ' ';
	file << now->tm_hour << ':';
	file << now->tm_min << ':';
	file << now->tm_sec << endl;
	
	file << "Seed :" << currentTime << endl;
	file << "Difficulty : " << difficulty << endl << endl << endl;
	srand(currentTime);

	vector <char> mainMenuChoices = { 'a', 'b', 'c', 'd', 'e', 'q' };
	bool running = true;
	do
	{
		drawMenu(mainMenuChoices, allowNegatives);
		
		switch (getChoice(mainMenuChoices))
		{
		case 'a':
			arithmatic(difficulty, 'a', allowNegatives, file);
			break;
		case 'b':
			arithmatic(difficulty, 'b', allowNegatives, file);
			break;
		case 'c':
			arithmatic(difficulty, 'c', allowNegatives, file);
			break;
		case 'd':
			arithmatic(difficulty, 'd', allowNegatives, file);
			break;
		case 'e':
			allowNegatives = !allowNegatives;
			break;
		case 'q':
			running = false;
			break;

		default:
			break;
		}
	} while (running);
	return 0;
}


/* -----------------------------------------------------------------------------
FUNCTION:          output()
DESCRIPTION:       outputs string input to screen and output file
RETURNS:           void
NOTES:
----------------------------------------------------------------------------- */
void output(ofstream &file, string s)
{
	cout << s << endl;
	file << s << endl;
}

/* -----------------------------------------------------------------------------
FUNCTION:          getBool()
DESCRIPTION:       outputs true or false based on bool input
RETURNS:           string
NOTES:
----------------------------------------------------------------------------- */
string getBool(bool b)
{
	if (b)
	{
		return "True";
	}
	else
	{
		return "False";
	}
}


/* -----------------------------------------------------------------------------
FUNCTION:          drawMenu()
DESCRIPTION:       draws main menu to screen
RETURNS:           void
NOTES:
----------------------------------------------------------------------------- */
void drawMenu(vector <char> choices, bool allowNegatives)
{
	system("cls");
	cout << choices[0] << ": Addition"<< endl;
	cout << choices[1] << ": Subtraction" << endl;
	cout << choices[2] << ": Multiplication" << endl;
	cout << choices[3] << ": Division" << endl;
	cout << choices[4] << ": Allow Negative Results : " << getBool(allowNegatives) << endl;
	cout << choices[5] << ": Exit Program" << endl;
	cout << "Enter your choice [ ";
	for each (char choice in choices)
	{
		cout << choice << " ";
	}
		cout << "]" << endl;
}


/* -----------------------------------------------------------------------------
FUNCTION:          getChoice()
DESCRIPTION:       gets user input
RETURNS:           char
NOTES:
----------------------------------------------------------------------------- */
char getChoice(vector <char> list)
{
	bool failed = false;
	char choice;
	do
	{
		failed = false;
		choice = 0;
		cin >> choice;
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(80, '\n');
			failed = true;
		}
		choice = tolower(choice);
		if (!verifyChoice(list, choice))
		{
			failed = true;
		}

	} while (failed);
	
	return choice;
}



/* -----------------------------------------------------------------------------
FUNCTION:          getRandomNumber()
DESCRIPTION:       returns random number based on difficulty
RETURNS:           int
NOTES:
----------------------------------------------------------------------------- */
int getRandomNumber(int difficulty)
{
	return rand() % (int)(pow(10, difficulty) - (int)pow(10, difficulty - 1)) + (int)pow(10, difficulty - 1);
}


/* -----------------------------------------------------------------------------
FUNCTION:          verifyChoice()
DESCRIPTION:       checks if the choice exists in the list
RETURNS:           bool
NOTES:
----------------------------------------------------------------------------- */
bool verifyChoice(vector <char> list, char choice)
{
	bool found = false;
	
	// apparently you cannot get sizeof an array after passing it into a function
	for each (char option in list)
	{
		if (choice == option)
		{
			found = true;
			break;
		}
	}

	return found;
}


/* -----------------------------------------------------------------------------
FUNCTION:          getEquation()
DESCRIPTION:       gets a random math problem for both correct and incorrect answers
RETURNS:           string
NOTES:
----------------------------------------------------------------------------- */
string getEquation(int difficulty, char type, int& x, int & y , bool allowNegatives)
{


	x = getRandomNumber(difficulty);
	y = getRandomNumber(difficulty);
	string z;
	switch (type)
	{
		//addition
	case 'a':
		z =  to_string(x + y);
				
		break;
		//subtraction
	case 'b':
		if (!allowNegatives && y > x)
		{
			swapInt(x, y);
		}
		z = to_string(x - y);
		
		break;
		//mutliplication
	case 'c':
		z = to_string(x * y);
		
		break;
		//division
	case 'd':
		if (y == 0)
		{
			z = "undefined";
		}
		else
		{
			//cout << "x: " << x << endl;
			//cout << "y: " << y << endl;
			if (x != 0 && y > x)
			{
				swapInt(x , y);
			}
			while (x%y != 0)
			{
				y--;
			}
			z = to_string(x / y);
		}
		break;

	default:
		break;
	}
	return z;

}


/* -----------------------------------------------------------------------------
FUNCTION:          displayEquation()
DESCRIPTION:       writes the math problem to be solved on the screen
RETURNS:           void
NOTES:
----------------------------------------------------------------------------- */
void displayEquation(char type, int x, int y, ofstream &file)
{
	stringstream ss;
	switch (type)
	{
	case 'a':
		type = '+';
		break;

	case 'b':
		type = '-';
		break;

	case 'c':
		type = '*';
		break;

	case 'd':
		type = '/';
		break;		
	default:
		type = '+';
		break;
	}
	ss << "    " << x;
	output(file, ss.str());
	ss.str("");
	ss << "  " << type << ' ' << y << endl << endl;
	output(file, ss.str());
	ss.str("");
}


/* -----------------------------------------------------------------------------
FUNCTION:          displayAnswers()
DESCRIPTION:       displays the 5 answers for math problems
RETURNS:           void
NOTES:
----------------------------------------------------------------------------- */
void displayAnswers( vector <char> choices, vector <string> listOfAnswers, ofstream &file )
{
	//cout << listOfAnswers.size() << endl << choices.size() << endl;
	stringstream ss;
	for (unsigned int i = 0; i < (choices.size() - 1); i++)
	{
		
		ss << choices[i] << ": " << listOfAnswers[i];
		output(file, ss.str());
		ss.str("");
	}
	ss << choices[choices.size() - 1] <<  ": None of the Above" ;
	output(file, ss.str());
	ss.str("");

}

/* -----------------------------------------------------------------------------
FUNCTION:          getCorrectAnswer()
DESCRIPTION:       returns random number between 0 and 4
RETURNS:           int
NOTES:
----------------------------------------------------------------------------- */
int getCorrectAnswer()
{
	return rand() % 5;
}

/* -----------------------------------------------------------------------------
FUNCTION:          arithmatic()
DESCRIPTION:       Gets random problems for user to solve
RETURNS:           void
NOTES:
----------------------------------------------------------------------------- */
void arithmatic(int difficulty, char type, bool allowNegatives, ofstream &file)
{
	
	char choice;
	string str;
	string answer, wrongAnswer;
	int x = getRandomNumber(difficulty), y = getRandomNumber(difficulty);
	vector <string> listOfAnswers;
	vector <char> choices = { 'a', 'b', 'c', 'd', 'e' };
	int correctAnswer = getCorrectAnswer();
	answer = getEquation(difficulty, type, x, y, allowNegatives);


	time_t currentTime = time(0);
	struct tm * now = localtime(&currentTime);
	file << now->tm_mon + 1 << '-';
	file << now->tm_mday << '-';
	file << now->tm_year + 1900 << ' ';
	file << now->tm_hour << ':';
	file << now->tm_min << ':';
	file << now->tm_sec << endl;

	for (int i = 0; i < 4; i++)
	{
		if (i == correctAnswer)
		{
			while (checkDuplicateAnswers(answer, listOfAnswers))
			{
				answer = getEquation(difficulty, type, x, y, allowNegatives);
			}
			listOfAnswers.push_back(answer);
		}
		else
		{
			wrongAnswer = getWrongAnswer(difficulty, type, listOfAnswers, allowNegatives);
			listOfAnswers.push_back(wrongAnswer);
		}	
		//cout << answer << endl;
		
	}

	if (correctAnswer == 4)
	{
		while (checkDuplicateAnswers(answer, listOfAnswers))
		{
			answer = getEquation(difficulty, type, x, y, allowNegatives);
		}
	}
	
	for (int i = 0; i < 3; i++)
	{
		system("cls");
		displayEquation(type, x, y, file);
		displayAnswers(choices, listOfAnswers, file);
		cout << "Please enter your choice: ";
		choice = getChoice(choices);
		str = choice;
		output(file, str);
		if (choice == choices[correctAnswer])
		{
			output(file, "Correct Guess");
			file << "Accuracy: " << (float)100 / (i + 1) << '%' << endl; 
			system("pause");
			break;
		}
		else
		{
			output(file,"Incorrect Guess");
		}
		system("pause");
		if (i == 2)
		{
			file << "Accuracy: 0%" << endl;
		}
	}
	listOfAnswers.clear();
}

/* -----------------------------------------------------------------------------
FUNCTION:          swapInt()
DESCRIPTION:       swaps two int's value
RETURNS:           void
NOTES:
----------------------------------------------------------------------------- */
void swapInt(int& x, int& y)
{
	int z;
	z = y;
	y = x;
	x = z;
}


/* -----------------------------------------------------------------------------
FUNCTION:          getWrongAnswer()
DESCRIPTION:       gets wrong answer for questions 
RETURNS:           string
NOTES:
----------------------------------------------------------------------------- */
string getWrongAnswer(int difficulty, char type, vector <string> listOfAnswers, bool allowNegatives)
{
	int x, y;
	string value;
	do{
		value = getEquation(difficulty, type, x, y, allowNegatives);
	} while (checkDuplicateAnswers(value, listOfAnswers));
	return value;
}


/* -----------------------------------------------------------------------------
FUNCTION:          checkDuplicateAnswers()
DESCRIPTION:       Checks input and returns true if it matches anything in list
RETURNS:           bool
NOTES:
----------------------------------------------------------------------------- */
bool checkDuplicateAnswers(string s, vector <string> listOfAnswers)
{
	bool b = false;
	for each (string t in listOfAnswers)
	{
		//cout << " X : " << x << " , y : " << y << " , S : " << s << ", T : " << t <<endl;
		if (!s.compare(t))
		{
			//cout << "Equal" << endl;
			b = true;
			break;
		}
	}
	return b;
}
