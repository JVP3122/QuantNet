#ifndef MESHER_CPP
#define MESHER_CPP

// Global function that creates a mesh to be used for a range of option prices
// User input for mesh creation is included in this file as well

#include<iostream>
#include"mesher.hpp"

// Generic mesh creation tool - Not using const inputs in case the inputs aren't compatible values
template<typename T>
std::vector<T> mesharray(T& init, T& fin, T& h) {
	while (fin < init || h >(fin - init)) {
		std::cout << "Error: Either the ending value was less than the beginning value or the step size is larger than the interval, please enter the values again." << std::endl;
		std::cout << "init: ";
		std::cin >> init;
		std::cout << "fin: ";
		std::cin >> fin;
		std::cout << "h: ";
		std::cin >> h;
	}
	// Instantiate the return vector
	std::vector<T> temp_vec;

	// Instantiate the "iterator" for the mesh
	double temp_iter = init;

	// While loop to add elements to the vector for each step
	while (temp_iter < fin) {
		temp_vec.push_back(temp_iter);
		temp_iter += h;
	}

	// Add the final value to the back of the vector if the start, end, and step-size don't match up
	// For example, if init = 0, fin = 1, h = 2/3 then without this code the vector would only be (0,2/3)
	// and would not constitute the entire space.
	if (temp_vec.back() != fin)
		temp_vec.push_back(fin);

	return temp_vec;
}

// Mesh creation specifically designed for option ranges
template<typename T>
boost::tuple<int, std::vector<T>> mesharray() {
	// Create two "flags" to get user input
	int input_val = -1, yes_no = -1;

	// Create mesh-specific variables
	double init, fin, h;

	// Get user input to choose the parameter over which the user would like a range of values
	while (input_val < 0 || input_val > 6) {
		std::cout << "Which parameter would you like to vary? (1:T, 2:K, 3:sigma, 4: r, 5: q, 6: S) ";
		std::cin >> input_val;
		while (std::cin.fail())
		{
			std::cout << "Error: an incorrect type was entered, please try again." << std::endl;
			std::cin.clear();
			std::cin.ignore(256, '\n');
			std::cin >> input_val;
		}
		if (input_val < 0 || input_val > 6)
			std::cout << "You have entered an invalid choice, please try again." << std::endl;
	}

	// Ask the user if the default values are sufficient and display default values
	std::cout << "Would you like to use the default values: ";
	switch (input_val) {
	// T
	case 1:
		init = 0.05; fin = 1.5; h = 0.05;
		std::cout << "min = 0.05, max = 1.5, h = 0.05?";
		break;
	// K
	case 2:
		init = 10; fin = 100; h = 5;
		std::cout << "min = 10, max = 100, h = 5?";
		break;
	// sigma
	case 3:
		init = 0; fin = 0.35; h = 0.05;
		std::cout << "min = 0, max = 0.35, h = 0.05?";
		break;
	// r
	case 4:
		init = 0; fin = 0.12; h = 0.01;
		std::cout << "min = 0, max = 0.12, h = 0.01?";
		break;
	// q - dividend yield
	case 5:
		init = 0; fin = 0.12; h = 0.01;
		std::cout << "min = 0, max = 0.12, h = 0.01?";
		break;
	// S
	case 6:
		init = 10; fin = 100; h = 5;
		std::cout << "min = 10, max = 100, h = 5?";
		break;
	}
	while (yes_no < 0 || yes_no > 2) {
		std::cout << " Yes (1), No (2) ";
		std::cin >> yes_no;
		while (std::cin.fail())
		{
			std::cout << "Error: an incorrect type was entered, please try again." << std::endl;
			std::cin.clear();
			std::cin.ignore(256, '\n');
			std::cin >> yes_no;
		}
		if (yes_no < 0 || yes_no > 2)
			std::cout << "You have entered an invalid choice, please try again." << std::endl;
	}

	// Only if the user input is "No" will the user be prompted to enter in his/her own values
	switch (yes_no) {
	case 2:
		init = -1; fin = -1; h = -1;	// Negative initial values set to allow the "while" loop to run when invalid choices are entered
		while (init < 0) {	// In the case of option parameters the initial mesh value should always be non-negative
			std::cout << "Choose a min value: ";
			std::cin >> init;
			if (init < 0 || (init == 0 && input_val == 1))	// Invalid entry if negative init value entered
				std::cout << "Invalid selection, please choose another number." << std::endl;
		}
		while ((fin < 0) || (fin < init)) {	// Should also have non-negative final mesh value and the final value should be larger than the initial value
			std::cout << "Choose a max value: ";
			std::cin >> fin;
			if ((fin < 0) || (fin < init))	// Invalid entry check
				std::cout << "Invalid selection, please choose another number." << std::endl;
		}
		while ((h < 0) || (h >(fin - init))) {	// Step size should also be positive and should be smaller than the size of the interval
			std::cout << "Choose a step size value: ";
			std::cin >> h;
			if ((h < 0) || (h >(fin - init)))	//Invalid entry check
				std::cout << "Invalid selection, please choose another number." << std::endl;
		}
	}

	// Instantiate the return vector
	std::vector<T> temp_vec;

	// Instantiate the "iterator" for the mesh
	double temp_iter = init;

	// While loop to add elements to the vector for each step
	while (temp_iter < fin) {
		temp_vec.push_back(temp_iter);
		temp_iter += h;
	}

	// Add the final value to the back of the vector if the start, end, and step-size don't match up
	// For example, if init = 0, fin = 1, h = 2/3 then without this code the vector would only be (0,2/3)
	// and would not constitute the entire space.
	if (temp_vec.back() != fin)
		temp_vec.push_back(fin);

	// Create tuple to return the vector and the flag telling which parameter is being varied
	boost::tuple<int, std::vector<T>> return_tuple(input_val, temp_vec);
	return return_tuple;
}

