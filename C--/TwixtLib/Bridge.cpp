#include "Bridge.h"

Bridge::Bridge(Position firstPegPos, Position secondPegPos)
	:m_firstPegPos{ firstPegPos }
	, m_secondPegPos{ secondPegPos }
{
}

Position Bridge::GetFirstPegPos() const
{
	return m_firstPegPos;
}
