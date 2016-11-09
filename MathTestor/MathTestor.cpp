#include <iostream>
#include <stdio.h>
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <string>
#include <list>
#include <vector>
#include <fstream>

using namespace std;

void drawMenu(vector <char>, bool);
void arithmatic(int, char, bool);
void displayAnswers(string, int, int, char, bool, vector <char>, list <string> &);
void displayEquation(char, int, int);
char getCorrectAnswer();
string getEquation(int, char, int& , int&);
int getRandomNumber(int);
char getChoice(vector <char>);
bool verifyChoice(vector <char>, char);
string getDifficulty(int);
string getBool(bool);
int changeDifficulty(int);
void swapInt(int&, int&);
bool checkDuplicateAnswers(string, list <string>);
string getWrongAnswer(int, char, list <string>&, bool);
void output(string);


int main(){
	ofstream outputFile;
	int difficulty = 5;
	
	bool allowNegatives = false;


	srand(time(NULL));
	vector <char> mainMenuChoices = { 'a', 'b', 'c', 'd', 'e', 'q' };
	bool running = true;
	do
	{
		drawMenu(mainMenuChoices, allowNegatives);
		
		switch (getChoice(mainMenuChoices))
		{
		case 'a':
			arithmatic(difficulty, 'a', allowNegatives);
			break;
		case 'b':
			arithmatic(difficulty, 'b', allowNegatives);
			break;
		case 'c':
			arithmatic(difficulty, 'c', allowNegatives);
			break;
		case 'd':
			arithmatic(difficulty, 'd', allowNegatives);
			break;
		case 'e':
			allowNegatives = !allowNegatives;
		case 'q':
			running = false;
			break;

		default:
			break;
		}
	} while (running);
	return 0;
}
/*
void output(ofstream output, string s)
{
	cout << s << endl;
	output.open();
	output << s;
	output.close();
}*/

int changeDifficulty(int difficulty)
{
	switch (difficulty)
	{
	case 1:
	case 2:
	case 3:
	case 4:
		difficulty++;
		break;

	case 5:
			difficulty = 1;
		break;
		
	default:
		difficulty = 1;
		break;
		
	}
	return difficulty;
}

string getDifficulty(int difficulty)
{
	string s;
	switch (difficulty)
	{
	case 1:
		s = "beginner";
		break;
	case 2:
		s = "easy";
		break;
	case 3:
		s = "medium";
		break;
	case 4:
		s = "hard";
		break;
	case 5:
		s = "challenging";
	default:
		break;
	}
	return s;
}

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

int getRandomNumber(int difficulty)
{
	return rand() % (int)(pow(10, difficulty) - (int)pow(10, difficulty - 1)) + (int)pow(10, difficulty - 1);
}

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

void displayEquation(char type, int x, int y)
{
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
		break;
	}

	cout << "    " << x << endl;
	cout << "  " << type << " " << y << endl << endl;
}



void displayAnswers(string answer, int correct, int difficulty, char type, bool allowNegatives, vector <char> listOfAnswers, list <string> &possibleAnswers )
{
	string wrongAnswer;
	for (int i = 0; i < (listOfAnswers.size() - 1); i++)
	{
		if (correct == i)
		{
			cout << listOfAnswers[i] << ": " << answer << endl;
		}
		else
		{
			wrongAnswer = getWrongAnswer(difficulty, type, possibleAnswers, allowNegatives);
			possibleAnswers.push_back(answer);
			cout << listOfAnswers[i] << ": " << wrongAnswer << endl;
		}
	}
	cout << listOfAnswers[listOfAnswers.size() - 1] << ": None of the Above" << endl;
	possibleAnswers.clear();

}

char getCorrectAnswer()
{
	return rand() % 5;
}

void arithmatic(int difficulty, char type, bool allowNegatives)
{
	char choice;
	int x, y;
	list <string> possibleAnswers;
	vector <char> listOfAnswers = { 'a', 'b', 'c', 'd', 'e' };
	int correctAnswer = getCorrectAnswer();
	string answer = getEquation(difficulty, type, x, y, allowNegatives);
	possibleAnswers.push_back(answer);
	
	for (int i = 0; i < 3; i++)
	{
		displayEquation(type, x, y);
		displayAnswers(answer, correctAnswer, difficulty, type, allowNegatives, listOfAnswers, possibleAnswers);
		cout << "Correct answer = " << correctAnswer << endl;
		choice = getChoice(listOfAnswers);
		
		if (choice == listOfAnswers[correctAnswer])
		{
			break;
		}
		else
		{
			cout << "Incorrect Guess" << endl;
		}
		system("pause");
	}

	
}

void swapInt(int& x, int& y)
{
	int z;
	z = y;
	y = x;
	x = z;
}

string getWrongAnswer(int difficulty, char type, list <string> &possibleAnswers, bool allowNegatives)
{
	int x, y;
	string value;
	do{
		value = getEquation(difficulty, type, x, y, allowNegatives);
	} while (checkDuplicateAnswers(value, possibleAnswers));
	possibleAnswers.push_back(value);
	return value;
}

bool checkDuplicateAnswers(string s, list <string> possibleAnswers)
{
	bool b = false;
	for each (string t in possibleAnswers)
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
