#pragma once
#include <iostream>
#include "lettercell.h"
using namespace std;

struct Word {
	string words;
	int row;
	int column;


	bool operator ==(const string & rhs) const { return words == rhs; }

};

class WordSearch {
	const char* puzzleName = "wordsearch_grid.txt";
	const char* dictionaryName = "dictionary.txt";
	const char* Output;
	
	

public:
	
	explicit WordSearch(const char * const filename); // default constructor
	WordSearch(const WordSearch &pWordSearch); // copy constructor
	WordSearch &operator=(const WordSearch &pWordSearch); // assignement
	~WordSearch(); // destructor

	void ReadSimplePuzzle()const;
	void ReadSimpleDictionary()const;
	void ReadAdvancedPuzzle()const;
	void ReadAdvancedDictionary()const;
	void linkedListSetter()const;
	void SolvePuzzleSimple()const;
	void SolvePuzzleAdvanced()const;
	void WriteResults(const	double loadTime, const double solveTime) const;

	
};

