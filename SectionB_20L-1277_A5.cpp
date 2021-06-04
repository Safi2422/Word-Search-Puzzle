#include <iostream>
#include <fstream>

using namespace std;

//Struct check_present defines these properties
//Defining properties to check whether the word is already present
//Check array is present in create grid class which has these properties

enum base_data {not_present, present};			

struct check_present
{
	base_data is_present;
};

//Struct dimensions defines proerties of rows and cols 

struct dimensions		//For defining grid
{
	int rows = -1;
	int cols = -1;
};

//class createGrid will create a grid with user entered rows and cols
//Words input from file are stored in wordArr double pointer
//grid created is stored temporarily on arr double pointer
//checArray checks the whether the word is already written or not

class createGrid
{
private:
	int totalWords = -1;
	int longestWord = -1;

	char** arr;
	check_present** checkArray;
	char** wordArr;
public:
	createGrid();
	~createGrid();

	void inputWords(char[], int);
	void outputWords();
	int initializeGrid(int, int);
	int putWordsInGrid(int, int);
	void outputGrid(int, int);
	void displayMessage();

	void deallocate(int);
};

//class findWord will give dimensions/positions of words
//Words input from file are stored in wordArr double pointer
//grid is stored temporarily on arr double pointer

class findWord
{
private:
	int totalWords;
	int startCoordinates[2];
	int endCoordinates[2];

	char** arr;
	char** wordArr;

	dimensions d;
public:
	findWord();
	~findWord();

	void inputGrid(char[]);
	void inputData(char[]);

	void findingWord(char[]);

	bool checkLeft(int);
	bool checkRight(int);
	bool checkDown(int);
	bool checkUp(int);

	bool checkDownLeft(int);
	bool checkDownRight(int);
	bool checkUpLeft(int);
	bool checkUpRight(int);

	void deallocate();
	void displayMessage();
};

//to calculate the lenght of word
int wordLength(char arr[])
{
	int sizeOfWord = 0;

	for (int i = 0; arr[i] != '\0'; i++)
	{
		sizeOfWord++;
	}

	return sizeOfWord;
}

createGrid::createGrid()
{
	checkArray = 0;
	totalWords = 0;
	arr = 0;
	wordArr = 0;
}

createGrid::~createGrid()
{
}

void createGrid::deallocate(int cols)    //To avoid memory leakage
{
	delete[] wordArr;

	delete[] arr;
}

//Taking input from file. File name is entered by user

void createGrid::inputWords(char inputFile[15], int noOfWords)
{
	int i = 0;
	char temp[20];
	longestWord = 0;

	ifstream FIN(inputFile);
	totalWords = noOfWords;

	while (!FIN)
	{
		cout << "\nNo input file found of name \"" << inputFile << "\"!!!\n";
		cout << "Enter correct name: ";
		cin >> inputFile;
		FIN.open(inputFile);
	}

	wordArr = new char* [10];

	while (i < noOfWords)
	{
		FIN.getline(temp, 20);

		int sizeOfWord = wordLength(temp);

		if (sizeOfWord > longestWord)
			longestWord = sizeOfWord;

		wordArr[i] = new char[sizeOfWord + 1];					//Inputting pointers pointing to first letter
		int j = 0;
		for (; j < sizeOfWord; j++)
			wordArr[i][j] = temp[j];							//Inputting rest of letters from pointer of first letter

		wordArr[i][j] = '\0';

		i++;
	}

	FIN.close();
}

void createGrid::outputWords()
{
	cout << "Words read from file:\n\n";

	for (int i = 0; i < totalWords; i++)
	{
		cout << wordArr[i] << endl;
	}

	cout << "\nNow, Grid will be created for these words!!!\n";
	system("pause");
}

//initializes a grid of user entered rows and cols with random letters

int createGrid::initializeGrid(int rows, int cols)
{
	if (rows < longestWord || cols < longestWord)
		return -1;

	arr = new char* [rows];
	for (int i = 0; i < rows; i++)
		arr[i] = new char[cols];

	checkArray = new check_present * [rows];
	for (int i = 0; i < rows; i++)
		checkArray[i] = new check_present[cols];

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			arr[i][j] = (rand() % 26) + 65;
			checkArray[i][j].is_present = not_present;
		}
	}

	return 0;
}

