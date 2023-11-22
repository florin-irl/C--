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