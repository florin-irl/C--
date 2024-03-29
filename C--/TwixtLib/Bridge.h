#pragma once
#include "Position.h"

class Bridge
{
public:
	Bridge();
	Bridge(Position firstPegPos, Position secondPegPos);

	Position GetFirstPegPos() const;
	Position GetSecondPegPos() const;

	bool operator==(const Bridge& other) const;
private:
	Position m_firstPegPos, m_secondPegPos;
};

