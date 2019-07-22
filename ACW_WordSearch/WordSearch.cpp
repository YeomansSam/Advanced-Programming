#include "WordSearch.h"
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
using namespace std;

vector<string> Dictionary;
int CellCounter;
char SimpleBoard[9][9];
vector<Word> foundWords;
int DictionaryCounter;
vector<string> unmatchedWords;

vector<string> AdvancedDictionary;
char **AdvancedBoard;
int arraySize;
char *AdvancedArray;
lettercell* letterCellArray;

WordSearch::WordSearch(const char * const filename) : Output(filename)
{
}

WordSearch::WordSearch(const WordSearch & pWordSearch) : puzzleName(pWordSearch.puzzleName), dictionaryName(pWordSearch.dictionaryName), Output(pWordSearch.Output) // Copy
{
}

WordSearch & WordSearch::operator=(const WordSearch & pWordSearch) // Assignement Operator
{
	if (this != &pWordSearch)
	{
		puzzleName = pWordSearch.puzzleName;
		dictionaryName = pWordSearch.dictionaryName;
		Output = pWordSearch.Output;
	}
	return *this;
}

WordSearch::~WordSearch() {
	foundWords.clear();
	unmatchedWords.clear();
	Dictionary.clear();

	CellCounter = 0;
	DictionaryCounter = 0;
}

void WordSearch::ReadSimplePuzzle() const {


	ifstream fin(puzzleName);

	if (fin.is_open())
	{

		fin.ignore(1, -1);
		for (int i = 0; i < 9; i++)
		{
			for (int j = 0; j < 9; j++)
			{
				fin >> SimpleBoard[i][j];

			}
		}
	}
	else
	{
		cout << "File not found" << endl;
	}

}

void WordSearch::ReadSimpleDictionary() const {
	ifstream fin(dictionaryName);

	if (fin.is_open())
	{
		string dictionaryWord;

		while (fin >> dictionaryWord)
		{

			Dictionary.push_back(dictionaryWord);

		}
	}
	else
	{
		cout << "File not found" << endl;
	}


}


void WordSearch::ReadAdvancedPuzzle() const {
	ifstream fin(puzzleName);

	if (fin.is_open())
	{

		fin >> arraySize; // Reads the number of the wordsearch file

		char letter;

		AdvancedBoard = new char*[arraySize];
		AdvancedArray = new char[arraySize * arraySize];

		for (int row = 0; row < arraySize; row++)
		{

			AdvancedBoard[row] = &AdvancedArray[row * arraySize];

			for (int column = 0; column < arraySize; column++)
			{

				fin >> letter;
				AdvancedBoard[row][column] = letter;

			}
		}
	}
	linkedListSetter();
}

void WordSearch::ReadAdvancedDictionary() const {
	ifstream fin(dictionaryName);

	if (fin.is_open())
	{
		string dictionaryWord;

		while (fin >> dictionaryWord)
		{
			AdvancedDictionary.push_back(dictionaryWord);
		}
	}
}

