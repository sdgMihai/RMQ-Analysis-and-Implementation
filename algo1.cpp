#include "algo.h"

int iLog(int n) {
	long long i = 30;
	if (n <= 0)
		return 0;
	while ((n & (1 << i)) == 0) {
		--i;
	}

	return i;
}

void dinamicProcess(std::vector<std::vector<int>>& dinMin, const std::vector<int>& input);

std::vector<int> rmq(const std::vector<int>& input, const std::vector< std::pair<int, int> >& queries) {
	// TODO
	// M[i][j] - index of the minValue in the sub array
	//starting at i having length 2j
	std::vector<int> init(iLog(input.size()) + 1);
	std::vector<std::vector<int>> dinMin(input.size(), init);
	std::vector<int> answer(queries.size());

	dinamicProcess(dinMin, input);  // preprocess input using dinamic prog.

	for (int i = 0; i < queries.size(); ++i) {  // answer queries.
		int indexStart, indexStop;
		indexStart = queries[i].first;
		indexStop = queries[i].second;
		int k = iLog(indexStop - indexStart + 1);

		if (input[dinMin[indexStart][k]] <= input[dinMin[indexStop - (1 << k) + 1][k]])
			answer[i] = input[dinMin[indexStart][k]];  // min e in 1/2 inf.
		else answer[i] = input[dinMin[indexStop - (1 << k) + 1][k]];  // min e in 1/2 sup.
	}
	return answer;
}

void dinamicProcess(std::vector<std::vector<int>>& dinMin, const std::vector<int>& input)
{
	int i, j;
	// for the intervals with length 1
	// initialize M.
	for (i = 0; i < input.size(); i++) {
		dinMin[i][0] = i;
	}

	//compute min from smaller to bigger intervals.
	for (j = 1; 1 << j <= input.size(); ++j) {  // interval size contor.
		for (i = 0; i + (1 << j) - 1 < input.size(); ++i) {  // starting point contor.
			if (input[dinMin[i][j - 1]] < input[dinMin[i + (1 << (j - 1))][j - 1]])
				dinMin[i][j] = dinMin[i][j - 1];
			else
				dinMin[i][j] = dinMin[i + (1 << (j - 1))][j - 1];
		}
	}
}