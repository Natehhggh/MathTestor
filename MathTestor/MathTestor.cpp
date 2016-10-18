#include <iostream>
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

void drawMenu(int);
void optionsMenu(char[]);
void additionMenu(int, char[]);
void subtractionMenu(int, char[]);
void multiplicationMenu(int, char[]);
void divisionMenu(int, char[]);

void addition(int);
void subtraction(int);
void multiplication(int);
void division(int);

int getRandomNumber(int);
char getChoice(char[]);
bool verifyChoice(char[], char);

int changeDifficulty(int);

enum Menus
{
	MainMenu,
	OptionsMenu,
	AdditionMenu,
	SubtractionMenu,
	MultiplicationMenu,
	DivisionMenu
};

enum Difficulty
{
	Beginner,
	Easy,
	Medium,
	Hard
};

const int MAINMENUCHOICES = 6;
const int OPTIONSMENUCHOICES = 5;
const int  ARITMATICMENUCHOICES= 3;

char mainMenuChoices[MAINMENUCHOICES] = { 'a', 'b', 'c', 'd', 'o', 'q'  };
char optionsMenuChoices[OPTIONSMENUCHOICES] = { 'a', 's', 'm', 'd', 'r' };
char arithmaticMenuChoices[ARITMATICMENUCHOICES] = { 'a', 'd', 'r' };

int additionDifficulty = Beginner;
int subtractionDifficulty = Beginner;
int multiplicationDifficulty = Beginner;
int divisionDifficulty = Beginner;

int main(){
	srand(time(NULL));
	bool running = true;
	do
	{
		drawMenu(MainMenu);
		
		switch (getChoice(mainMenuChoices))
		{
		case 'a':
			additionMenu(additionDifficulty, arithmaticMenuChoices);
			break;
		case 'b':
			subtractionMenu(subtractionDifficulty, arithmaticMenuChoices);
			break;
		case 'c':
			multiplicationMenu(multiplicationDifficulty, arithmaticMenuChoices);
			break;
		case 'd':
			divisionMenu(divisionDifficulty, arithmaticMenuChoices);
			break;
		case 'o':
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

int changeDifficulty(int difficulty)
{
	switch (difficulty)
	{
	case Beginner:
	case Easy:
	case Medium:
		difficulty++;
		break;

	case Hard:
		difficulty = Beginner;
		break;
		
	default:
		break;

		return difficulty;
	}

}

void drawMenu(int menu)
{

	system("cls");
	switch (menu)
	{
	case MainMenu:
		break;

	case OptionsMenu:
		break;

	default:
		break;
	}

}

char getChoice(char list[])
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

		if (!verifyChoice(list, choice))
		{
			failed = true;
		}

	} while (failed);
	
	return choice;
}

int getRandomNumber(int difficulty)
{
	int number, rangeMin, rangeMax;

	switch (difficulty)
	{

	case Beginner:
		rangeMin = 0;
		rangeMax = 10;
		break;

	case Easy:
		rangeMin = 10;
		rangeMax = 100;

		break;

	case Medium:
		rangeMin = 100;
		rangeMax = 1000;
		break;

	case Hard:
		rangeMin = 1000;
		rangeMax = 10000;
		break;

	default:
		break;
	}


	number = rand() % rangeMax + rangeMin;

	return number;
}

bool verifyChoice(char list[], char choice)
{
	bool found = false;
	for (int i = 0; i < sizeof(list); i++)
	{
		if (choice == list[i])
		{
			found = true;
			break;
		}
	}
	return found;
}

void optionsMenu()
{
	bool running = true;
	do
	{

		drawMenu(OptionsMenu);
		switch (getChoice(optionsMenuChoices))
		{
		case 'a':
			additionDifficulty = changeDifficulty(additionDifficulty); 
			break;

		case 's':
			subtractionDifficulty = changeDifficulty(subtractionDifficulty);
			break;

		case 'm':
			multiplicationDifficulty = changeDifficulty(subtractionDifficulty);
			break;

		case 'd':
			divisionDifficulty = changeDifficulty(divisionDifficulty);
			break;

		case 'r':
			running = false;
			break;

		default:
			break;
		}


	} while (running);
}

void additionMenu(int, char choices[])
{
	bool running;
	do
	{
		drawMenu(AdditionMenu);
		switch (getChoice(choices))
		{
		case 'a':
			addition(additionDifficulty);
			break;

		case 'd':
			additionDifficulty = changeDifficulty(additionDifficulty);
			break;

		case 'r':
			running = false;
			break;

		default:
			break;
		}
	} while (running);
}

void subtractionMenu(int, char choices[])
{
	bool running;
	do
	{
		drawMenu(SubtractionMenu);
		switch (getChoice(choices))
		{
		case 'a':
			subtraction(subtractionDifficulty);
			break;

		case 'd':
			subtractionDifficulty = changeDifficulty(subtractionDifficulty);
			break;

		case 'r':
			running = false;
			break;

		default:
			break;
		}
	} while (running);
}

void multiplicationMenu(int, char choices[])
{
	bool running;
	do
	{
		drawMenu(MultiplicationMenu);
		switch (getChoice(choices))
		{
		case 'a':
			multiplication(multiplicationDifficulty);
			break;

		case 'd':
			multiplicationDifficulty = changeDifficulty(multiplicationDifficulty);
			break;

		case 'r':
			running = false;
			break;

		default:
			break;
		}
	} while (running);
}

void divisionMenu(int, char choices[])
{
	bool running;
	do
	{
		drawMenu(DivisionMenu);
		switch (getChoice(choices))
		{
		case 'a':
			division(divisionDifficulty);
			break;

		case 'd':
			divisionDifficulty = changeDifficulty(divisionDifficulty);
			break;

		case 'r':
			running = false;
			break;

		default:
			break;
		}
	} while (running);
}

void addition(int difficulty)
{
	
}

void subtraction(int difficulty)
{

}

void multiplication(int difficulty)
{

}

void division(int difficulty)
{

}