void WordSearch::linkedListSetter() const
{
	int CountArray = 0;
	letterCellArray = new lettercell[arraySize * arraySize];

	for (int row = 0; row < arraySize; row++)
	{
		for (int column = 0; column < arraySize; column++)
		{
			letterCellArray[CountArray].setLetter(AdvancedBoard[row][column]);
			letterCellArray[CountArray].setRow(row);
			letterCellArray[CountArray].setColumn(column);

			if (row == 0 && column == 0) // Top Left Corner
			{
				letterCellArray[CountArray].setRight(&letterCellArray[CountArray + 1]);
				letterCellArray[CountArray].setDownRight(&letterCellArray[CountArray + arraySize + 1]);
				letterCellArray[CountArray].setDown(&letterCellArray[CountArray + arraySize]);
			}
			else if (row == 0 && column == arraySize - 1) // Top Right Corner
			{
				letterCellArray[CountArray].setLeft(&letterCellArray[CountArray - 1]);
				letterCellArray[CountArray].setDownLeft(&letterCellArray[CountArray + arraySize - 1]);
				letterCellArray[CountArray].setDown(&letterCellArray[CountArray + arraySize]);
			}
			else if (row == arraySize - 1 && column == arraySize - 1) // Bottom Right Corner
			{
				letterCellArray[CountArray].setUp(&letterCellArray[CountArray - arraySize]);
				letterCellArray[CountArray].setUpLeft(&letterCellArray[CountArray - arraySize - 1]);
				letterCellArray[CountArray].setLeft(&letterCellArray[CountArray - 1]);
			}
			else if (row == arraySize - 1 && column == 0) // Bottom Left Corner
			{
				letterCellArray[CountArray].setRight(&letterCellArray[CountArray + 1]);
				letterCellArray[CountArray].setUpRight(&letterCellArray[CountArray - arraySize - 1]);
				letterCellArray[CountArray].setUp(&letterCellArray[CountArray - arraySize]);
			}
			else if (row == 0 && column > 0 && column < arraySize - 1) // Top Middle 
			{
				letterCellArray[CountArray].setLeft(&letterCellArray[CountArray - 1]);
				letterCellArray[CountArray].setDownLeft(&letterCellArray[CountArray + arraySize - 1]);
				letterCellArray[CountArray].setDown(&letterCellArray[CountArray + arraySize]);
				letterCellArray[CountArray].setDownRight(&letterCellArray[CountArray + arraySize + 1]);
				letterCellArray[CountArray].setRight(&letterCellArray[CountArray + 1]);
			}
			else if (column == arraySize - 1 && row > 0 && row < arraySize - 1) // Right Side Middle
			{
				letterCellArray[CountArray].setUp(&letterCellArray[CountArray - arraySize]);
				letterCellArray[CountArray].setUpLeft(&letterCellArray[CountArray - arraySize - 1]);
				letterCellArray[CountArray].setLeft(&letterCellArray[CountArray - 1]);
				letterCellArray[CountArray].setDownLeft(&letterCellArray[CountArray + arraySize - 1]);
				letterCellArray[CountArray].setDown(&letterCellArray[CountArray + arraySize]);
			}
			else if (row == arraySize - 1 && column > 0 && column < arraySize - 1) // Bottom Middle
			{
				letterCellArray[CountArray].setRight(&letterCellArray[CountArray + 1]);
				letterCellArray[CountArray].setUpRight(&letterCellArray[CountArray - arraySize - 1]);
				letterCellArray[CountArray].setUp(&letterCellArray[CountArray - arraySize]);
				letterCellArray[CountArray].setUpLeft(&letterCellArray[CountArray - arraySize - 1]);
				letterCellArray[CountArray].setLeft(&letterCellArray[CountArray - 1]);
			}
			else if (column == 0 && row > 0 && row < arraySize - 1) // Left Side Middle
			{
				letterCellArray[CountArray].setDown(&letterCellArray[CountArray + arraySize]);
				letterCellArray[CountArray].setDownRight(&letterCellArray[CountArray + arraySize + 1]);
				letterCellArray[CountArray].setRight(&letterCellArray[CountArray + 1]);
				letterCellArray[CountArray].setUpRight(&letterCellArray[CountArray - arraySize - 1]);
				letterCellArray[CountArray].setUp(&letterCellArray[CountArray - arraySize]);
			}
			else
			{
				letterCellArray[CountArray].setUp(&letterCellArray[CountArray - arraySize]);
				letterCellArray[CountArray].setUpRight(&letterCellArray[CountArray - arraySize - 1]);
				letterCellArray[CountArray].setRight(&letterCellArray[CountArray + 1]);
				letterCellArray[CountArray].setDownRight(&letterCellArray[CountArray + arraySize + 1]);
				letterCellArray[CountArray].setDown(&letterCellArray[CountArray + arraySize]);
				letterCellArray[CountArray].setDownLeft(&letterCellArray[CountArray + arraySize - 1]);
				letterCellArray[CountArray].setLeft(&letterCellArray[CountArray - 1]);
				letterCellArray[CountArray].setUpLeft(&letterCellArray[CountArray - arraySize - 1]);
			}
			CountArray++;
		}
	}
	SolvePuzzleAdvanced();
}

