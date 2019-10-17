#include "algo.h"

/*
* For a given input n, return x, as 2 ^ x <= n.
* @param n argument
* @return x, as 2 ^ x <= n
*/
int iLog(int n) {
	long long i = 30;
	if (n <= 0)
		return 0;
	while ((n & (1 << i)) == 0) {
		--i;
	}
	
	return i;
}

class Data {
public:
	std::vector<int>& sTree;
	std::vector<int>& answer;
	const std::vector<int>& input;
	int firstQueryIndex;
	int secQueryIndex;

	Data(std::vector<int>& sTree,
		std::vector<int>& answer,
		const std::vector<int>& input) : sTree(sTree), answer(answer), input(input) {}

	void getQuery(int a, int b) {
		firstQueryIndex = a;
		secQueryIndex = b;
	}

	int getFirstQueryIndex() {
		return firstQueryIndex;
	}

	int getSecQueryIndex() {
		return secQueryIndex;
	}
};

void getSegmentTree(int node,
	int startIndex,
	int stopIndex,
	Data& data);

int query(int node,
	int startIndex,
	int stopIndex,
	Data& data);

void segTree(const std::vector<int>& input,
	const std::vector< std::pair<int, int> >& queries,
	std::vector<int>& answer) {
	std::vector<int> sTree((1 << (iLog(input.size()) + 2)) - 1);
	// std::vector<int> answer(queries.size());
	Data data(sTree, answer, input);

	getSegmentTree(1, 0, input.size() - 1, data);
	for (int i = 0; i < queries.size(); ++i) {
		data.getQuery(queries[i].first, queries[i].second);
		answer[i] = input[query(1, 0, input.size() - 1, data)];
	}
}

/*
* compute the minimum value position in the interval assigned to node i
* @param node index in M, used to set sons value and arrange them similar to heap order
* @param startIndex the interval start index
* @param stopIndex the interval stop index
* @param M M[i] holds the minimum value position in the interval assigned to node i
* @param preprocessed index
*/
void getSegmentTree(int node,
	int startIndex,
	int stopIndex,
	Data& data)
{
	if (startIndex == stopIndex)
		data.sTree[node] = startIndex;
	else
	{
		//compute the values in the left and right subtrees
		getSegmentTree(2 * node, startIndex, (startIndex + stopIndex) / 2, data);
		getSegmentTree(2 * node + 1, (startIndex + stopIndex) / 2 + 1, stopIndex, data);
		//search for the minimum value in the first and
		//second half of the interval
		if (data.input[data.sTree[2 * node]] <= data.input[data.sTree[2 * node + 1]])
			data.sTree[node] = data.sTree[2 * node];
		else
			data.sTree[node] = data.sTree[2 * node + 1];
	}
}

int query(int node,
	int startIndex,
	int stopIndex,
	Data& data)
{
	int p1, p2;

	//if the current interval doesn't intersect
	//the query interval return -1
	if (data.getFirstQueryIndex() > stopIndex || data.getSecQueryIndex() < startIndex)
		return -1;

	//if the current interval is included in
	//the query interval return M[node]
	if (startIndex >= data.getFirstQueryIndex() && stopIndex <= data.getSecQueryIndex())
		return data.sTree[node];

	//compute the minimum position in the
	//left and right part of the interval
	p1 = query(2 * node, startIndex, (startIndex + stopIndex) / 2, data);
	p2 = query(2 * node + 1, (startIndex + stopIndex) / 2 + 1, stopIndex, data);

	//return the position where the overall
	//minimum is
	if (p1 == -1)
		return p2;
	if (p2 == -1)
		return p1;
	if (data.input[p1] <= data.input[p2])
		return p1;
	return p2;
}

void dinamicProcess(std::vector<std::vector<int>>& dinMin, const std::vector<int>& input);

void sparseTable(const std::vector<int>& input, 
	const std::vector< std::pair<int, int> >& queries,
	std::vector<int>& answer) {
	// TODO
	// M[i][j] - index of the minValue in the sub array
	//starting at i having length 2j
	std::vector<int> init(iLog(input.size()) + 1);
	std::vector<std::vector<int>> dinMin(input.size(), init);
	//std::vector<int> answer(queries.size());

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
}

void dinamicProcess(std::vector<std::vector<int>>& dinMin,const std::vector<int>& input)
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

std::vector<int> rmq(const std::vector<int>& input, const std::vector< std::pair<int, int> >& queries) {
	std::vector<int> answer(queries.size());
	if (queries.size() > input.size()) {
		sparseTable(input, queries, answer);
	}
	else {
		segTree(input, queries, answer);
	}
	return answer;
}