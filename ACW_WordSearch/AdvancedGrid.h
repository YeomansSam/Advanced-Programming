#pragma once
#include <string>
#include "lettercell.h"

using namespace std;
class AdvancedGrid
{
	
public:
	AdvancedGrid();
	~AdvancedGrid();

	void addWords(const char& letter);
	
private:
	lettercell *m_head;

};

