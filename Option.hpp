// This base option class contains values common to all options (T, K, sigma, r, S, q) whether European, American, Bermudan
// The option class is not explicitly used

#ifndef OPTION_HPP
#define OPTION_HPP

#include<iostream>
#include"Pricer.hpp"
#include"mesher.hpp"

class Option {
protected:
	double T_val;		// Time to expiry
	double K_val;		// Strike
	double sigma_val;	// Volatility
	double r_val;		// Risk-free rate - Setting this to 0 along with q = 0 will create the futures option model
	double S_val;		// Underlying current price
	double q_val;		// Constant dividend yield - Setting this to 0 with non-zero r will create the standard B-S stock option model.  Non-zero q (or R) is the Merton model (or Garman-Kohlhagen)
public:
	Option();	// Default constructor
	Option(double, double, double, double, double, double);	// Constructor with inputs
	Option(const Option&);	// Copy constructor
	~Option();	// Destructor

	Option& operator = (const Option&);	// Assignment operator

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

	// Virtual Call Price function
	virtual double Call() const = 0;

	// Virtual Put Price function
	virtual double Put() const = 0;

	// ToString Function
	std::string ToString() const;

	friend std::ostream& operator << (std::ostream&, const Option&);	// Send to ostream

	// Mesh functions to return arrays of results
	virtual boost::tuple<std::vector<double>, std::vector<double>> CallRange() = 0;
	virtual boost::tuple<std::vector<double>, std::vector<double>> PutRange() = 0;
};
#endif // !OPTION_HPP