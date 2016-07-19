#include"Option.hpp"
#include<sstream>

Option::Option() : T_val(1), K_val(100), sigma_val(0.20), r_val(0.08), S_val(100), q_val(0) {}	// Default constructor

Option::Option(double t, double k, double sig, double rate, double q, double s) : T_val(t), K_val(k), sigma_val(sig), r_val(rate), q_val(q), S_val(s) {}	// Constructor with input

Option::Option(const Option& input) : T_val(input.T_val), K_val(input.K_val), sigma_val(input.sigma_val), r_val(input.r_val), q_val(input.q_val), S_val(input.S_val) {}	// Copy constructor

Option::~Option() {}	// Destructor

Option& Option::operator= (const Option& input) {
	if (&input == this)
		return *this;

	T_val = input.T_val;
	K_val = input.K_val;
	sigma_val = input.sigma_val;
	r_val = input.r_val;
	S_val = input.S_val;
	q_val = input.q_val;
	return *this;
}

// Getter functions
double Option::T() const {
	return T_val;
}

double Option::K() const {
	return K_val;
}

double Option::sigma() const {
	return sigma_val;
}

double Option::r() const {
	return r_val;
}

double Option::S() const {
	return S_val;
}

double Option::q() const {
	return q_val;
}

// Setter functions
void Option::T(const double& input) {
	T_val = input;
}

void Option::K(const double& input) {
	K_val = input;
}

void Option::sigma(const double& input) {
	sigma_val = input;
}

void Option::r(const double& input) {
	r_val = input;
}

void Option::S(const double& input) {
	S_val = input;
}

void Option::q(const double& input) {
	q_val = input;
}

// ToString Function
std::string Option::ToString() const {
	std::stringstream ss;
	ss << "T = " << T_val << ", K = " << K_val << ", sig = " << sigma_val << ", r = " << r_val << ", S = " << S_val << ", q = " << q_val;
	return ss.str();
}

std::ostream& operator << (std::ostream& os, const Option& input) {	// Send to ostream
	os << input.ToString();
	return os;
}