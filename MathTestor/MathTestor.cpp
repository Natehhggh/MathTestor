#include <iostream>
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

void drawMenu(int);
void optionsMenu();
void additionMenu(int, char[]);
void subtractionMenu(int, char[]);
void multiplicationMenu(int, char[]);
void divisionMenu(int, char[]);

void addition(int);
void subtraction(int);
void multiplication(int);
void division(int);

int getRandomNumber(int);
char getChoice(char[], int);
bool verifyChoice(char[], char, int);
string getDifficulty(int);
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
		
		switch (getChoice(mainMenuChoices, MAINMENUCHOICES))
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
			optionsMenu();
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
		difficulty = Beginner;
		break;
		
	}
	return difficulty;
}

string getDifficulty(int difficulty)
{
	string s;
	switch (difficulty)
	{
	case Beginner:
		s = "beginner";
		break;
	case Easy:
		s = "easy";
		break;
	case Medium:
		s = "medium";
		break;
	case Hard:
		s = "hard";
		break;
	default:
		break;
	}
	return s;
}

void drawMenu(int menu)
{

	system("cls");
	switch (menu)
	{
	case MainMenu:
		cout << mainMenuChoices[0] << ": Addition"<< endl;
		cout << mainMenuChoices[1] << ": Subtraction" << endl;
		cout << mainMenuChoices[2] << ": Multiplication" << endl;
		cout << mainMenuChoices[3] << ": Division" << endl;
		cout << mainMenuChoices[4] << ": Options Menu" << endl;
		cout << mainMenuChoices[5] << ": Exit Program" << endl;
		cout << "Enter your choice [ ";
		for (int i = 0; i < MAINMENUCHOICES; i++)
		{
			cout << mainMenuChoices[i] << " ";
		}
		cout << "]" << endl;
		break;

	case OptionsMenu:
		cout << optionsMenuChoices[0] << ": Addition Difficulty : " << getDifficulty(additionDifficulty) << endl;
		cout << optionsMenuChoices[1] << ": Subtraction Difficulty : " << getDifficulty(subtractionDifficulty) << endl;
		cout << optionsMenuChoices[2] << ": multiplication Difficulty : " << getDifficulty(multiplicationDifficulty) << endl;
		cout << optionsMenuChoices[3] << ": division Difficulty : " << getDifficulty(divisionDifficulty) << endl;
		cout << optionsMenuChoices[4] << ": return to main menu" << endl;
		cout << "Enter your choice [ ";
		for (int i = 0; i < OPTIONSMENUCHOICES; i++)
		{
			cout << optionsMenuChoices[i] << " ";
		}
		cout << "]" << endl;
		break;

	case AdditionMenu:
		cout << arithmaticMenuChoices[0] << ": Addition" << endl;
		cout << arithmaticMenuChoices[1] << ": Addition Difficulty : " << getDifficulty(additionDifficulty) << endl;
		cout << arithmaticMenuChoices[2] << ": Return to Main Menu" << endl;
		for (int i = 0; i < ARITMATICMENUCHOICES; i++)
		{
			cout << arithmaticMenuChoices[i] << " ";
		}
		cout << "]" << endl;
		break;

		break;

	case SubtractionMenu:
		cout << arithmaticMenuChoices[0] << ": Subtraction" << endl;
		cout << arithmaticMenuChoices[1] << ": Subtraction Difficulty : " << getDifficulty(subtractionDifficulty) << endl;
		cout << arithmaticMenuChoices[2] << ": Return to Main Menu" << endl;
		for (int i = 0; i < ARITMATICMENUCHOICES; i++)
		{
			cout << arithmaticMenuChoices[i] << " ";
		}
		cout << "]" << endl;
		break;

	case MultiplicationMenu:
		cout << arithmaticMenuChoices[0] << ": Multiplication" << endl;
		cout << arithmaticMenuChoices[1] << ": Multiplication Difficulty : " << getDifficulty(multiplicationDifficulty) << endl;
		cout << arithmaticMenuChoices[2] << ": Return to Main Menu" << endl;
		for (int i = 0; i < ARITMATICMENUCHOICES; i++)
		{
			cout << arithmaticMenuChoices[i] << " ";
		}
		cout << "]" << endl;
		break;

	case DivisionMenu:
		cout << arithmaticMenuChoices[0] << ": Division" << endl;
		cout << arithmaticMenuChoices[1] << ": Division Difficulty : " << getDifficulty(divisionDifficulty) << endl;
		cout << arithmaticMenuChoices[2] << ": Return to Main Menu" << endl;
		for (int i = 0; i < ARITMATICMENUCHOICES; i++)
		{
			cout << arithmaticMenuChoices[i] << " ";
		}
		cout << "]" << endl;
		break;

	default:
		break;
	}

}

char getChoice(char list[], int size)
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
		if (!verifyChoice(list, choice, size))
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

bool verifyChoice(char list[], char choice, int size)
{
	bool found = false;
	
	// apparently you cannot get sizeof an array after passing it into a function
	for (int i = 0; i < size; i++)
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
		switch (getChoice(optionsMenuChoices, OPTIONSMENUCHOICES))
		{
		case 'a':
			additionDifficulty = changeDifficulty(additionDifficulty); 
			break;

		case 's':
			subtractionDifficulty = changeDifficulty(subtractionDifficulty);
			break;

		case 'm':
			multiplicationDifficulty = changeDifficulty(multiplicationDifficulty);
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
	bool running = true;
	do
	{
		drawMenu(AdditionMenu);
		switch (getChoice(choices , ARITMATICMENUCHOICES))
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
	bool running = true;
	do
	{
		drawMenu(SubtractionMenu);
		switch (getChoice(choices, ARITMATICMENUCHOICES))
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
	bool running = true;
	do
	{
		drawMenu(MultiplicationMenu);
		switch (getChoice(choices, ARITMATICMENUCHOICES))
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
	bool running = true;
	do
	{
		drawMenu(DivisionMenu);
		switch (getChoice(choices, ARITMATICMENUCHOICES))
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
