// This file contains function definitions for the European Option derived class

#include"European.hpp"
#include"Exceptions.hpp"
#include"Greeks.hpp"
#include"Pricer.hpp"
#include"DividedDIfferences.hpp"
#include<sstream>
#include<boost\math\distributions\normal.hpp>
#include<cmath>

// Default constructor
European::European() : Option(), early_exercise(false) {}

// Constructor with input that itself calls the Option class constructor
European::European(double t, double k, double sig, double rate, double q, double s) : Option(t, k, sig, rate, q, s), early_exercise(false) {}

// Copy constructor that itself calls the Option class constructor
European::European(const European& input) : Option(input.T_val, input.K_val, input.sigma_val, input.r_val, input.q_val, input.S_val) {
	if (input.early_exercise == false)
		early_exercise = input.early_exercise;
	else
		throw EarlyExerciseException();	// This exception class is included in case American/Bermudan options are used in the future that would also derive from the Options base class
}

// Destructor
European::~European() {}

// Assignment operator
European& European::operator= (const European& input) {
	if (&input == this)
		return *this;

	T_val = input.T_val;
	K_val = input.K_val;
	sigma_val = input.sigma_val;
	r_val = input.r_val;
	q_val = input.q_val;
	S_val = input.S_val;
	if (input.early_exercise == false)
		early_exercise = input.early_exercise;
	else
		throw EarlyExerciseException();

	return *this;
}

// Getter functions
double European::T() const {
	return T_val;
}

double European::K() const {
	return K_val;
}

double European::sigma() const {
	return sigma_val;
}

double European::r() const {
	return r_val;
}

double European::S() const {
	return S_val;
}

double European::q() const {
	return q_val;
}

// Setter functions
void European::T(const double& input) {
	T_val = input;
}

void European::K(const double& input) {
	K_val = input;
}

void European::sigma(const double& input) {
	sigma_val = input;
}

void European::r(const double& input) {
	r_val = input;
}

void European::S(const double& input) {
	S_val = input;
}

void European::q(const double& input) {
	q_val = input;
}

// European member function calling on the global CallOption function
double European::Call() const{
	return CallOption(T_val, K_val, sigma_val, r_val, q_val, S_val);
}

// European member function calling on the global PutOption function
double European::Put() const{
	return PutOption(T_val, K_val, sigma_val, r_val, q_val, S_val);
}

// Put-Call Parity Calculating Call Price
double European::CallParity() const {
	return Put() + S_val - K_val * exp(-r_val * T_val);
}

// Put-Call Parity Calculating Put Price
double European::PutParity() const {
	return Call() - S_val + K_val * exp(-r_val * T_val);
}

// ToString Function
std::string European::ToString() const {
	std::stringstream ss;
	ss << "T = " << T_val << ", K = " << K_val << ", sig = " << sigma_val << ", r = " << r_val << ", S = " << S_val << ", q = " << q_val;
	return ss.str();
}

// Send to ostream
std::ostream& operator << (std::ostream& os, const European& input) {
	os << input.ToString();
	return os;
}

// Function to return the vector of parameter values, corresponding Call prices
// and print out the option information and Put prices (via Put-Call Parity)
// for entire range specified by user
boost::tuple<std::vector<double>, std::vector<double>> European::CallRange() {
	// Instantiate the tuple to take the input_val and vector of parameter values from mesher class
	boost::tuple<int, std::vector<double>> my_tuple = mesharray<double>();	// First value is input flag, second is vector of parameter values

	// Instantiate the vector to store price values
	std::vector<double> price_val;

	// Loop to iterate through parameter vector and update corresponding parameter based on input flag
	for (std::vector<double>::const_iterator iter = my_tuple.get<1>().begin(); iter != my_tuple.get<1>().end(); iter++) {
		switch (my_tuple.get<0>()) {
		case 1:
			T_val = *iter;
			break;
		case 2:
			K_val = *iter;
			break;
		case 3:
			sigma_val = *iter;
			break;
		case 4:
			r_val = *iter;
			break;
		case 5:
			q_val = *iter;
			break;
		case 6:
			S_val = *iter;
			break;
		}
		// Add current price to price_val return vector
		price_val.push_back(Call());
		// Display all necessary information
		std::cout << *this << ". Call Price = " << Call() << ", Put Price (Using Parity) = " << PutParity() << std::endl;
	}

	// Create tuple used to return both vectors to user in case he/she wants to use either vector of values elsewhere
	boost::tuple<std::vector<double>, std::vector<double>> return_tuple(price_val, my_tuple.get<1>());
	return return_tuple;
}

