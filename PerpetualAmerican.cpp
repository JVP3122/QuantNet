// This file contains function definitions for the PerpetualAmerican Option derived class

#include"PerpetualAmerican.hpp"
#include"Exceptions.hpp"
#include"Pricer.hpp"
#include<sstream>
#include<boost\math\distributions\normal.hpp>
#include<cmath>

// Default constructor
PerpetualAmerican::PerpetualAmerican() : Option(0, 100, 0.1, 0.1, 0.08, 110), PerpAmerFlag(true) {
	T_val = 0;	// Set the time value from the base class to 0 since it is not used in Perpetual American Options
}

// Constructor with input that itself calls the Option class constructor
PerpetualAmerican::PerpetualAmerican(double k, double sig, double rate, double q, double s) : Option(0, k, sig, rate, q, s), PerpAmerFlag(true) {}

// Copy constructor that itself calls the Option class constructor
PerpetualAmerican::PerpetualAmerican(const PerpetualAmerican& input) : Option(input.T_val, input.K_val, input.sigma_val, input.r_val, input.q_val, input.S_val) {
	T_val = 0;	// Set the time value from the base class to 0 since it is not used in Perpetual American Options
	if (input.PerpAmerFlag)
		PerpAmerFlag = input.PerpAmerFlag;
	else
		throw PerpetualAmericanException();	// This exception class is included in case American/Bermudan options are used in the future that would also derive from the Options base class
}

// Destructor
PerpetualAmerican::~PerpetualAmerican() {}

// Assignment operator
PerpetualAmerican& PerpetualAmerican::operator= (const PerpetualAmerican& input) {
	if (&input == this)
		return *this;

	T_val = 0;
	K_val = input.K_val;
	sigma_val = input.sigma_val;
	r_val = input.r_val;
	q_val = input.q_val;
	S_val = input.S_val;
	if (input.PerpAmerFlag)
		PerpAmerFlag = input.PerpAmerFlag;
	else
		throw PerpetualAmericanException();

	return *this;
}

// Getter functions
double PerpetualAmerican::T() const {
	return T_val;
}

double PerpetualAmerican::K() const {
	return K_val;
}

double PerpetualAmerican::sigma() const {
	return sigma_val;
}

double PerpetualAmerican::r() const {
	return r_val;
}

double PerpetualAmerican::S() const {
	return S_val;
}

double PerpetualAmerican::q() const {
	return q_val;
}

// Setter functions
void PerpetualAmerican::T(const double& input) {
	std::cout << "Perpetual American options do not have a time value associated with them.  Assignment did not occur." << std::endl;
	T_val = 0;
}

void PerpetualAmerican::K(const double& input) {
	K_val = input;
}

void PerpetualAmerican::sigma(const double& input) {
	sigma_val = input;
}

void PerpetualAmerican::r(const double& input) {
	r_val = input;
}

void PerpetualAmerican::S(const double& input) {
	S_val = input;
}

void PerpetualAmerican::q(const double& input) {
	q_val = input;
}

// PerpetualAmerican member function calling on the global CallOption function
double PerpetualAmerican::Call() const {
	return PerpetualAmericanCall(K_val, sigma_val, r_val, q_val, S_val);
}

// PerpetualAmerican member function calling on the global PutOption function
double PerpetualAmerican::Put() const {
	return PerpetualAmericanPut(K_val, sigma_val, r_val, q_val, S_val);
}

// ToString Function
std::string PerpetualAmerican::ToString() const {
	std::stringstream ss;
	ss << "K = " << K_val << ", sig = " << sigma_val << ", r = " << r_val << ", S = " << S_val << ", q = " << q_val;
	return ss.str();
}

// Send to ostream
std::ostream& operator << (std::ostream& os, const PerpetualAmerican& input) {
	os << input.ToString();
	return os;
}

// Function to return the vector of parameter values, corresponding Call prices
// and print out the option information for entire range specified by user
boost::tuple<std::vector<double>, std::vector<double>> PerpetualAmerican::CallRange() {
	// Instantiate the tuple to take the input_val and vector of parameter values from mesher class
	boost::tuple<int, std::vector<double>> my_tuple = mesharray<double>(PerpAmerFlag);	// First value is input flag, second is vector of parameter values

	// Instantiate the vector to store price values
	std::vector<double> price_val;

	// Loop to iterate through parameter vector and update corresponding parameter based on input flag
	for (std::vector<double>::const_iterator iter = my_tuple.get<1>().begin(); iter != my_tuple.get<1>().end(); iter++) {
		switch (my_tuple.get<0>()) {
		case 1:
			K_val = *iter;
			break;
		case 2:
			sigma_val = *iter;
			break;
		case 3:
			r_val = *iter;
			break;
		case 4:
			q_val = *iter;
			break;
		case 5:
			S_val = *iter;
			break;
		}
		// Add current price to price_val return vector
		price_val.push_back(Call());
		// Display all necessary information
		std::cout << *this << ". Call Price = " << Call() << std::endl;
	}

	// Create tuple used to return both vectors to user in case he/she wants to use either vector of values elsewhere
	boost::tuple<std::vector<double>, std::vector<double>> return_tuple(price_val, my_tuple.get<1>());
	return return_tuple;
}

// Function to return the vector of parameter values, corresponding Put prices
// and print out the option information for entire range specified by user
boost::tuple<std::vector<double>, std::vector<double>> PerpetualAmerican::PutRange() {
	// Instantiate the tuple to take the input_val and vector of parameter values from mesher class
	boost::tuple<int, std::vector<double>> my_tuple = mesharray<double>(PerpAmerFlag);	// First value is input flag, second is vector of parameter values

	// Instantiate the vector to store price values
	std::vector<double> price_val;

	// Loop to iterate through parameter vector and update corresponding parameter based on input flag
	for (std::vector<double>::const_iterator iter = my_tuple.get<1>().begin(); iter != my_tuple.get<1>().end(); iter++) {
		switch (my_tuple.get<0>()) {
		case 1:
			K_val = *iter;
			break;
		case 2:
			sigma_val = *iter;
			break;
		case 3:
			r_val = *iter;
			break;
		case 4:
			q_val = *iter;
			break;
		case 5:
			S_val = *iter;
			break;
		}
		// Add current price to price_val return vector
		price_val.push_back(Put());
		// Display all necessary information
		std::cout << *this << ". Put Price = " << Put() << std::endl;
	}

	// Create tuple used to return both vectors to user in case he/she wants to use either vector of values elsewhere
	boost::tuple<std::vector<double>, std::vector<double>> return_tuple(price_val, my_tuple.get<1>());
	return return_tuple;
}