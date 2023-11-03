#pragma once
#include "Position.h"

class Bridge
{
public:
	Bridge(Position firstPegPos, Position secondPegPos);
private:
	Position m_firstPegPos, m_secondPegPos;
};

