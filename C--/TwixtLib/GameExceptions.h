#pragma once
#include <stdexcept>

// TwixtException class //

class TwixtException : public std::logic_error
{
public:
	TwixtException();
	TwixtException(const std::string& message);
};