//putWordsInGrid makes a grid withe given words
//the algorithm used is:
//first it is checked the random place obtained is with in grid
//if it is in grid then it is checked whether that place is empty ie not allocated by another word
//if check then it place the word at that positions/places
//this algorithm is used for all directions by changing conditions

int createGrid::putWordsInGrid(int rows, int cols)
{
	int place_1;
	int place_2;
	int wordCount = 0, currentWord = totalWords - 1;
	int counter = 0, warningCount = 0;

	while (wordCount < totalWords)
	{
		place_1 = (rand() % rows) + 0;
		place_2 = (rand() % cols) + 0;

		if (currentWord < 0)
			return 0;

		int sizeOfWord = wordLength(wordArr[currentWord]);

		if (place_2 + sizeOfWord <= cols)
		{
			for (int i = place_1, j = place_2; j < (place_2 + sizeOfWord); j++)
			{
				if (checkArray[i][j].is_present == not_present)
					counter++;
			}
			
			if (counter == sizeOfWord)
			{
				for (int i = place_1, j = place_2, k = 0; k < sizeOfWord; j++, k++)
				{
					arr[i][j] = wordArr[currentWord][k];
					checkArray[i][j].is_present = present;
				}
				wordCount++;
				currentWord--;
				warningCount = 0;
			}
			counter = 0;
		}

		place_1 = (rand() % rows) + 0;
		place_2 = (rand() % cols) + 0;

		if (currentWord < 0)
			return 0;

		sizeOfWord = wordLength(wordArr[currentWord]);

		if (place_2 - sizeOfWord >= 0)
		{
			for (int i = place_1, j = place_2; j > (place_2 - sizeOfWord); j--)
			{
				if (checkArray[i][j].is_present == not_present)
					counter++;
			}

			if (counter == sizeOfWord)
			{
				for (int i = place_1, j = place_2, k = 0; k < sizeOfWord; j--, k++)
				{
					arr[i][j] = wordArr[currentWord][k];
					checkArray[i][j].is_present = present;
				}
				wordCount++;
				currentWord--;
				warningCount = 0;
			}
			counter = 0;
		}
		
		place_1 = (rand() % rows) + 0;
		place_2 = (rand() % cols) + 0;

		if (currentWord < 0)
			return 0;

		sizeOfWord = wordLength(wordArr[currentWord]);
		
		if (place_1 + sizeOfWord <= rows)
		{
			for (int i = place_1, j = place_2; i < (place_1 + sizeOfWord); i++)
			{
				if (checkArray[i][j].is_present == not_present)
					counter++;
			}

			if (counter == sizeOfWord)
			{
				for (int i = place_1, j = place_2, k = 0; k < sizeOfWord; i++, k++)
				{
					arr[i][j] = wordArr[currentWord][k];
					checkArray[i][j].is_present = present;
				}
				wordCount++;
				currentWord--;
				warningCount = 0;
			}
			counter = 0;
		}
		
		place_1 = (rand() % rows) + 0;
		place_2 = (rand() % cols) + 0;

		if (currentWord < 0)
			return 0;

		sizeOfWord = wordLength(wordArr[currentWord]);

		if (place_1 - sizeOfWord >= 0)
		{
			for (int i = place_1, j = place_2; i > (place_1 - sizeOfWord); i--)
			{
				if (checkArray[i][j].is_present == not_present)
					counter++;
			}

			if (counter == sizeOfWord)
			{
				for (int i = place_1, j = place_2, k = 0; k < sizeOfWord; i--, k++)
				{
					arr[i][j] = wordArr[currentWord][k];
					checkArray[i][j].is_present = present;
				}
				wordCount++;
				currentWord--;
				warningCount = 0;
			}
			counter = 0;
		}
		
		place_1 = (rand() % rows) + 0;
		place_2 = (rand() % cols) + 0;

		if (currentWord < 0)
			return 0;

		sizeOfWord = wordLength(wordArr[currentWord]);
		
		if (place_2 + sizeOfWord <= cols && place_1 + sizeOfWord <= rows)
		{
			for (int i = place_1, j = place_2; j < (place_2 + sizeOfWord); j++, i++)
			{
				if (checkArray[i][j].is_present == not_present)
					counter++;
			}

			if (counter == sizeOfWord)
			{
				for (int i = place_1, j = place_2, k = 0; k < sizeOfWord; j++, k++, i++)
				{
					arr[i][j] = wordArr[currentWord][k];
					checkArray[i][j].is_present = present;
				}
				wordCount++;
				currentWord--;
				warningCount = 0;
			}
			counter = 0;
		}
		
		place_1 = (rand() % rows) + 0;
		place_2 = (rand() % cols) + 0;

		if (currentWord < 0)
			return 0;

		sizeOfWord = wordLength(wordArr[currentWord]);

		if (place_2 - sizeOfWord >= 0 && place_1 - sizeOfWord >= 0)
		{
			for (int i = place_1, j = place_2; j > (place_2 - sizeOfWord); j--, i--)
			{
				if (checkArray[i][j].is_present == not_present)
					counter++;
			}

			if (counter == sizeOfWord)
			{
				for (int i = place_1, j = place_2, k = 0; k < sizeOfWord; j--, k++, i--)
				{
					arr[i][j] = wordArr[currentWord][k];
					checkArray[i][j].is_present = present;
				}
				wordCount++;
				currentWord--;
				warningCount = 0;
			}
			counter = 0;
		}
		
		place_1 = (rand() % rows) + 0;
		place_2 = (rand() % cols) + 0;

		if (currentWord < 0)
			return 0;

		sizeOfWord = wordLength(wordArr[currentWord]);

		if (place_1 + sizeOfWord <= rows && place_2 - sizeOfWord >=0)
		{
			for (int i = place_1, j = place_2; i < (place_1 + sizeOfWord); i++, j--)
			{
				if (checkArray[i][j].is_present == not_present)
					counter++;
			}

			if (counter == sizeOfWord)
			{
				for (int i = place_1, j = place_2, k = 0; k < sizeOfWord; i++, k++, j--)
				{
					arr[i][j] = wordArr[currentWord][k];
					checkArray[i][j].is_present = present;
				}
				wordCount++;
				currentWord--;
				warningCount = 0;
			}
			counter = 0;
		}
		
		place_1 = (rand() % rows) + 0;
		place_2 = (rand() % cols) + 0;

		if (currentWord < 0)
			return 0;

		sizeOfWord = wordLength(wordArr[currentWord]);

		if (place_1 - sizeOfWord >= 0 && place_2 + sizeOfWord <= cols)
		{
			for (int i = place_1, j = place_2; i > (place_1 - sizeOfWord); i--, j++)
			{
				if (checkArray[i][j].is_present == not_present)
					counter++;
			}

			if (counter == sizeOfWord)
			{
				for (int i = place_1, j = place_2, k = 0; k < sizeOfWord; i--, k++, j++)
				{
					arr[i][j] = wordArr[currentWord][k];
					checkArray[i][j].is_present = present;
				}
				wordCount++;
				currentWord--;
				warningCount = 0;
			}
			counter = 0;
		}
		
		if(warningCount > 50)
			return -1;

		warningCount++;
	}

	return 0;
}

