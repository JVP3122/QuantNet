// This file contains the function definitions for calculating the five main Greeks for Calls and Puts

#include"Pricer.hpp"
#include"Greeks.hpp"
#include<cmath>

double Delta_Call(const double& T, const double& K, const double& sigma, const double& r, const double& q, const double& S) {
	double b = r - q;	// Declare cost of carry which should incorporate all four possible models
	double d1;

	// Calculate d1
	d1 = (log(S / K) + (b + pow(sigma, 2) / 2) * T) / (sigma * sqrt(T));
	
	return exp((b - r) * T) * N(d1);
}

double Delta_Put(const double& T, const double& K, const double& sigma, const double& r, const double& q, const double& S){
	double b = r - q;	// Declare cost of carry which should incorporate all four possible models
	double d1;

	// Calculate d1
	d1 = (log(S / K) + (b + pow(sigma, 2) / 2) * T) / (sigma * sqrt(T));

	return exp((b - r) * T) * (N(d1) - 1);
}

double Gamma_Call(const double& T, const double& K, const double& sigma, const double& r, const double& q, const double& S){
	double b = r - q;	// Declare cost of carry which should incorporate all four possible models
	double d1;

	// Calculate d1
	d1 = (log(S / K) + (b + pow(sigma, 2) / 2) * T) / (sigma * sqrt(T));

	return (n(d1) * exp((b - r) * T)) / (S * sigma * sqrt(T));
}

double Gamma_Put(const double& T, const double& K, const double& sigma, const double& r, const double& q, const double& S){
	return Gamma_Call(T, K, sigma, r, q, S);
}

double Vega_Call(const double& T, const double& K, const double& sigma, const double& r, const double& q, const double& S){
	double b = r - q;	// Declare cost of carry which should incorporate all four possible models
	double d1;

	// Calculate d1
	d1 = (log(S / K) + (b + pow(sigma, 2) / 2) * T) / (sigma * sqrt(T));

	return S * sqrt(T) * exp((b - r) * T) * n(d1);
}

double Vega_Put(const double& T, const double& K, const double& sigma, const double& r, const double& q, const double& S){
	return Vega_Call(T, K, sigma, r, q, S);
}

double Theta_Call(const double& T, const double& K, const double& sigma, const double& r, const double& q, const double& S){
	double b = r - q;	// Declare cost of carry which should incorporate all four possible models
	double d1, d2;

	// Calculate d1 & d2
	d1 = (log(S / K) + (b + pow(sigma, 2) / 2) * T) / (sigma * sqrt(T));
	d2 = d1 - sigma * sqrt(T);

	double theta_term_1, theta_term_2, theta_term_3;
	theta_term_1 = -(S * sigma * exp((b - r) * T) * n(d1)) / (2 * sqrt(T));
	theta_term_2 = -(b - r) * S * exp((b - r) * T) * N(d1);
	theta_term_3 = -r * K * exp(-r * T) * N(d2);

	return theta_term_1 + theta_term_2 + theta_term_3;
}

double Theta_Put(const double& T, const double& K, const double& sigma, const double& r, const double& q, const double& S){
	double b = r - q;	// Declare cost of carry which should incorporate all four possible models
	double d1, d2;

	// Calculate d1 & d2
	d1 = (log(S / K) + (b + pow(sigma, 2) / 2) * T) / (sigma * sqrt(T));
	d2 = d1 - sigma * sqrt(T);

	double theta_term_1, theta_term_2, theta_term_3;
	theta_term_1 = -(S * sigma * exp((b - r) * T) * n(-d1)) / (2 * sqrt(T));
	theta_term_2 = (b - r) * S * exp((b - r) * T) * N(-d1);
	theta_term_3 = r * K * exp(-r * T) * N(-d2);

	return theta_term_1 + theta_term_2 + theta_term_3;
}

double Rho_Call(const double& T, const double& K, const double& sigma, const double& r, const double& q, const double& S){
	double b = r - q;	// Declare cost of carry which should incorporate all four possible models
	double d2;

	// Calculate d2
	d2 = (log(S / K) + (b - pow(sigma, 2) / 2) * T) / (sigma * sqrt(T));

	return K * T * exp(-r * T) * N(d2);
}

double Rho_Put(const double& T, const double& K, const double& sigma, const double& r, const double& q, const double& S){
	double b = r - q;	// Declare cost of carry which should incorporate all four possible models
	double d2;

	// Calculate d2
	d2 = (log(S / K) + (b - pow(sigma, 2) / 2) * T) / (sigma * sqrt(T));

	return -K * T * exp(-r * T) * N(-d2);
}