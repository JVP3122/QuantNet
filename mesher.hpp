// Global function that creates a mesh to be used for a range of option prices

#ifndef MESHER_HPP
#define MESHER_HPP

#include<vector>
#include<boost\tuple\tuple.hpp>

// Generic mesh creation
template<typename T>
std::vector<T> mesharray(T& init, T& fin, T& h);

// Mesh creation for option class ranges
template<typename T>
boost::tuple<int, std::vector<T>> mesharray();

// Mesh creation for Perpetual American option class ranges
template<typename T>
boost::tuple<int, std::vector<T>> mesharray(const bool& PerpAmerFlag);

#ifndef MESHER_CPP
#include"mesher.cpp"
#endif // !MESHER_CPP

#endif // !MESHER_HPP