#include <fstream>
#include<iostream>
#include <vector>
#include <cmath>
#include <sstream>
#include <chrono> 
#include "algo.h"

using namespace std::chrono;

const int NUM_TESTS = 25;
const int MAX_TEST_NAME_SIZE = 32;

int run_test(const char* input_file,const char* output_file) {
	std::ios::sync_with_stdio(false);
	std::ifstream f(input_file);
	std::ifstream g(output_file);

	if (!f.is_open()) {
		std::cout << "Error opening input file! Program is shutting down...";
		return -1;
	}

	if (!f.is_open()) {
		std::cout << "Error opening output file! Program is shutting down...";
		return -2;
	}

	// declare variables
	std::vector<int> input;  // input array
	std::vector<std::pair<int, int>> queries;  // queries array (indexStart, indexStop)
	std::vector<int> min(queries.size());
	int inputSize, queriesSize;

	// citiri
	f >> inputSize >> queriesSize;
	for (int i = 0; i < inputSize; ++i) {  // read input array
		int nr;
		f >> nr;
		input.push_back(nr);
	}
	for (int i = 0; i < queriesSize; ++i) {  // read queries
		int a, b;
		f >> a >> b;
		queries.push_back(std::make_pair(a, b));
	}

	min = rmq(input, queries);  // main logic - rmq

	for (int i = 0; i < queriesSize; ++i) {  // display results
		int localMin;
		g >> localMin;
		if (min[i] != localMin)
			return -3;
	}

	return 0;
}

int main() {
	char inputTest[MAX_TEST_NAME_SIZE],
		outputRef[MAX_TEST_NAME_SIZE];
	std::stringstream ss;

	// Get starting timepoint 
	auto start = high_resolution_clock::now();

	for (int i = 0; i <= NUM_TESTS; ++i) {

		ss.clear();
		ss << "./in/test" << i << ".in";
		ss >> inputTest;
		
		ss.clear();
		ss << "./out/test" << i << ".out";
		ss >> outputRef;

		std::cout << "Running test " << i << "\n";
		std::cout << inputTest << " " << outputRef << '\t';

		if (run_test(inputTest, outputRef)) {
			std::cout << "Failed to run test " << i << "\n";
			return -1;
		}
		else {
			std::cout << "ok\n";
		}
	}
	// Get ending timepoint 
	auto stop = high_resolution_clock::now();
	// Get duration. Substart timepoints to  
	// get durarion. To cast it to proper unit 
	// use duration cast method 
	auto duration = duration_cast<microseconds>(stop - start);

	std::cout << "Time taken by function: "
		<< duration.count() << " microseconds" << '\n';
}