//to store output in file. Name is provided by user

void createGrid::outputGrid(int rows, int cols)
{
	char outputFile[20];

	cout << "\nEnter the name for output file in which grid will be stored: ";
	cin >> outputFile;

	ofstream FOUT(outputFile);

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			FOUT << arr[i][j] << " ";
		}
		FOUT << endl;
	}

	FOUT.close();
}

void createGrid::displayMessage()
{
	cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
	cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
	cout << "\t\t\t\t************************************\n"
		<< "\t\t\t\t* Grid has been created in file!!! *\n"
		<< "\t\t\t\t************************************\n";
	cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
	cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
	cout << "Now you will return to home screen!!!\n";
}


findWord::findWord()
{
	totalWords = 0;
	arr = 0;
	wordArr = 0;
	startCoordinates[0] = 0, startCoordinates[1] = 0;
	endCoordinates[0] = 0, endCoordinates[1] = 0;
}

findWord::~findWord()
{
}

//taking in data from file
//which contains dimensions of grid
//number of words
//and words

void findWord::inputData(char inputFile[])
{

	ifstream FIN(inputFile);

	while (!FIN)
	{
		cout << "\nNo input file found of name \"" << inputFile << "\"!!!\n";
		cout << "Enter correct name: ";
		cin >> inputFile;
		FIN.open(inputFile);
	}

	FIN >> d.rows >> d.cols;

	FIN >> totalWords;

	wordArr = new char* [totalWords + 1];

	int i = 0;
	char temp[15];

	while (i <= totalWords)
	{
		FIN.getline(temp, 15);

		int sizeOfWord = wordLength(temp);

		wordArr[i] = new char[sizeOfWord + 1];					//Inputting pointers pointing to first letter
		int j = 0;
		for (; j < sizeOfWord; j++)
			wordArr[i][j] = temp[j];							//Inputting rest of letters from pointer of first letter

		wordArr[i][j] = '\0';

		i++;
	}

	FIN.close();
}

