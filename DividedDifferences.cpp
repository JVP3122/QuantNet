#include"DividedDifferences.hpp"

double Divided_Delta_Call(const double& T, const double& K, const double& sigma, const double& r, const double& q, const double& S, const double& h){
	double Call_Plus = CallOption(T, K, sigma, r, q, S + h);
	double Call_Minus = CallOption(T, K, sigma, r, q, S - h);
	return (Call_Plus - Call_Minus) / (2 * h);
}

double Divided_Delta_Put(const double& T, const double& K, const double& sigma, const double& r, const double& q, const double& S, const double& h){
	double Put_Plus = PutOption(T, K, sigma, r, q, S + h);
	double Put_Minus = PutOption(T, K, sigma, r, q, S - h);
	return (Put_Plus - Put_Minus) / (2 * h);
}

double Divided_Gamma_Call(const double& T, const double& K, const double& sigma, const double& r, const double& q, const double& S, const double& h){
	double Call_Plus = CallOption(T, K, sigma, r, q, S + h);
	double Call_Minus = CallOption(T, K, sigma, r, q, S - h);
	return (Call_Plus - 2 * CallOption(T, K, sigma, r, q, S) + Call_Minus) / (h * h);
}

double Divided_Gamma_Put(const double& T, const double& K, const double& sigma, const double& r, const double& q, const double& S, const double& h){
	double Put_Plus = PutOption(T, K, sigma, r, q, S + h);
	double Put_Minus = PutOption(T, K, sigma, r, q, S - h);
	return (Put_Plus - 2 * PutOption(T, K, sigma, r, q, S) + Put_Minus) / (h * h);
}

double Divided_Theta_Call(const double& T, const double& K, const double& sigma, const double& r, const double& q, const double& S, const double& h){
	double Call_Plus = CallOption(T + h, K, sigma, r, q, S);
	double Call_Minus = CallOption(T - h, K, sigma, r, q, S);
	return (Call_Plus - Call_Minus) / (2 * h);
}

double Divided_Theta_Put(const double& T, const double& K, const double& sigma, const double& r, const double& q, const double& S, const double& h){
	double Put_Plus = PutOption(T + h, K, sigma, r, q, S);
	double Put_Minus = PutOption(T - h, K, sigma, r, q, S);
	return (Put_Plus - Put_Minus) / (2 * h);
}

double Divided_Vega_Call(const double& T, const double& K, const double& sigma, const double& r, const double& q, const double& S, const double& h){
	double Call_Plus = CallOption(T, K, sigma + h, r, q, S);
	double Call_Minus = CallOption(T, K, sigma - h, r, q, S);
	return (Call_Plus - Call_Minus) / (2 * h);
}

double Divided_Vega_Put(const double& T, const double& K, const double& sigma, const double& r, const double& q, const double& S, const double& h){
	double Put_Plus = PutOption(T, K, sigma + h, r, q, S);
	double Put_Minus = PutOption(T, K, sigma - h, r, q, S);
	return (Put_Plus - Put_Minus) / (2 * h);
}

double Divided_Rho_Call(const double& T, const double& K, const double& sigma, const double& r, const double& q, const double& S, const double& h){
	double Call_Plus = CallOption(T, K, sigma, r + h, q, S);
	double Call_Minus = CallOption(T, K, sigma, r - h, q, S);
	return (Call_Plus - Call_Minus) / (2 * h);
}

double Divided_Rho_Put(const double& T, const double& K, const double& sigma, const double& r, const double& q, const double& S, const double& h){
	double Put_Plus = PutOption(T, K, sigma, r + h, q, S);
	double Put_Minus = PutOption(T, K, sigma, r - h, q, S);
	return (Put_Plus - Put_Minus) / (2 * h);
}