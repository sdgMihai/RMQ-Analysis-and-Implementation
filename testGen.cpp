#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cstdlib>

#include "algo.h"

using namespace std;

#define MAXNUMBER 1000000
const int MAX_TEST_NAME_SIZE = 32;

int main() {
	char inputTest[MAX_TEST_NAME_SIZE],
		outputRef[MAX_TEST_NAME_SIZE];
	srand((unsigned)time(0));
	stringstream ss;
	int cnt = 1;
	
	for (int n = 10; n < MAXNUMBER; n *= 10) {
		for (int j = 10; j < MAXNUMBER; j *= 10) {
			ss.clear();
			ss << "./in/test" << cnt << ".in";
			cnt++;
			ss >> inputTest;

			ofstream f(inputTest);

			f << n << ' ' << j << '\n';
			for (int i = 0; i < n; ++i) {
				f << (rand() % MAXNUMBER) + 1 << ' ';
			}
			f << '\n';
			for (int i = 0; i < j; ++i) {
				int lowerBound = (rand() % n);
				int upperBound = lowerBound 
					+ (rand() % ((n - lowerBound) > 0 ? (n - lowerBound) : 1));
				f << lowerBound << ' ' << upperBound << '\n'; 
			}
		}
	}

	for(int i = 1; i < cnt; ++i) {
		ss.clear();
		ss << "./in/test" << i << ".in";
		ss >> inputTest;
		
		ss.clear();
		ss << "./out/test" << i << ".out";
		ss >> outputRef;

		std::ifstream f(inputTest);
		std::ofstream g(outputRef);

		if (!f.is_open()) {
			std::cout << "Error opening input file! Program is shutting down...";
			return -1;
		}

		if (!g.is_open()) {
			std::cout << "Error opening output file! Program is shutting down...";
			return -2;
		}

		// declare variables
		std::vector<int> input;  // input array
		std::vector< std::pair<int, int> > queries;  // queries array (indexStart, indexStop)
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

		for (int  j = 0; j < min.size(); ++j) {
			g << min[j] << '\n';
		}
	}

}