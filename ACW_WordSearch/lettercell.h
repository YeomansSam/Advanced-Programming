#pragma once
#include <string>
#include "lettercell.h"
using namespace std;


class lettercell
{
public:
	lettercell();
	lettercell(const lettercell &plettercell); //copy
	lettercell &operator=(const lettercell &plettercell); // assignment
	~lettercell(); // destructor
	
	void setLetter(const char& letter);
	char getLetter(void) const;
	void setRow(const char& letter);
	char getRow(void) const;
	void setColumn(const char& letter);
	char getColumn(void) const;
	void setUp(lettercell* const cell);
	lettercell* getUp(void) const;
	void setDown(lettercell* const cell);
	lettercell* getDown(void) const;
	void setLeft(lettercell* const cell);
	lettercell* getLeft(void) const;
	void setRight(lettercell* const cell);
	lettercell* getRight(void) const;
	void setUpLeft(lettercell* const cell);
	lettercell* getUpLeft(void) const;
	void setUpRight(lettercell* const cell);
	lettercell* getUpRight(void) const;
	void setDownRight(lettercell* const cell);
	lettercell* getDownRight(void) const;
	void setDownLeft(lettercell* const cell);
	lettercell* getDownLeft(void) const;
	

	

private:
	char m_letter;
	char m_Row;
	char m_Column;
	lettercell* m_Up;
	lettercell* m_Down;
	lettercell* m_Left;
	lettercell* m_Right;
	lettercell* m_UpLeft;
	lettercell* m_UpRight;
	lettercell* m_DownRight;
	lettercell* m_DownLeft;
};

