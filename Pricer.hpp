// Global functions to calculate pdf, cdf of normal distributions
// and separately put and call option prices

#ifndef PRICER_HPP
#define PRICER_HPP

// CDF
double N(double x);

// PDF
double n(double x);

// Call Option
double CallOption(const double& T, const double& K, const double& sigma, const double& r, const double& q, const double& S);

// Put Option
double PutOption(const double& T, const double& K, const double& sigma, const double& r, const double& q, const double& S);

// Perpetual American Call
double PerpetualAmericanCall(const double& K, const double& sigma, const double& r, const double& q, const double& S);

// Perpetual American Put
double PerpetualAmericanPut(const double& K, const double& sigma, const double& r, const double& q, const double& S);

#endif // !PRICER_HPP