// Function to return the vector of parameter values, corresponding Put prices
// and print out the option information and call prices (via put-call parity)
// for entire range specified by user
boost::tuple<std::vector<double>, std::vector<double>> European::PutRange() {
	// Instantiate the tuple to take the input_val and vector of parameter values from mesher class
	boost::tuple<int, std::vector<double>> my_tuple = mesharray<double>();	// First value is input flag, second is vector of parameter values

	// Instantiate the vector to store price values
	std::vector<double> price_val;

	// Loop to iterate through parameter vector and update corresponding parameter based on input flag
	for (std::vector<double>::const_iterator iter = my_tuple.get<1>().begin(); iter != my_tuple.get<1>().end(); iter++) {
		switch (my_tuple.get<0>()) {
		case 1:
			T_val = *iter;
			break;
		case 2:
			K_val = *iter;
			break;
		case 3:
			sigma_val = *iter;
			break;
		case 4:
			r_val = *iter;
			break;
		case 5:
			q_val = *iter;
			break;
		case 6:
			S_val = *iter;
			break;
		}
		// Add current price to price_val return vector
		price_val.push_back(Put());
		// Display all necessary information
		std::cout << *this << ". Put Price = " << Put() << ", Call Price (Using Parity) = " << CallParity() << std::endl;
	}

	// Create tuple used to return both vectors to user in case he/she wants to use either vector of values elsewhere
	boost::tuple<std::vector<double>, std::vector<double>> return_tuple(price_val, my_tuple.get<1>());
	return return_tuple;
}

// Function to return the vector of parameter values, corresponding Call Delta prices
// and print out the option information for entire range specified by user
boost::tuple<std::vector<double>, std::vector<double>> European::CallDeltaRange() {
	// Instantiate the tuple to take the input_val and vector of parameter values from mesher class
	boost::tuple<int, std::vector<double>> my_tuple = mesharray<double>();	// First value is input flag, second is vector of parameter values

	// Instantiate the vector to store price values
	std::vector<double> price_val;

	// Loop to iterate through parameter vector and update corresponding parameter based on input flag
	for (std::vector<double>::const_iterator iter = my_tuple.get<1>().begin(); iter != my_tuple.get<1>().end(); iter++) {
		switch (my_tuple.get<0>()) {
		case 1:
			T_val = *iter;
			break;
		case 2:
			K_val = *iter;
			break;
		case 3:
			sigma_val = *iter;
			break;
		case 4:
			r_val = *iter;
			break;
		case 5:
			q_val = *iter;
			break;
		case 6:
			S_val = *iter;
			break;
		}
		// Add current price to price_val return vector
		price_val.push_back(CallDelta());
		// Display all necessary information
		std::cout << *this << ". Call Delta Price = " << CallDelta() << std::endl;
	}

	// Create tuple used to return both vectors to user in case he/she wants to use either vector of values elsewhere
	boost::tuple<std::vector<double>, std::vector<double>> return_tuple(price_val, my_tuple.get<1>());
	return return_tuple;
}