//Taking in grid in file entered by user

void findWord::inputGrid(char inputGrid[])
{
	ifstream FIN(inputGrid);
	
	while (!FIN)
	{
		cout << "\nNo input file found of name \"" << inputGrid << "\"!!!\n";
		cout << "Enter correct name: ";
		cin >> inputGrid;
		FIN.open(inputGrid);
	}
	
	arr = new char* [d.rows];
	for (int i = 0; i < d.rows; i++)
		arr[i] = new char[d.cols];

	for (int i = 0; i < d.rows; i++)
		for (int j = 0; j < d.cols; j++)
			FIN >> arr[i][j];

	FIN.close();
}

//findingWord checks conditions provided below and outputs positions on console and file

void findWord::findingWord(char outputFile[])
{
	int wordNo = 1;

	ofstream FOUT(outputFile);

	while (wordNo <= totalWords)              //using if else in loop until word found
	{
		if (checkLeft(wordNo) == true)
		{
			cout << "\nWord '" << wordArr[wordNo] << "' Start From (" << startCoordinates[0] << ", "
				<< startCoordinates[1] << ") " << "End At (" << endCoordinates[0] << ", "
				<< endCoordinates[1] << ") ";
			FOUT << "\nWord '" << wordArr[wordNo] << "' Start From (" << startCoordinates[0] << ", "
				<< startCoordinates[1] << ") " << "End At (" << endCoordinates[0] << ", "
				<< endCoordinates[1] << ") ";
		}
		else if (checkRight(wordNo) == true)
		{
			cout << "\nWord '" << wordArr[wordNo] << "' Start From (" << startCoordinates[0] << ", "
				<< startCoordinates[1] << ") " << "End At (" << endCoordinates[0] << ", "
				<< endCoordinates[1] << ") ";
			FOUT << "\nWord '" << wordArr[wordNo] << "' Start From (" << startCoordinates[0] << ", "
				<< startCoordinates[1] << ") " << "End At (" << endCoordinates[0] << ", "
				<< endCoordinates[1] << ") ";
		}
		else if (checkUp(wordNo) == true)
		{
			cout << "\nWord '" << wordArr[wordNo] << "' Start From (" << startCoordinates[0] << ", "
				<< startCoordinates[1] << ") " << "End At (" << endCoordinates[0] << ", "
				<< endCoordinates[1] << ") ";
			FOUT << "\nWord '" << wordArr[wordNo] << "' Start From (" << startCoordinates[0] << ", "
				<< startCoordinates[1] << ") " << "End At (" << endCoordinates[0] << ", "
				<< endCoordinates[1] << ") ";
		}
		else if (checkDown(wordNo) == true)
		{
			cout << "\nWord '" << wordArr[wordNo] << "' Start From (" << startCoordinates[0] << ", "
				<< startCoordinates[1] << ") " << "End At (" << endCoordinates[0] << ", "
				<< endCoordinates[1] << ") ";
			FOUT << "\nWord '" << wordArr[wordNo] << "' Start From (" << startCoordinates[0] << ", "
				<< startCoordinates[1] << ") " << "End At (" << endCoordinates[0] << ", "
				<< endCoordinates[1] << ") ";
		}
		else if (checkDownLeft(wordNo) == true)
		{
			cout << "\nWord '" << wordArr[wordNo] << "' Start From (" << startCoordinates[0] << ", "
				<< startCoordinates[1] << ") " << "End At (" << endCoordinates[0] << ", "
				<< endCoordinates[1] << ") ";
			FOUT << "\nWord '" << wordArr[wordNo] << "' Start From (" << startCoordinates[0] << ", "
				<< startCoordinates[1] << ") " << "End At (" << endCoordinates[0] << ", "
				<< endCoordinates[1] << ") ";
		}
		else if (checkDownRight(wordNo) == true)
		{
			cout << "\nWord '" << wordArr[wordNo] << "' Start From (" << startCoordinates[0] << ", "
				<< startCoordinates[1] << ") " << "End At (" << endCoordinates[0] << ", "
				<< endCoordinates[1] << ") ";
			FOUT << "\nWord '" << wordArr[wordNo] << "' Start From (" << startCoordinates[0] << ", "
				<< startCoordinates[1] << ") " << "End At (" << endCoordinates[0] << ", "
				<< endCoordinates[1] << ") ";
		}
		else if (checkUpLeft(wordNo) == true)
		{
			cout << "\nWord '" << wordArr[wordNo] << "' Start From (" << startCoordinates[0] << ", "
				<< startCoordinates[1] << ") " << "End At (" << endCoordinates[0] << ", "
				<< endCoordinates[1] << ") ";
			FOUT << "\nWord '" << wordArr[wordNo] << "' Start From (" << startCoordinates[0] << ", "
				<< startCoordinates[1] << ") " << "End At (" << endCoordinates[0] << ", "
				<< endCoordinates[1] << ") ";
		}
		else if (checkUpRight(wordNo) == true)
		{
			cout << "\nWord '" << wordArr[wordNo] << "' Start From (" << startCoordinates[0] << ", "
				<< startCoordinates[1] << ") " << "End At (" << endCoordinates[0] << ", "
				<< endCoordinates[1] << ") ";
			FOUT << "\nWord '" << wordArr[wordNo] << "' Start From (" << startCoordinates[0] << ", "
				<< startCoordinates[1] << ") " << "End At (" << endCoordinates[0] << ", "
				<< endCoordinates[1] << ") ";
		}
		else
		{
			cout << "\nWord '" << wordArr[wordNo] << "' not found!!!";
			FOUT << "\nWord '" << wordArr[wordNo] << "' not found!!!";
		}

		wordNo++;
	}

	FOUT.close();
}

