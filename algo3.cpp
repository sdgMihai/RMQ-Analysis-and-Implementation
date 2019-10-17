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

class Data {
public:
	std::vector<int>& sTree;
	std::vector<int>& answer;
	const std::vector<int>& input;
	int firstQueryIndex;
	int secQueryIndex;

	Data(std::vector<int>& sTree,
		std::vector<int>& answer,
		const std::vector<int>& input): sTree(sTree), answer(answer), input(input) {}

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

std::vector<int> rmq(const std::vector<int>& input, const std::vector< std::pair<int, int> >& queries) {
	std::vector<int> sTree((1 << (iLog(input.size()) + 2)) - 1);
	std::vector<int> answer(queries.size());
	Data data(sTree, answer, input);

	getSegmentTree(1, 0, input.size() - 1, data);
	for (int i = 0; i < queries.size(); ++i) {
		data.getQuery(queries[i].first, queries[i].second);
		answer[i] = input[query(1, 0, input.size() - 1, data)];
	}
	return answer;
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