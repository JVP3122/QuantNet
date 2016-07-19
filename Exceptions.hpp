// This exception class is included in case American/Bermudan options are used in the future that would also derive from the Options base class

#ifndef EXCEPTIONS_HPP
#define EXCEPTIONS_HPP

#include<iostream>
#include<string>

class TypeException {
public:
	TypeException();
	~TypeException();
	virtual std::string GetMessage() const = 0;
};

class EarlyExerciseException : public TypeException {
public:
	EarlyExerciseException();
	~EarlyExerciseException();

	std::string GetMessage() const;
};

class PerpetualAmericanException : public TypeException {
public:
	PerpetualAmericanException();
	~PerpetualAmericanException();

	std::string GetMessage() const;
};
#endif // !EXCEPTIONS_HPP