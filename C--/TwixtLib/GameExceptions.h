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