void WordSearch::SolvePuzzleSimple() const {
	int StartRow;
	int StartColumn;
	string CheckForWord;

	for (int Row = 0; Row < 9; Row++)
	{
		for (int Column = 0; Column < 9; Column++)
		{
			CheckForWord = "";
			StartRow = Row;
			StartColumn = Column;
			// Searches in the left direction
			while (StartColumn > -1 && StartColumn < 9 && StartRow > -1 && StartRow < 9)
			{
				CellCounter++;
				CheckForWord += SimpleBoard[StartRow][StartColumn];
				for (int i = 0; i < Dictionary.size(); i++)
				{
					++DictionaryCounter;
					if (CheckForWord == Dictionary[i])
					{
						foundWords.push_back({ CheckForWord ,Row, Column });
					}
				}
				--StartColumn;
			}


			CheckForWord = "";
			StartRow = Row;
			StartColumn = Column;
			// Searches in the right direction
			while (StartColumn > -1 && StartColumn < 9 && StartRow > -1 && StartRow < 9)
			{
				CellCounter++;
				CheckForWord += SimpleBoard[StartRow][StartColumn];
				for (int i = 0; i < Dictionary.size(); i++)
				{
					++DictionaryCounter;
					if (CheckForWord == Dictionary[i])
					{
						foundWords.push_back({ CheckForWord ,Row, Column });
					}
				}
				++StartColumn;
			}


			CheckForWord = "";
			StartRow = Row;
			StartColumn = Column;
			// Searches in the down direction
			while (StartColumn > -1 && StartColumn < 9 && StartRow > -1 && StartRow < 9)
			{
				CellCounter++;
				CheckForWord += SimpleBoard[StartRow][StartColumn];
				for (int i = 0; i < Dictionary.size(); i++)
				{
					++DictionaryCounter;
					if (CheckForWord == Dictionary[i])
					{
						foundWords.push_back({ CheckForWord ,Row, Column });
					}
				}
				++StartRow;
			}

			CheckForWord = "";
			StartRow = Row;
			StartColumn = Column;
			// Searches in the up direction
			while (StartColumn > -1 && StartColumn < 9 && StartRow > -1 && StartRow < 9)
			{
				CellCounter++;
				CheckForWord += SimpleBoard[StartRow][StartColumn];
				for (int i = 0; i < Dictionary.size(); i++)
				{
					++DictionaryCounter;
					if (CheckForWord == Dictionary[i])
					{
						foundWords.push_back({ CheckForWord ,Row, Column });
					}
				}
				--StartRow;
			}
			CheckForWord = "";
			StartRow = Row;
			StartColumn = Column;
			// Searches in the up right direction
			while (StartColumn > -1 && StartColumn < 9 && StartRow > -1 && StartRow < 9)
			{
				CellCounter++;
				CheckForWord += SimpleBoard[StartRow][StartColumn];
				for (int i = 0; i < Dictionary.size(); i++)
				{
					++DictionaryCounter;
					if (CheckForWord == Dictionary[i])
					{
						foundWords.push_back({ CheckForWord ,Row, Column });
					}
				}
				--StartRow;
				++StartColumn;
			}
			CheckForWord = "";
			StartRow = Row;
			StartColumn = Column;
			// Searches in the up left direction
			while (StartColumn > -1 && StartColumn < 9 && StartRow > -1 && StartRow < 9)
			{
				CellCounter++;
				CheckForWord += SimpleBoard[StartRow][StartColumn];
				for (int i = 0; i < Dictionary.size(); i++)
				{
					++DictionaryCounter;
					if (CheckForWord == Dictionary[i])
					{
						foundWords.push_back({ CheckForWord ,Row, Column });
					}
				}
				--StartRow;
				--StartColumn;
			}
			CheckForWord = "";
			StartRow = Row;
			StartColumn = Column;
			// Searches in the down right direction
			while (StartColumn > -1 && StartColumn < 9 && StartRow > -1 && StartRow < 9)
			{
				CellCounter++;
				CheckForWord += SimpleBoard[StartRow][StartColumn];
				for (int i = 0; i < Dictionary.size(); i++)
				{
					++DictionaryCounter;
					if (CheckForWord == Dictionary[i])
					{
						foundWords.push_back({ CheckForWord ,Row, Column });
					}
				}
				++StartRow;
				++StartColumn;
			}
			CheckForWord = "";
			StartRow = Row;
			StartColumn = Column;
			// Searches in the down left direction
			while (StartColumn > -1 && StartColumn < 9 && StartRow > -1 && StartRow < 9)
			{
				CellCounter++;
				CheckForWord += SimpleBoard[StartRow][StartColumn];
				for (int i = 0; i < Dictionary.size(); i++)
				{
					++DictionaryCounter;
					if (CheckForWord == Dictionary[i])
					{
						foundWords.push_back({ CheckForWord ,Row, Column });
					}
				}
				++StartRow;
				--StartColumn;
			}
		}
	}
	for (int i = 0; i < Dictionary.size(); i++)
	{
		if (find(foundWords.begin(), foundWords.end(), Dictionary[i]) == foundWords.end())
		{
			unmatchedWords.push_back(Dictionary[i]);
		}
	}
}