// Function to return the vector of parameter values, corresponding Put Delta prices
// and print out the option information for entire range specified by user
boost::tuple<std::vector<double>, std::vector<double>> European::PutDeltaRange() {
	// Instantiate the tuple to take the input_val and vector of parameter values from mesher class
	boost::tuple<int, std::vector<double>> my_tuple = mesharray<double>();	// First value is input flag, second is vector of parameter values

	// Instantiate the vector to store price values
	std::vector<double> price_val;

	// Loop to iterate through parameter vector and update corresponding parameter based on input flag
	for (std::vector<double>::const_iterator iter = my_tuple.get<1>().begin(); iter != my_tuple.get<1>().end(); iter++) {
		switch (my_tuple.get<0>()) {
		case 1:
			T_val = *iter;
			break;
		case 2:
			K_val = *iter;
			break;
		case 3:
			sigma_val = *iter;
			break;
		case 4:
			r_val = *iter;
			break;
		case 5:
			q_val = *iter;
			break;
		case 6:
			S_val = *iter;
			break;
		}
		// Add current price to price_val return vector
		price_val.push_back(PutDelta());
		// Display all necessary information
		std::cout << *this << ". Put Delta Price = " << PutDelta() << std::endl;
	}

	// Create tuple used to return both vectors to user in case he/she wants to use either vector of values elsewhere
	boost::tuple<std::vector<double>, std::vector<double>> return_tuple(price_val, my_tuple.get<1>());
	return return_tuple;
}

// Function to return the vector of parameter values, corresponding Call Gamma prices
// and print out the option information for entire range specified by user
boost::tuple<std::vector<double>, std::vector<double>> European::CallGammaRange() {
	// Instantiate the tuple to take the input_val and vector of parameter values from mesher class
	boost::tuple<int, std::vector<double>> my_tuple = mesharray<double>();	// First value is input flag, second is vector of parameter values

	// Instantiate the vector to store price values
	std::vector<double> price_val;

	// Loop to iterate through parameter vector and update corresponding parameter based on input flag
	for (std::vector<double>::const_iterator iter = my_tuple.get<1>().begin(); iter != my_tuple.get<1>().end(); iter++) {
		switch (my_tuple.get<0>()) {
		case 1:
			T_val = *iter;
			break;
		case 2:
			K_val = *iter;
			break;
		case 3:
			sigma_val = *iter;
			break;
		case 4:
			r_val = *iter;
			break;
		case 5:
			q_val = *iter;
			break;
		case 6:
			S_val = *iter;
			break;
		}
		// Add current price to price_val return vector
		price_val.push_back(CallGamma());
		// Display all necessary information
		std::cout << *this << ". Call Gamma Price = " << CallGamma() << std::endl;
	}

	// Create tuple used to return both vectors to user in case he/she wants to use either vector of values elsewhere
	boost::tuple<std::vector<double>, std::vector<double>> return_tuple(price_val, my_tuple.get<1>());
	return return_tuple;
}

// Function to return the vector of parameter values, corresponding Put Gamma prices
// and print out the option information for entire range specified by user
boost::tuple<std::vector<double>, std::vector<double>> European::PutGammaRange() {
	// Instantiate the tuple to take the input_val and vector of parameter values from mesher class
	boost::tuple<int, std::vector<double>> my_tuple = mesharray<double>();	// First value is input flag, second is vector of parameter values

	// Instantiate the vector to store price values
	std::vector<double> price_val;

	// Loop to iterate through parameter vector and update corresponding parameter based on input flag
	for (std::vector<double>::const_iterator iter = my_tuple.get<1>().begin(); iter != my_tuple.get<1>().end(); iter++) {
		switch (my_tuple.get<0>()) {
		case 1:
			T_val = *iter;
			break;
		case 2:
			K_val = *iter;
			break;
		case 3:
			sigma_val = *iter;
			break;
		case 4:
			r_val = *iter;
			break;
		case 5:
			q_val = *iter;
			break;
		case 6:
			S_val = *iter;
			break;
		}
		// Add current price to price_val return vector
		price_val.push_back(PutGamma());
		// Display all necessary information
		std::cout << *this << ". Put Gamma Price = " << PutGamma() << std::endl;
	}

	// Create tuple used to return both vectors to user in case he/she wants to use either vector of values elsewhere
	boost::tuple<std::vector<double>, std::vector<double>> return_tuple(price_val, my_tuple.get<1>());
	return return_tuple;
}

