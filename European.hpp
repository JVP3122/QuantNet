// This file contains function prototypes for the European Option derived class

#ifndef EUROPEAN_HPP
#define EUROPEAN_HPP

#include"Option.hpp"
#include<vector>

class European : public  Option {
private:
	bool early_exercise;	// Flag determining if early exercise is allowed (which determines if the option is European)
public:

	European();	// Default constructor
	European(double t, double k, double sig, double rate, double q, double s);	// Constructor with inputs
	European(const European&);	// Copy constructor
	~European();	// Destructor

	European& operator = (const European&);	// Assignment operator

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

	// Call Price function
	double Call() const;

	// Put Price function
	double Put() const;

	// Put-Call Parity Calculating Call Price
	double CallParity() const;

	// Put-Call Parity Calculating Put Price
	double PutParity() const;

	// ToString Function
	std::string ToString() const;

	friend std::ostream& operator << (std::ostream&, const European&);	// Send to ostream

	// Mesh functions to return arrays of results
	boost::tuple<std::vector<double>, std::vector<double>> CallRange();
	boost::tuple<std::vector<double>, std::vector<double>> PutRange();
	boost::tuple<std::vector<double>, std::vector<double>> CallDeltaRange();
	boost::tuple<std::vector<double>, std::vector<double>> PutDeltaRange();
	boost::tuple<std::vector<double>, std::vector<double>> CallGammaRange();
	boost::tuple<std::vector<double>, std::vector<double>> PutGammaRange();
	boost::tuple<std::vector<double>, std::vector<double>> CallVegaRange();
	boost::tuple<std::vector<double>, std::vector<double>> PutVegaRange();
	boost::tuple<std::vector<double>, std::vector<double>> CallThetaRange();
	boost::tuple<std::vector<double>, std::vector<double>> PutThetaRange();
	boost::tuple<std::vector<double>, std::vector<double>> CallRhoRange();
	boost::tuple<std::vector<double>, std::vector<double>> PutRhoRange();


	// Greeks
	double CallDelta() const;
	double PutDelta() const;
	double CallGamma() const;
	double PutGamma() const;
	double CallVega() const;
	double PutVega() const;
	double CallTheta() const;
	double PutTheta() const;
	double CallRho() const;
	double PutRho() const;

	// Divided Differences Formulae
	double DividedCallDelta(const double& h) const;
	double DividedPutDelta(const double& h) const;
	double DividedCallGamma(const double& h) const;
	double DividedPutGamma(const double& h) const;
	double DividedCallTheta(const double& h) const;
	double DividedPutTheta(const double& h) const;
	double DividedCallVega(const double& h) const;
	double DividedPutVega(const double& h) const;
	double DividedCallRho(const double& h) const;
	double DividedPutRho(const double& h) const;

};

#endif // !EUROPEAN_HPP