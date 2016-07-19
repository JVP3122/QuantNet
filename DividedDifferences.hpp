#ifndef DIVIDEDDIFFERENCES_HPP
#define DIVIDEDDIFFERENCES_HPP

#include"Pricer.hpp"

double Divided_Delta_Call(const double& T, const double& K, const double& sigma, const double& r, const double& q, const double& S, const double& h);

double Divided_Delta_Put(const double& T, const double& K, const double& sigma, const double& r, const double& q, const double& S, const double& h);

double Divided_Gamma_Call(const double& T, const double& K, const double& sigma, const double& r, const double& q, const double& S, const double& h);

double Divided_Gamma_Put(const double& T, const double& K, const double& sigma, const double& r, const double& q, const double& S, const double& h);

double Divided_Theta_Call(const double& T, const double& K, const double& sigma, const double& r, const double& q, const double& S, const double& h);

double Divided_Theta_Put(const double& T, const double& K, const double& sigma, const double& r, const double& q, const double& S, const double& h);

double Divided_Vega_Call(const double& T, const double& K, const double& sigma, const double& r, const double& q, const double& S, const double& h);

double Divided_Vega_Put(const double& T, const double& K, const double& sigma, const double& r, const double& q, const double& S, const double& h);

double Divided_Rho_Call(const double& T, const double& K, const double& sigma, const double& r, const double& q, const double& S, const double& h);

double Divided_Rho_Put(const double& T, const double& K, const double& sigma, const double& r, const double& q, const double& S, const double& h);

#endif // !DIVIDEDDIFFERENCES_HPP