// Function to return the vector of parameter values, corresponding Call Vega prices
// and print out the option information for entire range specified by user
boost::tuple<std::vector<double>, std::vector<double>> European::CallVegaRange() {
	// Instantiate the tuple to take the input_val and vector of parameter values from mesher class
	boost::tuple<int, std::vector<double>> my_tuple = mesharray<double>();	// First value is input flag, second is vector of parameter values

		// Instantiate the vector to store price values
	std::vector<double> price_val;

	// Loop to iterate through parameter vector and update corresponding parameter based on input flag
	for (std::vector<double>::const_iterator iter = my_tuple.get<1>().begin(); iter != my_tuple.get<1>().end(); iter++) {
		switch (my_tuple.get<0>()) {
		case 1:
			T_val = *iter;
			break;
		case 2:
			K_val = *iter;
			break;
		case 3:
			sigma_val = *iter;
			break;
		case 4:
			r_val = *iter;
			break;
		case 5:
			q_val = *iter;
			break;
		case 6:
			S_val = *iter;
			break;
		}
		// Add current price to price_val return vector
		price_val.push_back(CallVega());
		// Display all necessary information
		std::cout << *this << ". Call Vega Price = " << CallVega() << std::endl;
	}

	// Create tuple used to return both vectors to user in case he/she wants to use either vector of values elsewhere
	boost::tuple<std::vector<double>, std::vector<double>> return_tuple(price_val, my_tuple.get<1>());
	return return_tuple;
}

// Function to return the vector of parameter values, corresponding Put Vega prices
// and print out the option information for entire range specified by user
boost::tuple<std::vector<double>, std::vector<double>> European::PutVegaRange() {
	// Instantiate the tuple to take the input_val and vector of parameter values from mesher class
	boost::tuple<int, std::vector<double>> my_tuple = mesharray<double>();	// First value is input flag, second is vector of parameter values

	// Instantiate the vector to store price values
	std::vector<double> price_val;

	// Loop to iterate through parameter vector and update corresponding parameter based on input flag
	for (std::vector<double>::const_iterator iter = my_tuple.get<1>().begin(); iter != my_tuple.get<1>().end(); iter++) {
		switch (my_tuple.get<0>()) {
		case 1:
			T_val = *iter;
			break;
		case 2:
			K_val = *iter;
			break;
		case 3:
			sigma_val = *iter;
			break;
		case 4:
			r_val = *iter;
			break;
		case 5:
			q_val = *iter;
			break;
		case 6:
			S_val = *iter;
			break;
		}
		// Add current price to price_val return vector
		price_val.push_back(PutVega());
		// Display all necessary information
		std::cout << *this << ". Put Vega Price = " << PutVega() << std::endl;
	}

	// Create tuple used to return both vectors to user in case he/she wants to use either vector of values elsewhere
	boost::tuple<std::vector<double>, std::vector<double>> return_tuple(price_val, my_tuple.get<1>());
	return return_tuple;
}

// Function to return the vector of parameter values, corresponding Call Theta prices
// and print out the option information for entire range specified by user
boost::tuple<std::vector<double>, std::vector<double>> European::CallThetaRange() {
	// Instantiate the tuple to take the input_val and vector of parameter values from mesher class
	boost::tuple<int, std::vector<double>> my_tuple = mesharray<double>();	// First value is input flag, second is vector of parameter values

	// Instantiate the vector to store price values
	std::vector<double> price_val;

	// Loop to iterate through parameter vector and update corresponding parameter based on input flag
	for (std::vector<double>::const_iterator iter = my_tuple.get<1>().begin(); iter != my_tuple.get<1>().end(); iter++) {
		switch (my_tuple.get<0>()) {
		case 1:
			T_val = *iter;
			break;
		case 2:
			K_val = *iter;
			break;
		case 3:
			sigma_val = *iter;
			break;
		case 4:
			r_val = *iter;
			break;
		case 5:
			q_val = *iter;
			break;
		case 6:
			S_val = *iter;
			break;
		}
		// Add current price to price_val return vector
		price_val.push_back(CallTheta());
		// Display all necessary information
		std::cout << *this << ". Call Theta Price = " << CallTheta() << std::endl;
	}

	// Create tuple used to return both vectors to user in case he/she wants to use either vector of values elsewhere
	boost::tuple<std::vector<double>, std::vector<double>> return_tuple(price_val, my_tuple.get<1>());
	return return_tuple;
}

