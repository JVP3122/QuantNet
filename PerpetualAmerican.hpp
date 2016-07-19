// This file contains function prototypes for the Perpetual American option class

#ifndef PERPETUALAMERICAN_HPP
#define PERPETUALAMERICAN_HPP

#include"Option.hpp"
#include<vector>

class PerpetualAmerican : public Option {
private:
	bool PerpAmerFlag;	// Flag which will tell the mesher whether this is a Perpetual American option
public:
	PerpetualAmerican();	// Default constructor
	PerpetualAmerican(double k, double sig, double rate, double q, double s);	// Constructor with input
	PerpetualAmerican(const PerpetualAmerican&);	// Copy constructor
	~PerpetualAmerican();	// Destructor

	PerpetualAmerican& operator = (const PerpetualAmerican&);	// Assignment operator

	// Getter functions
	double T() const;
	double K() const;
	double sigma() const;
	double r() const;
	double S() const;
	double q() const;

	// Setter functions
	void T(const double&);
	void K(const double&);
	void sigma(const double&);
	void r(const double&);
	void S(const double&);
	void q(const double&);

	// Call Price function
	double Call() const;

	// Put Price function
	double Put() const;

	// ToString Function
	std::string ToString() const;

	friend std::ostream& operator << (std::ostream&, const PerpetualAmerican&);	// Send to ostream

	// Mesh functions to return arrays of results
	boost::tuple<std::vector<double>, std::vector<double>> CallRange();
	boost::tuple<std::vector<double>, std::vector<double>> PutRange();
};

#endif	// !PERPETUALAMERICAN_HPP