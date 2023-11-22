#pragma once
#include <stdexcept>

// TwixtException class //

class TwixtException : public std::logic_error
{
public:
	TwixtException();
	TwixtException(const std::string& message);
};

inline TwixtException::TwixtException()
	: std::logic_error("Unknown exception")
{}

inline TwixtException::TwixtException(const std::string& message)
	: std::logic_error(message)
{}

// OcuppiedPositionException class //

class OcuppiedPositionException : public TwixtException
{
public:
	OcuppiedPositionException(const std::string& message);
};

inline OcuppiedPositionException::OcuppiedPositionException(const std::string& message)
	: TwixtException(message)
{}

// OutOfBoundsException class //

class OutOfBoundsException : public TwixtException
{
public:
	OutOfBoundsException(const std::string& message);
};

inline OutOfBoundsException::OutOfBoundsException(const std::string& message)
	: TwixtException(message)
{}

// EnemyBaseException class //

class EnemyBaseException : public TwixtException
{
public:
	EnemyBaseException(const std::string& message);
};

inline EnemyBaseException::EnemyBaseException(const std::string& message)
	: TwixtException(message)
{}

// InvalidBridgeException class //

class InvalidBridgeException : public TwixtException
{
public:
	InvalidBridgeException(const std::string& message);
};

inline InvalidBridgeException::InvalidBridgeException(const std::string& message)
	: TwixtException(message)
{}

// BridgeInTheWayException class //

class BridgeInTheWayException : public InvalidBridgeException
{
public:
	BridgeInTheWayException(const std::string& message);
};

inline BridgeInTheWayException::BridgeInTheWayException(const std::string& message)
	: InvalidBridgeException(message)
{}

// InvalidPegsForBridgeException class //

class InvalidPegsForBridgeException : public InvalidBridgeException
{
public:
	InvalidPegsForBridgeException(const std::string& message);
};

inline InvalidPegsForBridgeException::InvalidPegsForBridgeException(const std::string& message)
	: InvalidBridgeException(message)
{}

// CantFormBridgeException class //

class CantFormBridgeException : public InvalidBridgeException
{
public:
	CantFormBridgeException(const std::string& message);
};

inline CantFormBridgeException::CantFormBridgeException(const std::string& message)
	: InvalidBridgeException(message)
{}