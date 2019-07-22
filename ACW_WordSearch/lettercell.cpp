#include "lettercell.h"





lettercell::lettercell()
{
	m_letter = 0;
	m_Row = 0;
	m_Column = 0;
	m_Up = nullptr;
	m_Down = nullptr;
	m_Left = nullptr;
	m_Right = nullptr;
	m_UpLeft = nullptr;
	m_UpRight = nullptr;
	m_DownRight = nullptr;
	m_DownLeft = nullptr;
	
}

lettercell::lettercell(const lettercell &plettercell) : m_letter(plettercell.m_letter), m_Row(plettercell.m_Row), m_Column(plettercell.m_Column), m_Up(plettercell.m_Up), m_Down(plettercell.m_Down), m_Left(plettercell.m_Left), m_Right(plettercell.m_Right), m_UpLeft(plettercell.m_UpLeft), m_UpRight(plettercell.m_UpRight), m_DownRight(plettercell.m_DownRight), m_DownLeft(plettercell.m_DownLeft)
{
	m_letter = 0;
	m_Row = 0;
	m_Column = 0;
	m_Up = nullptr;
	m_Down = nullptr;
	m_Left = nullptr;
	m_Right = nullptr;
	m_UpLeft = nullptr;
	m_UpRight = nullptr;
	m_DownRight = nullptr;
	m_DownLeft = nullptr;
	
}

lettercell & lettercell::operator=(const lettercell &plettercell)
{
	if (this != &plettercell)
	{
		m_letter = plettercell.m_letter;
		m_Column = plettercell.m_Column;
		m_Row = plettercell.m_Row;
		m_Up = plettercell.m_Up;
		m_Down = plettercell.m_Down;
		m_Left = plettercell.m_Left;
		m_Right = plettercell.m_Right;
		m_UpRight = plettercell.m_UpRight;
		m_DownRight = plettercell.m_DownRight;
		m_DownLeft = plettercell.m_DownLeft;
		m_UpLeft = plettercell.m_UpLeft;
	}
	return *this;
}


lettercell::~lettercell()
{
}


void lettercell::setLetter(const char& letter)
{
	m_letter = letter;
}

char lettercell::getLetter(void) const
{
	return m_letter;
}

void lettercell::setRow(const char & letter)
{
	m_Row = letter;
}

char lettercell::getRow(void) const
{
	return m_Row;
}

void lettercell::setColumn(const char & letter)
{
	m_Column = letter;
}

char lettercell::getColumn(void) const
{
	return m_Column;
}

void lettercell::setUp(lettercell* const cell) 
{
	m_Up = cell;
}

lettercell * lettercell::getUp(void) const
{
	return m_Up;
}

void lettercell::setDown(lettercell* const cell)
{
	m_Down = cell;
}

lettercell * lettercell::getDown(void) const
{
	return m_Down;
}

void lettercell::setLeft(lettercell* const cell)
{
	m_Left = cell;
}

lettercell * lettercell::getLeft(void) const
{
	return m_Left;
}

void lettercell::setRight(lettercell* const cell)
{
	m_Right = cell;
}

lettercell * lettercell::getRight(void) const
{
	return m_Right;
}

void lettercell::setUpLeft(lettercell* const cell)
{
	m_UpLeft = cell;
}

lettercell * lettercell::getUpLeft(void) const
{
	return m_UpLeft;
}

void lettercell::setUpRight(lettercell* const cell)
{
	m_UpRight = cell;
}

lettercell * lettercell::getUpRight(void) const
{
	return m_UpRight;
}

void lettercell::setDownRight(lettercell* const cell)
{
	m_DownRight = cell;
}

lettercell * lettercell::getDownRight(void) const
{
	return m_DownRight;
}

void lettercell::setDownLeft(lettercell* const cell)
{
	m_DownLeft = cell;
}

lettercell * lettercell::getDownLeft(void) const
{
	return m_DownLeft;
}


