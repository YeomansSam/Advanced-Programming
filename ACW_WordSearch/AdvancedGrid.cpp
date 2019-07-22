#include "AdvancedGrid.h"

using namespace std;


AdvancedGrid::AdvancedGrid() : m_head(0)
{
}


AdvancedGrid::~AdvancedGrid()
{
}

void AdvancedGrid::addWords(const char& letter)
{
	if (!m_head)
	{
		m_head = new lettercell(letter);
	}
        

	else
	{
	
	lettercell *current = m_head;
		lettercell *currentStart = current;

		while (current->getRight() != nullptr)
		{
			current = current->getRight();
		}
		current->setRight(new lettercell(letter));
	}
}