// Function to return the vector of parameter values, corresponding Put Theta prices
// and print out the option information for entire range specified by user
boost::tuple<std::vector<double>, std::vector<double>> European::PutThetaRange() {
	// Instantiate the tuple to take the input_val and vector of parameter values from mesher class
	boost::tuple<int, std::vector<double>> my_tuple = mesharray<double>();	// First value is input flag, second is vector of parameter values

	// Instantiate the vector to store price values
	std::vector<double> price_val;

	// Loop to iterate through parameter vector and update corresponding parameter based on input flag
	for (std::vector<double>::const_iterator iter = my_tuple.get<1>().begin(); iter != my_tuple.get<1>().end(); iter++) {
		switch (my_tuple.get<0>()) {
		case 1:
			T_val = *iter;
			break;
		case 2:
			K_val = *iter;
			break;
		case 3:
			sigma_val = *iter;
			break;
		case 4:
			r_val = *iter;
			break;
		case 5:
			q_val = *iter;
			break;
		case 6:
			S_val = *iter;
			break;
		}
		// Add current price to price_val return vector
		price_val.push_back(PutTheta());
		// Display all necessary information
		std::cout << *this << ". Put Theta Price = " << PutTheta() << std::endl;
	}

	// Create tuple used to return both vectors to user in case he/she wants to use either vector of values elsewhere
	boost::tuple<std::vector<double>, std::vector<double>> return_tuple(price_val, my_tuple.get<1>());
	return return_tuple;
}

// Function to return the vector of parameter values, corresponding Call Rho prices
// and print out the option information for entire range specified by user
boost::tuple<std::vector<double>, std::vector<double>> European::CallRhoRange() {
	// Instantiate the tuple to take the input_val and vector of parameter values from mesher class
	boost::tuple<int, std::vector<double>> my_tuple = mesharray<double>();	// First value is input flag, second is vector of parameter values

	// Instantiate the vector to store price values
	std::vector<double> price_val;

	// Loop to iterate through parameter vector and update corresponding parameter based on input flag
	for (std::vector<double>::const_iterator iter = my_tuple.get<1>().begin(); iter != my_tuple.get<1>().end(); iter++) {
		switch (my_tuple.get<0>()) {
		case 1:
			T_val = *iter;
			break;
		case 2:
			K_val = *iter;
			break;
		case 3:
			sigma_val = *iter;
			break;
		case 4:
			r_val = *iter;
			break;
		case 5:
			q_val = *iter;
			break;
		case 6:
			S_val = *iter;
			break;
		}
		// Add current price to price_val return vector
		price_val.push_back(CallRho());
		// Display all necessary information
		std::cout << *this << ". Call Rho Price = " << CallRho() << std::endl;
	}

	// Create tuple used to return both vectors to user in case he/she wants to use either vector of values elsewhere
	boost::tuple<std::vector<double>, std::vector<double>> return_tuple(price_val, my_tuple.get<1>());
	return return_tuple;
}

