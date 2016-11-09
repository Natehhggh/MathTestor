











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
void displayAnswers(vector <char>, vector <string> &);
void displayEquation(char, int, int, ofstream &);
char getCorrectAnswer();
string getEquation(int, char, int& , int&);
int getRandomNumber(int);
char getChoice(vector <char>);
bool verifyChoice(vector <char>, char);
string getDifficulty(int);
string getBool(bool);
int changeDifficulty(int);
void swapInt(int&, int&);
bool checkDuplicateAnswers(string, vector <string>);
string getWrongAnswer(int, char, vector <string>&, bool);
void output(ofstream&, string);


int main(){
	time_t currentTime = time(NULL);
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
	ofstream file(name);
	
	file << "PUT IN TIMESTAMP" << endl;
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

void output(ofstream &file, string s)
{
	cout << s << endl;
	file << s << endl;
}

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
		break;
	}
	ss << "    " << x;
	output(file, ss.str());
	ss.str("");
	ss << "  " << type << ' ' << y << endl << endl;
	output(file, ss.str());
	ss.str("");
}



void displayAnswers( vector <char> listOfAnswers, vector <string> &possibleAnswers, ofstream &file )
{
	string wrongAnswer;
	stringstream ss;
	for (int i = 0; i < (listOfAnswers.size() - 1); i++)
	{
			ss << listOfAnswers[i] << ": " << possibleAnswers[i];
			output(file, ss.str());
			ss.str("");
	}
	ss << listOfAnswers[listOfAnswers.size() - 1] <<  ": None of the Above" ;
	output(file, ss.str());
	ss.str("");

}

char getCorrectAnswer()
{
	return rand() % 5;
}

void arithmatic(int difficulty, char type, bool allowNegatives, ofstream &file)
{
	char choice;
	string str;
	string answer;
	int x = 0, y = 0;
	vector <string> possibleAnswers;
	vector <char> listOfAnswers = { 'a', 'b', 'c', 'd', 'e' };
	int correctAnswer = getCorrectAnswer();
	
	
	for (int i = 0; i < 4; i++)
	{
		if (i == correctAnswer)
		{

			do{
				answer = getEquation(difficulty, type, x, y, allowNegatives);
			} while (checkDuplicateAnswers(answer, possibleAnswers));
		}
		else
		{
			answer = getWrongAnswer(difficulty, type, possibleAnswers, allowNegatives);
		}	
		cout << answer << endl;
		possibleAnswers.push_back(answer);
	}
	
	for (int i = 0; i < 3; i++)
	{
		displayEquation(type, x, y, file);
		displayAnswers(listOfAnswers, possibleAnswers, file);
		cout << "Correct answer = " << correctAnswer << endl;
		choice = getChoice(listOfAnswers);
		str = choice;
		output(file, str);
		if (choice == listOfAnswers[correctAnswer])
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

	}
	file << "Accuracy: 0%" << endl;
	possibleAnswers.clear();
	
}

void swapInt(int& x, int& y)
{
	int z;
	z = y;
	y = x;
	x = z;
}

string getWrongAnswer(int difficulty, char type, vector <string> &possibleAnswers, bool allowNegatives)
{
	int x, y;
	string value;
	do{
		value = getEquation(difficulty, type, x, y, allowNegatives);
	} while (checkDuplicateAnswers(value, possibleAnswers));
	possibleAnswers.push_back(value);
	return value;
}

bool checkDuplicateAnswers(string s, vector <string> possibleAnswers)
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