// Mesh creation specifically designed for Perpetual American options - Where the parameter T cannot be varied
template<typename T>
boost::tuple<int, std::vector<T>> mesharray(const bool& PerpAmerFlag) {
	while (PerpAmerFlag) {
		// Create two "flags" to get user input
		int input_val = -1, yes_no = -1;

		// Create mesh-specific variables
		double init, fin, h;

		// Get user input to choose the parameter over which the user would like a range of values
		while (input_val < 0 || input_val > 5) {
			std::cout << "Which parameter would you like to vary? (1:K, 2:sigma, 3: r, 4: q, 5: S) ";
			std::cin >> input_val;
			while (std::cin.fail())
			{
				std::cout << "Error: an incorrect type was entered, please try again." << std::endl;
				std::cin.clear();
				std::cin.ignore(256, '\n');
				std::cin >> input_val;
			}
			if (input_val < 0 || input_val > 5)
				std::cout << "You have entered an invalid choice, please try again." << std::endl;
		}

		// Ask the user if the default values are sufficient and display default values
		std::cout << "Would you like to use the default values: ";
		switch (input_val) {
		case 1:
			init = 10; fin = 100; h = 5;
			std::cout << "min = 10, max = 100, h = 5?";
			break;
			// sigma
		case 2:
			init = 0; fin = 0.35; h = 0.05;
			std::cout << "min = 0, max = 0.35, h = 0.05?";
			break;
			// r
		case 3:
			init = 0; fin = 0.12; h = 0.01;
			std::cout << "min = 0, max = 0.12, h = 0.01?";
			break;
			// q - dividend yield
		case 4:
			init = 0; fin = 0.12; h = 0.01;
			std::cout << "min = 0, max = 0.12, h = 0.01?";
			break;
			// S
		case 5:
			init = 10; fin = 100; h = 5;
			std::cout << "min = 10, max = 100, h = 5?";
			break;
		}
		while (yes_no < 0 || yes_no > 2) {
			std::cout << " Yes (1), No (2) ";
			std::cin >> yes_no;
			while (std::cin.fail())
			{
				std::cout << "Error: an incorrect type was entered, please try again." << std::endl;
				std::cin.clear();
				std::cin.ignore(256, '\n');
				std::cin >> yes_no;
			}
			if (yes_no < 0 || yes_no > 2)
				std::cout << "You have entered an invalid choice, please try again." << std::endl;
		}

		// Only if the user input is "No" will the user be prompted to enter in his/her own values
		switch (yes_no) {
		case 2:
			init = -1; fin = -1; h = -1;	// Negative initial values set to allow the "while" loop to run when invalid choices are entered
			while (init < 0) {	// In the case of option parameters the initial mesh value should always be non-negative
				std::cout << "Choose a min value: ";
				std::cin >> init;
				if (init < 0 || (init == 0 && input_val == 1))	// Invalid entry if negative init value entered
					std::cout << "Invalid selection, please choose another number." << std::endl;
			}
			while ((fin < 0) || (fin < init)) {	// Should also have non-negative final mesh value and the final value should be larger than the initial value
				std::cout << "Choose a max value: ";
				std::cin >> fin;
				if ((fin < 0) || (fin < init))	// Invalid entry check
					std::cout << "Invalid selection, please choose another number." << std::endl;
			}
			while ((h < 0) || (h >(fin - init))) {	// Step size should also be positive and should be smaller than the size of the interval
				std::cout << "Choose a step size value: ";
				std::cin >> h;
				if ((h < 0) || (h >(fin - init)))	//Invalid entry check
					std::cout << "Invalid selection, please choose another number." << std::endl;
			}
		}

		// Instantiate the return vector
		std::vector<T> temp_vec;

		// Instantiate the "iterator" for the mesh
		double temp_iter = init;

		// While loop to add elements to the vector for each step
		while (temp_iter < fin) {
			temp_vec.push_back(temp_iter);
			temp_iter += h;
		}

		// Add the final value to the back of the vector if the start, end, and step-size don't match up
		// For example, if init = 0, fin = 1, h = 2/3 then without this code the vector would only be (0,2/3)
		// and would not constitute the entire space.
		if (temp_vec.back() != fin)
			temp_vec.push_back(fin);

		// Create tuple to return the vector and the flag telling which parameter is being varied
		boost::tuple<int, std::vector<T>> return_tuple(input_val, temp_vec);
		return return_tuple;
	}
}

#endif // !MESHER_CPP