// Function to return the vector of parameter values, corresponding Put Rho prices
// and print out the option information for entire range specified by user
boost::tuple<std::vector<double>, std::vector<double>> European::PutRhoRange() {
	// Instantiate the tuple to take the input_val and vector of parameter values from mesher class
	boost::tuple<int, std::vector<double>> my_tuple = mesharray<double>();	// First value is input flag, second is vector of parameter values

	// Instantiate the vector to store price values
	std::vector<double> price_val;

	// Loop to iterate through parameter vector and update corresponding parameter based on input flag
	for (std::vector<double>::const_iterator iter = my_tuple.get<1>().begin(); iter != my_tuple.get<1>().end(); iter++) {
		switch (my_tuple.get<0>()) {
		case 1:
			T_val = *iter;
			break;
		case 2:
			K_val = *iter;
			break;
		case 3:
			sigma_val = *iter;
			break;
		case 4:
			r_val = *iter;
			break;
		case 5:
			q_val = *iter;
			break;
		case 6:
			S_val = *iter;
			break;
		}
		// Add current price to price_val return vector
		price_val.push_back(PutRho());
		// Display all necessary information
		std::cout << *this << ". Put Rho Price = " << PutRho() << std::endl;
	}

	// Create tuple used to return both vectors to user in case he/she wants to use either vector of values elsewhere
	boost::tuple<std::vector<double>, std::vector<double>> return_tuple(price_val, my_tuple.get<1>());
	return return_tuple;
}

// Greeks
double European::CallDelta() const{
	return Delta_Call(T_val, K_val, sigma_val, r_val, q_val, S_val);
}

double European::PutDelta() const{
	return Delta_Put(T_val, K_val, sigma_val, r_val, q_val, S_val);
}

double European::CallGamma() const{
	return Gamma_Call(T_val, K_val, sigma_val, r_val, q_val, S_val);
}

double European::PutGamma() const{
	return Gamma_Put(T_val, K_val, sigma_val, r_val, q_val, S_val);
}

double European::CallVega() const{
	return Vega_Call(T_val, K_val, sigma_val, r_val, q_val, S_val);
}

double European::PutVega() const{
	return Vega_Put(T_val, K_val, sigma_val, r_val, q_val, S_val);
}

double European::CallTheta() const{
	return Theta_Call(T_val, K_val, sigma_val, r_val, q_val, S_val);
}

double European::PutTheta() const{
	return Theta_Put(T_val, K_val, sigma_val, r_val, q_val, S_val);
}

double European::CallRho() const{
	return Rho_Call(T_val, K_val, sigma_val, r_val, q_val, S_val);
}

double European::PutRho() const{
	return Rho_Put(T_val, K_val, sigma_val, r_val, q_val, S_val);
}

// Divided Differences Formulae
double European::DividedCallDelta(const double& h) const{
	return Divided_Delta_Call(T_val, K_val, sigma_val, r_val, q_val, S_val, h);
}

double European::DividedPutDelta(const double& h) const{
	return Divided_Delta_Put(T_val, K_val, sigma_val, r_val, q_val, S_val, h);
}

double European::DividedCallGamma(const double& h) const{
	return Divided_Gamma_Call(T_val, K_val, sigma_val, r_val, q_val, S_val, h);
}

double European::DividedPutGamma(const double& h) const{
	return Divided_Gamma_Put(T_val, K_val, sigma_val, r_val, q_val, S_val, h);
}

double European::DividedCallTheta(const double& h) const{
	return Divided_Theta_Call(T_val, K_val, sigma_val, r_val, q_val, S_val, h);
}

double European::DividedPutTheta(const double& h) const{
	return Divided_Theta_Put(T_val, K_val, sigma_val, r_val, q_val, S_val, h);
}

double European::DividedCallVega(const double& h) const{
	return Divided_Vega_Call(T_val, K_val, sigma_val, r_val, q_val, S_val, h);
}

double European::DividedPutVega(const double& h) const{
	return Divided_Vega_Put(T_val, K_val, sigma_val, r_val, q_val, S_val, h);
}

double European::DividedCallRho(const double& h) const{
	return Divided_Rho_Call(T_val, K_val, sigma_val, r_val, q_val, S_val, h);
}

double European::DividedPutRho(const double& h) const{
	return Divided_Rho_Put(T_val, K_val, sigma_val, r_val, q_val, S_val, h);
}