//Direction checking
//Algorithm used:
//It will check different conditions using lenght of word
//and returns word positions if found

bool findWord::checkLeft(int wordNo)
{
	int j = 0;
	int counter = 0;

	int sizeOfWord = wordLength(wordArr[wordNo]);

	for (int x = 0; x < d.rows; x++)
	{
		for (int y = 0; y < d.cols; y++)
		{
			j = 0;
			if (arr[x][y] == wordArr[wordNo][j])				//Running Grid in loop and matching first alphabet
			{
				startCoordinates[0] = x;
				startCoordinates[1] = y;
				if (y - sizeOfWord < 0)							//To avoid accessing uninitialized memory
				{
					startCoordinates[0] = -1;
					startCoordinates[1] = -1;
				}
				else
				{
					int sy = y;

					for (j = 0; j < sizeOfWord; j++, sy--)		//Comparing rest of word
						if (arr[x][sy] == wordArr[wordNo][j])
							counter++;
					if (counter == sizeOfWord)
					{
						sy++;
						endCoordinates[0] = x;					//getting points
						endCoordinates[1] = sy;
						counter = 0;

						return true;
					}
					else
					{
						counter = 0;							//resetting if not proved
						startCoordinates[0] = -1;
						startCoordinates[1] = -1;
					}
				}
			}
		}
	}

	return false;
}

//Direction checking
//Algorithm used:
//It will check different conditions using lenght of word
//and returns word positions if found

