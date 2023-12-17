#include "Bridge.h"


Bridge::Bridge()
	: m_firstPegPos{}
	, m_secondPegPos{}
{}

Bridge::Bridge(Position firstPegPos, Position secondPegPos)
	: m_firstPegPos{ firstPegPos }
	, m_secondPegPos{ secondPegPos }
{}

Position Bridge::GetFirstPegPos() const
{
	return m_firstPegPos;
}

Position Bridge::GetSecondPegPos() const
{
	return m_secondPegPos;
}

bool Bridge::operator==(const Bridge& other) const
{
	if (this->GetFirstPegPos() == other.GetFirstPegPos() && this->GetSecondPegPos() == other.GetSecondPegPos())
		return true;
	if (this->GetFirstPegPos() == other.GetSecondPegPos() && this->GetSecondPegPos() == other.GetFirstPegPos())
		return true;
	return false;

}
