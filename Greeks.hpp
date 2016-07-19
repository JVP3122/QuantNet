// This file contains the function prototypes for the five main Greeks for Calls and Puts

#ifndef GREEKS_HPP
#define GREEKS_HPP

double Delta_Call(const double& T, const double& K, const double& sigma, const double& r, const double& q, const double& S);

double Delta_Put(const double& T, const double& K, const double& sigma, const double& r, const double& q, const double& S);

double Gamma_Call(const double& T, const double& K, const double& sigma, const double& r, const double& q, const double& S);

double Gamma_Put(const double& T, const double& K, const double& sigma, const double& r, const double& q, const double& S);

double Vega_Call(const double& T, const double& K, const double& sigma, const double& r, const double& q, const double& S);

double Vega_Put(const double& T, const double& K, const double& sigma, const double& r, const double& q, const double& S);

double Theta_Call(const double& T, const double& K, const double& sigma, const double& r, const double& q, const double& S);

double Theta_Put(const double& T, const double& K, const double& sigma, const double& r, const double& q, const double& S);

double Rho_Call(const double& T, const double& K, const double& sigma, const double& r, const double& q, const double& S);

double Rho_Put(const double& T, const double& K, const double& sigma, const double& r, const double& q, const double& S);

#endif // !GREEKS_HPP