void WordSearch::SolvePuzzleAdvanced() const {
	int StartRow;
	int StartColumn;
	string CheckForWord;
	for (int Row = 0; Row < arraySize; Row++)
	{
		for (int Column = 0; Column < arraySize; Column++)
		{
			CheckForWord = "";
			StartRow = Row;
			StartColumn = Column;
			// Searches in the left direction
			while (StartColumn > -1 && StartColumn < arraySize  && StartRow > -1 && StartRow < arraySize)
			{
				CellCounter++;
				CheckForWord += AdvancedBoard[StartRow][StartColumn];
				for (int i = 0; i < AdvancedDictionary.size(); i++)
				{
					++DictionaryCounter;
					if (CheckForWord == AdvancedDictionary[i])
					{
						foundWords.push_back({ CheckForWord ,Row, Column });
					}
				}
				--StartColumn;
			}

			CheckForWord = "";
			StartRow = Row;
			StartColumn = Column;
			// Searches in the right direction
			while (StartColumn > -1 && StartColumn < arraySize && StartRow > -1 && StartRow < arraySize)
			{
				CellCounter++;
				CheckForWord += AdvancedBoard[StartRow][StartColumn];
				for (int i = 0; i < AdvancedDictionary.size(); i++)
				{
					++DictionaryCounter;
					if (CheckForWord == AdvancedDictionary[i])
					{
						foundWords.push_back({ CheckForWord ,Row, Column });
					}
				}
				++StartColumn;
			}
			CheckForWord = "";
			StartRow = Row;
			StartColumn = Column;
			// Searches in the Down direction
			while (StartColumn > -1 && StartColumn < arraySize  && StartRow > -1 && StartRow < arraySize)
			{
				CellCounter++;
				CheckForWord += AdvancedBoard[StartRow][StartColumn];
				for (int i = 0; i < AdvancedDictionary.size(); i++)
				{
					++DictionaryCounter;
					if (CheckForWord == AdvancedDictionary[i])
					{
						foundWords.push_back({ CheckForWord ,Row, Column });
					}
				}
				++StartRow;
			}
			CheckForWord = "";
			StartRow = Row;
			StartColumn = Column;
			// Searches in the Up direction
			while (StartColumn > -1 && StartColumn < arraySize  && StartRow > -1 && StartRow < arraySize)
			{
				CellCounter++;
				CheckForWord += AdvancedBoard[StartRow][StartColumn];
				for (int i = 0; i < AdvancedDictionary.size(); i++)
				{
					++DictionaryCounter;
					if (CheckForWord == AdvancedDictionary[i])
					{
						foundWords.push_back({ CheckForWord ,Row, Column });
					}
				}
				--StartRow;
			}
			CheckForWord = "";
			StartRow = Row;
			StartColumn = Column;
			// Searches in the Up Right direction
			while (StartColumn > -1 && StartColumn < arraySize  && StartRow > -1 && StartRow < arraySize)
			{
				CellCounter++;
				CheckForWord += AdvancedBoard[StartRow][StartColumn];
				for (int i = 0; i < AdvancedDictionary.size(); i++)
				{
					++DictionaryCounter;
					if (CheckForWord == AdvancedDictionary[i])
					{
						foundWords.push_back({ CheckForWord ,Row, Column });
					}
				}
				--StartRow;
				++StartColumn;
			}
			CheckForWord = "";
			StartRow = Row;
			StartColumn = Column;
			// Searches in the Down Right direction
			while (StartColumn > -1 && StartColumn < arraySize  && StartRow > -1 && StartRow < arraySize)
			{
				CellCounter++;
				CheckForWord += AdvancedBoard[StartRow][StartColumn];
				for (int i = 0; i < AdvancedDictionary.size(); i++)
				{
					++DictionaryCounter;
					if (CheckForWord == AdvancedDictionary[i])
					{
						foundWords.push_back({ CheckForWord ,Row, Column });
					}
				}
				++StartRow;
				++StartColumn;
			}
			CheckForWord = "";
			StartRow = Row;
			StartColumn = Column;
			// Searches in the Down Left direction
			while (StartColumn > -1 && StartColumn < arraySize  && StartRow > -1 && StartRow < arraySize)
			{
				CellCounter++;
				CheckForWord += AdvancedBoard[StartRow][StartColumn];
				for (int i = 0; i < AdvancedDictionary.size(); i++)
				{
					++DictionaryCounter;
					if (CheckForWord == AdvancedDictionary[i])
					{
						foundWords.push_back({ CheckForWord ,Row, Column });
					}
				}
				++StartRow;
				--StartColumn;
			}
			CheckForWord = "";
			StartRow = Row;
			StartColumn = Column;
			// Searches in the Up Left direction
			while (StartColumn > -1 && StartColumn < arraySize  && StartRow > -1 && StartRow < arraySize)
			{
				CellCounter++;
				CheckForWord += AdvancedBoard[StartRow][StartColumn];
				for (int i = 0; i < AdvancedDictionary.size(); i++)
				{
					++DictionaryCounter;
					if (CheckForWord == AdvancedDictionary[i])
					{
						foundWords.push_back({ CheckForWord ,Row, Column });
					}
				}
				--StartRow;
				--StartColumn;
			}
		}

	}
	for (int i = 0; i < AdvancedDictionary.size(); i++)
	{
		if (find(foundWords.begin(), foundWords.end(), AdvancedDictionary[i]) == foundWords.end())
		{
			unmatchedWords.push_back(AdvancedDictionary[i]);
		}
	}
}

void WordSearch::WriteResults(const double loadTime, const double solveTime) const
{

	ofstream fout(Output);

	fout << "NUMBER_OF_WORDS_MATCHED " << foundWords.size() << endl << endl;

	fout << "WORDS_MATCHED_IN_GRID" << endl;
	for (int i = 0; i < foundWords.size(); i++)
	{
		fout << foundWords[i].row << " " << foundWords[i].column << " " << foundWords[i].words << endl;
	}

	fout << endl;

	fout << "WORDS_UNMATCHED_IN_GRID" << endl;
	for (int i = 0; i < unmatchedWords.size(); i++)
	{
		fout << unmatchedWords[i] << endl;
	}

	fout << endl;

	fout << "NUMBER_OF_GRID_CELLS_VISITED " << CellCounter << endl << endl;

	fout << "NUMBER_OF_DICTIONARY_ENTRIES_VISITED " << DictionaryCounter << endl << endl;

	fout << "TIME_TO_POPULATE_GRID_STRUCTURE " << loadTime << endl << endl;

	fout << "TIME_TO_SOLVE_PUZZLE " << solveTime << endl << endl;
}