bool findWord::checkRight(int wordNo)
{
	int j = 0;
	int counter = 0;

	int sizeOfWord = wordLength(wordArr[wordNo]);

	for (int x = 0; x < d.rows; x++)
	{
		for (int y = 0; y < d.cols; y++)
		{
			j = 0;
			if (arr[x][y] == wordArr[wordNo][j])				//Running Grid in loop and matching first alphabet
			{
				startCoordinates[0] = x;
				startCoordinates[1] = y;
				if (y + sizeOfWord > d.cols)					//To avoid accessing uninitialized memory
				{
					startCoordinates[0] = -1;
					startCoordinates[1] = -1;
				}
				else
				{
					int sy = y;

					for (j = 0; j < sizeOfWord; j++, sy++)		//Comparing rest of word
						if (arr[x][sy] == wordArr[wordNo][j])
							counter++;
					if (counter == sizeOfWord)
					{
						sy--;
						endCoordinates[0] = x;					//getting points
						endCoordinates[1] = sy;
						counter = 0;

						return true;
					}
					else
					{
						counter = 0;
						startCoordinates[0] = -1;				//resetting if not proved
						startCoordinates[1] = -1;
					}
				}
			}
		}
	}

	return false;
}

//Direction checking
//Algorithm used:
//It will check different conditions using lenght of word
//and returns word positions if found

bool findWord::checkUp(int wordNo)
{
	int j = 0;
	int counter = 0;

	int sizeOfWord = wordLength(wordArr[wordNo]);

	for (int x = 0; x < d.rows; x++)
	{
		for (int y = 0; y < d.cols; y++)
		{
			j = 0;
			if (arr[x][y] == wordArr[wordNo][j])				//Running Grid in loop and matching first alphabet
			{
				startCoordinates[0] = x;
				startCoordinates[1] = y;
				if (x - sizeOfWord < 0)							//To avoid accessing uninitialized memory
				{
					startCoordinates[0] = -1;
					startCoordinates[1] = -1;
				}
				else
				{
					int sx = x;

					for (j = 0; j < sizeOfWord; j++, sx--)		//Comparing rest of word
						if (arr[sx][y] == wordArr[wordNo][j])
							counter++;
					if (counter == sizeOfWord)
					{
						sx++;
						endCoordinates[0] = sx;					//getting points
						endCoordinates[1] = y;
						counter = 0;

						return true;
					}
					else
					{
						counter = 0;
						startCoordinates[0] = -1;				//resetting if not proved
						startCoordinates[1] = -1;
					}
				}
			}
		}
	}

	return false;
}

//Direction checking
//Algorithm used:
//It will check different conditions using lenght of word
//and returns word positions if found

bool findWord::checkDown(int wordNo)
{
	int j = 0;
	int counter = 0;

	int sizeOfWord = wordLength(wordArr[wordNo]);

	for (int x = 0; x < d.rows; x++)
	{
		for (int y = 0; y < d.cols; y++)
		{
			j = 0;
			if (arr[x][y] == wordArr[wordNo][j])				//Running Grid in loop and matching first alphabet
			{
				startCoordinates[0] = x;
				startCoordinates[1] = y;
				if (x + sizeOfWord > d.rows)					//To avoid accessing uninitialized memory
				{
					startCoordinates[0] = -1;
					startCoordinates[1] = -1;
				}
				else
				{
					int sx = x;

					for (j = 0; j < sizeOfWord; j++, sx++)		//Comparing rest of word
						if (arr[sx][y] == wordArr[wordNo][j])
							counter++;
					if (counter == sizeOfWord)
					{
						sx--;
						endCoordinates[0] = sx;					//getting points
						endCoordinates[1] = y;
						counter = 0;

						return true;
					}
					else
					{
						counter = 0;
						startCoordinates[0] = -1;				//resetting if not proved
						startCoordinates[1] = -1;
					}
				}
			}
		}
	}

	return false;
}

//Direction checking
//Algorithm used:
//It will check different conditions using lenght of word
//and returns word positions if found

