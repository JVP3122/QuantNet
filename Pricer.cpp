// Global functions to calculate pdf, cdf of normal distributions
// and separately put and call option prices

#include"Pricer.hpp"
#include<cmath>
#include<boost\math\distributions\normal.hpp>


// Simple form of CDF of Standard Normal
double N(double x) {
	using namespace boost::math;
	normal_distribution<> norm_dist(0.0, 1.0);
	return cdf(norm_dist, x);
}

// First derivative of CDF of Standard Normal
double n(double x) {
	using namespace boost::math;
	normal_distribution<> norm_dist(0.0, 1.0);
	return pdf(norm_dist, x);
}

// Call Option
double CallOption(const double& T, const double& K, const double& sigma, const double& r, const double& q, const double& S) {
	double b = r - q;	// Declare cost of carry which should incorporate all four possible models
	double d1, d2;

	// Calculate d1 & d2
	d1 = (log(S / K) + (b + pow(sigma, 2) / 2) * T) / (sigma * sqrt(T));
	d2 = d1 - sigma * sqrt(T);

	// Return final value
	return S * exp((b - r) * T) * N(d1) -
		K * exp(-r * T) * N(d2);
}

// Put Option
double PutOption(const double& T, const double& K, const double& sigma, const double& r, const double& q, const double& S) {
	double b = r - q;	// Declare cost of carry which should incorporate all four possible models
	double d1, d2;

	// Calculate d1 & d2
	double temp1 = log(S / K);
	double temp2 = b + pow(sigma, 2) / 2;
	d1 = (log(S / K) + (b + pow(sigma, 2) / 2) * T) / (sigma * sqrt(T));
	d2 = d1 - sigma * sqrt(T);

	// Return final value
	return K * exp(-r * T) * N(-d2) -
		S * exp((b - r) * T) * N(-d1);
}

// Perpetual American Call
double PerpetualAmericanCall(const double& K, const double& sigma, const double& r, const double& q, const double& S) {
	double b = r - q;	// Declare cost of carry which should incorporate all four possible models
	double sig = pow(sigma, 2);	// Define a variable for sigma squared to make calculation of y1 cleaner
	double y1 = 0.5 - b / sig + sqrt(pow(b / sig - 0.5, 2) + 2 * r / sig);	// Calculate y1

	return K / (y1 - 1) * pow(((y1 - 1) / y1) * (S / K), y1);
}

// Perpetual American Put
double PerpetualAmericanPut(const double& K, const double& sigma, const double& r, const double& q, const double& S) {
	double b = r - q;	// Declare cost of carry which should incorporate all four possible models
	double sig = pow(sigma, 2);	// Define a variable for sigma squared to make calculation of y2 cleaner
	double y2 = 0.5 - b / sig - sqrt(pow(b / sig - 0.5, 2) + 2 * r / sig);	// Calculate y2

	return K / (1 - y2) * pow(((y2 - 1) / y2) * (S / K), y2);
}
