// The exceptions class is created proactively though not used at this time.
// The initial derived exception class is only used for copying over options
// and will be used to check if an option with early exercise is copied over
// to a European option

#include "Exceptions.hpp"
#include<sstream>

TypeException::TypeException() {}
TypeException::~TypeException() {}

EarlyExerciseException::EarlyExerciseException() {}
EarlyExerciseException::~EarlyExerciseException() {}

std::string EarlyExerciseException::GetMessage() const {
	std::stringstream ss;
	ss << "Error: Type of option being copied is not correct";
	return ss.str();
}

PerpetualAmericanException::PerpetualAmericanException() {}
PerpetualAmericanException::~PerpetualAmericanException() {}

std::string PerpetualAmericanException::GetMessage() const {
	std::stringstream ss;
	ss << "Error: Type of option being copied is not correct";
	return ss.str();
}