bool findWord::checkDownLeft(int wordNo)
{
	int j = 0;
	int counter = 0;

	int sizeOfWord = wordLength(wordArr[wordNo]);

	for (int x = 0; x < d.rows; x++)
	{
		for (int y = 0; y < d.cols; y++)
		{
			j = 0;
			if (arr[x][y] == wordArr[wordNo][j])						//Running Grid in loop and matching first alphabet
			{
				startCoordinates[0] = x;
				startCoordinates[1] = y;
				if (x + sizeOfWord > d.rows || y - sizeOfWord < 0)		//To avoid accessing uninitialized memory
				{
					startCoordinates[0] = -1;
					startCoordinates[1] = -1;
				}
				else
				{
					int sx = x;
					int sy = y;

					for (j = 0; j < sizeOfWord; j++, sx++, sy--)		//Comparing rest of word
						if (arr[sx][sy] == wordArr[wordNo][j])
							counter++;
					if (counter == sizeOfWord)
					{
						sx--;
						sy++;
						endCoordinates[0] = sx;							//getting points
						endCoordinates[1] = sy;
						counter = 0;

						return true;
					}
					else
					{
						counter = 0;
						startCoordinates[0] = -1;						//resetting if not proved
						startCoordinates[1] = -1;
					}
				}
			}
		}
	}

	return false;
}

//Direction checking
//Algorithm used:
//It will check different conditions using lenght of word
//and returns word positions if found

bool findWord::checkDownRight(int wordNo)
{
	int j = 0;
	int counter = 0;

	int sizeOfWord = wordLength(wordArr[wordNo]);

	for (int x = 0; x < d.rows; x++)
	{
		for (int y = 0; y < d.cols; y++)
		{
			j = 0;
			if (arr[x][y] == wordArr[wordNo][j])							//Running Grid in loop and matching first alphabet
			{
				startCoordinates[0] = x;
				startCoordinates[1] = y;
				if (x + sizeOfWord > d.rows || y + sizeOfWord > d.cols)		//To avoid accessing uninitialized memory
				{
					startCoordinates[0] = -1;
					startCoordinates[1] = -1;
				}
				else
				{
					int sx = x;
					int sy = y;

					for (j = 0; j < sizeOfWord; j++, sx++, sy++)			//Comparing rest of word
						if (arr[sx][sy] == wordArr[wordNo][j])
							counter++;
					if (counter == sizeOfWord)
					{
						sx--;
						sy--;
						endCoordinates[0] = sx;								//getting points
						endCoordinates[1] = sy;
						counter = 0;

						return true;
					}
					else
					{
						counter = 0;
						startCoordinates[0] = -1;							//resetting if not proved
						startCoordinates[1] = -1;
					}
				}
			}
		}
	}

	return false;
}

//Direction checking
//Algorithm used:
//It will check different conditions using lenght of word
//and returns word positions if found

bool findWord::checkUpLeft(int wordNo)
{
	int j = 0;
	int counter = 0;

	int sizeOfWord = wordLength(wordArr[wordNo]);

	for (int x = 0; x < d.rows; x++)
	{
		for (int y = 0; y < d.cols; y++)
		{
			j = 0;
			if (arr[x][y] == wordArr[wordNo][j])						//Running Grid in loop and matching first alphabet
			{
				startCoordinates[0] = x;
				startCoordinates[1] = y;
				if (x - sizeOfWord < 0 || y - sizeOfWord < 0)			//To avoid accessing uninitialized memory
				{
					startCoordinates[0] = -1;
					startCoordinates[1] = -1;
				}
				else
				{
					int sx = x;
					int sy = y;

					for (j = 0; j < sizeOfWord; j++, sx--, sy--)		//Comparing rest of word
						if (arr[sx][sy] == wordArr[wordNo][j])
							counter++;
					if (counter == sizeOfWord)
					{
						sx++;
						sy++;
						endCoordinates[0] = sx;							//getting points
						endCoordinates[1] = sy;
						counter = 0;

						return true;
					}
					else
					{
						counter = 0;
						startCoordinates[0] = -1;						//resetting if not proved
						startCoordinates[1] = -1;
					}
				}
			}
		}
	}

	return false;
}

//Direction checking
//Algorithm used:
//It will check different conditions using lenght of word
//and returns word positions if found

