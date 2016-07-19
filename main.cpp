// This file contains the code used for demonstrating the option class functionalities

#include<iostream>
#include<vector>
#include"European.hpp"
#include"PerpetualAmerican.hpp"

int main() {
	/*************************European Options********************************/
	// Instantiate European Option for each batch and define the parameters
	European Option1(0.25, 65, 0.3, 0.08, 0, 60);
	European Option2(1.0, 100, 0.2, 0.0, 0, 100);
	European Option3(1.0, 10, 0.5, 0.12, 0, 5);
	European Option4(30, 100, 0.3, 0.08, 0, 100);

	// Print results demonstrating correct formula implementation
	std::cout << "Batch 1: " << Option1 << ".  C: " << Option1.Call() << ", P: " << Option1.Put() << std::endl;
	std::cout << "Batch 2: " << Option2 << ".  C: " << Option2.Call() << ", P: " << Option2.Put() << std::endl;
	std::cout << "Batch 3: " << Option3 << ".  C: " << Option3.Call() << ", P: " << Option3.Put() << std::endl;
	std::cout << "Batch 4: " << Option4 << ".  C: " << Option4.Call() << ", P: " << Option4.Put() << std::endl;

	std::cout << std::endl;

	// Demonstrate correct implementation of Put-Call Parity
	std::cout << "Batch 1: C (Exact): " << Option1.Call() << ", P (Put-Call): " << Option1.PutParity() << ".  P (Exact): " << Option1.Put() << ", C (Put-Call): " << Option1.CallParity() << std::endl;
	std::cout << "Batch 2: C (Exact): " << Option2.Call() << ", P (Put-Call): " << Option2.PutParity() << ".  P (Exact): " << Option2.Put() << ", C (Put-Call): " << Option2.CallParity() << std::endl;
	std::cout << "Batch 3: C (Exact): " << Option3.Call() << ", P (Put-Call): " << Option3.PutParity() << ".  P (Exact): " << Option3.Put() << ", C (Put-Call): " << Option3.CallParity() << std::endl;
	std::cout << "Batch 4: C (Exact): " << Option4.Call() << ", P (Put-Call): " << Option4.PutParity() << ".  P (Exact): " << Option4.Put() << ", C (Put-Call): " << Option4.CallParity() << std::endl;

	std::cout << std::endl << std::endl;

	// Demonstrate a range of Call values - with user input
	std::cout << "Batch 1 Call Range - S" << std::endl;
	Option1.CallRange();

	std::cout << std::endl << std::endl;

	// Demonstrate a range of Put values - with user input
	std::cout << "Batch 1 Put Range - S" << std::endl;
	Option1.PutRange();

	std::cout << std::endl;

	// Demonstrate a range of Call values - with user input
	std::cout << "Batch 1 Call Range - T" << std::endl;
	Option1.CallRange();

	std::cout << std::endl << std::endl;

	// Demonstrate a range of Put values - with user input
	std::cout << "Batch 1 Put Range - T" << std::endl;
	Option1.PutRange();

	std::cout << std::endl;

	// Demonstrate a range of Call values - with user input
	std::cout << "Batch 1 Call Range - sigma" << std::endl;
	Option1.CallRange();

	std::cout << std::endl << std::endl;

	// Demonstrate a range of Put values - with user input
	std::cout << "Batch 1 Put Range - sigma" << std::endl;
	Option1.PutRange();

	std::cout << std::endl;

	/**************************Basic Greeks Test****************************************/
	// Instantiate European option with specified parameters and test exact delta formula implementation
	European Option5(0.5, 100, 0.36, 0.1, 0.1, 105);
	std::cout << "Testing exact call and put delta formula implementation" << std::endl << "Call Delta: " << Option5.CallDelta() << ", Put Delta: " << Option5.PutDelta() << std::endl << std::endl;
	
	// Call Delta Range usage - with user input
	std::cout << "Testing call delta range function implementation" << std::endl;
	Option5.CallDeltaRange();

	std::cout << std::endl << std::endl;

	// Put Theta Range usage - with user input
	std::cout << "Testing put theta range function implementation" << std::endl;
	Option5.PutThetaRange();

	std::cout << std::endl << std::endl;
	
	/**************************Basic Divided Differences Test****************************************/
	// Instantiate a European Option using the Copy Constructor
	European Option6(Option2);
	Option6.r(0.08);	// Update the risk-free rate to a non-zero value - This will match the default European constructor values

	// Choose the mesh and create it
	double init = 0.0001, fin = 0.1, h = 0.005;
	std::vector<double> my_mesh = mesharray(init, fin, h);	// First value is input flag, second is vector of parameter values
	
	// Loop through (using reverse iterator) to output exact values vs divided differences values
	std::cout << "Testing put rho exact vs divided differences results" << std::endl;
	for (std::vector<double>::reverse_iterator iter = my_mesh.rbegin(); iter != my_mesh.rend(); iter++) {
		std::cout << "Exact Put Rho = " << Option6.PutRho() << ", Divided Differences Put Rho (h = " << *iter << ") = " << Option6.DividedPutRho(*iter) << std::endl;
	}

	std::cout << std::endl;

	// Instantiate a default European Option
	European Option7;

	// Choose the mesh and create it
	init = 0.001, fin = 0.1, h = 0.005;
	std::vector<double> my_mesh_2 = mesharray(init, fin, h);	// First value is input flag, second is vector of parameter values

	// Loop through (using reverse iterator) to output exact values vs divided differences values
	std::cout << "Testing call (and put) Vega exact vs divided differences results" << std::endl;
	for (std::vector<double>::reverse_iterator iter = my_mesh_2.rbegin(); iter != my_mesh_2.rend(); iter++) {
		std::cout << "Exact Call Vega = " << Option7.CallVega() << ", Exact Put Vega = " << Option7.PutVega() << ", Divided Differences Call Vega (h = " << *iter << ") = " << Option7.DividedCallVega(*iter) << std::endl;
	}

	/*************************Perpetual American Options********************************/
	// Instantiate default Perpetual American Option
	PerpetualAmerican Option8;

	// Print out the call and put values to show that the formulae are correctly programmed
	std::cout << Option8 << ", C: " << Option8.Call() << std::endl;
	std::cout << Option8 << ", P: " << Option8.Put() << std::endl << std::endl;

	// Print ranges for call and put (user defines range for S)
	std::cout << "Perpetual American Call range" << std::endl;
	Option8.CallRange();
	std::cout << std::endl << "Perpetual American Put range" << std::endl;
	Option8.PutRange();


	return 0;
}