bool findWord::checkUpRight(int wordNo)
{
	int j = 0;
	int counter = 0;

	int sizeOfWord = wordLength(wordArr[wordNo]);

	for (int x = 0; x < d.rows; x++)
	{
		for (int y = 0; y < d.cols; y++)
		{
			j = 0;
			if (arr[x][y] == wordArr[wordNo][j])						//Running Grid in loop and matching first alphabet
			{
				startCoordinates[0] = x;
				startCoordinates[1] = y;
				if (x - sizeOfWord < 0 || y + sizeOfWord > d.cols)		//To avoid accessing uninitialized memory
				{
					startCoordinates[0] = -1;
					startCoordinates[1] = -1;
				}
				else
				{
					int sx = x;
					int sy = y;

					for (j = 0; j < sizeOfWord; j++, sx--, sy++)		//Comparing rest of word
						if (arr[sx][sy] == wordArr[wordNo][j])
							counter++;
					if (counter == sizeOfWord)
					{
						sx++;
						sy--;
						endCoordinates[0] = sx;							//getting points
						endCoordinates[1] = sy;
						counter = 0;

						return true;
					}
					else
					{
						counter = 0;
						startCoordinates[0] = -1;						//resetting if not proved
						startCoordinates[1] = -1;
					}
				}
			}
		}
	}

	return false;
}

//Direction checking
//Algorithm used:
//It will check different conditions using lenght of word
//and returns word positions if found

void findWord::deallocate()    //To avoid memory leakage
{
	delete[] wordArr;

	for (int i = 0; i < totalWords; i++)
		delete[] arr[i];

	delete[] arr;
}

//Direction checking
//Algorithm used:
//It will check different conditions using lenght of word
//and returns word positions if found

void findWord::displayMessage()
{
	cout << endl;
	system("pause");
	cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
	cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
	cout << "\t\t\t\t****************************************\n"
		<< "\t\t\t\t* Dimensions has been saved in file!!! *\n"
		<< "\t\t\t\t****************************************\n";
	cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
	cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
	cout << "Now you will return to home screen!!!!!!\n";
	system("pause");
	cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
	cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
}

int main()
{
	char option = ' ';

	while (option != 'Q' && option != 'q')
	{
		cout << "\n1- Create Grid (C)\n"
			<< "2- Search Words From Grid (S)\n"
			<< "3- Quit (Q)\n";

		cout << "\nEnter your option: ";
		cin >> option;

		if (option == 'C' || option == 'c')
		{
			char inputFileName[20];
			int noOfWords = 0, rows, cols;

			createGrid Grid;

			cout << "\nEnter name of input file containing words with file format: ";
			cin >> inputFileName;

			cout << "\nEnter number of words: ";
			cin >> noOfWords;

			Grid.inputWords(inputFileName, noOfWords);
			Grid.outputWords();

			cout << "\nInput Rows: ";
			cin >> rows;
			cout << "\nInput Cols: ";
			cin >> cols;

			if(Grid.initializeGrid(rows, cols) == -1)
			{
				cout << "\nGrid cannot be formed, return to the home screen.\n";
				system("pause");
			}
			else
			{
				if (Grid.putWordsInGrid(rows, cols) == -1)
				{
					cout << "\nGrid cannot be formed, return to the home screen.\n";
					system("pause");
				}
				else
				{
					Grid.outputGrid(rows, cols);
					Grid.displayMessage();
					system("pause");
					cout << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl << endl;
				}
			}
			
			Grid.deallocate(cols);
		}
		else if (option == 'S' || option == 's')
		{
			findWord FW;

			char gridFile[20];
			char inputFile[20];
			char outputFile[20];

			cout << "\nEnter name of file which has grid: ";
			cin >> gridFile;

			cout << "\nEnter name of file which has input to be searched: ";
			cin >> inputFile;

			FW.inputData(inputFile);
			FW.inputGrid(gridFile);

			cout << "\nEnter name of output file for results: ";
			cin >> outputFile;

			FW.findingWord(outputFile);
			FW.deallocate();
			FW.displayMessage();
		}
		else if (option == 'Q' || option == 'q')
		{
			cout << "\nProgram will now close!!!\n";
		}
		else
			cout << "\nOption not available!!!\nChoose valid option!\n";
	}

	return 0;
}