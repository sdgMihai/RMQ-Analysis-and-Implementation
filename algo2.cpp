#include "algo.h"
#include <stack>
#include <algorithm>
#include <cmath>

void computeNeighbours(std::vector< std::vector<int> >& neighbours, std::vector<int>& tree);
int lca(int root,
	const std::vector<int>& tree,
	const std::vector<int>& section,
	const std::vector<int>& level,
	int firstNode,
	int secondNode);
void dfsLevel(int node,
	std::vector< std::vector<int> >& neighbours,
	std::vector<int>& level,
	int currentLevel,
	int& height);
void dfs(int node,
	const std::vector<int>& tree,
	std::vector<int>& section,
	const std::vector<int>& level,
	std::vector< std::vector<int> >& neighbours,
	int nr);
void computeTree(const std::vector<int>& input, std::vector<int>& tree, int& rootIndex);

std::vector<int> rmq(const std::vector<int>& input, const std::vector< std::pair<int, int> >& queries) {
	int treeRootIndex, treeHeight;
	std::vector<int> tree(input.size());  // stores the index of minimum as a cartesian tree
	std::vector<int> section(input.size());  // section[i] = x; x is section of node i
	std::vector<int> level(input.size());  // level of node i = level[i]
	std::vector< std::vector<int> > neighbours(input.size());  // neighbours[i] = neighbours of node i
	std::vector<int> answer(queries.size());
	
	computeTree(input, tree, treeRootIndex);  // init tree
	computeNeighbours(neighbours, tree);  // init neighbours, in fact neighbours = sons
	dfsLevel(treeRootIndex, neighbours, level, 0, treeHeight);
	dfs(treeRootIndex, tree, section, level, neighbours, (int)sqrt((double) treeHeight));

	for (int i = 0; i < queries.size(); ++i) {  // answer queries.
		answer[i] = input[lca(treeRootIndex, tree, section, level, queries[i].first, queries[i].second)];
	}
	return answer;
}

void computeNeighbours(std::vector< std::vector<int> >& neighbours, std::vector<int>& tree) {
	for (int i = 0; i < neighbours.size(); ++i) {
		if(tree[i] != -1)
			neighbours[tree[i]].push_back(i);
	}
}

int lca(int root,
	const std::vector<int>& tree,
	const std::vector<int>& section,
	const std::vector<int>& level,
	int firstNode,
	int secondNode) {
	while (section[firstNode] != section[secondNode]) {
		if (level[firstNode] > level[secondNode]) {
			firstNode = section[firstNode];
		}
		else {
			secondNode = section[secondNode];
		}
	}
	//now we are in the same section => we can compute the lca
	while (firstNode != secondNode) {
		if (level[firstNode] > level[secondNode]) {
			firstNode = tree[firstNode];
		}
		else {
			secondNode = tree[secondNode];
		}
	}
	return firstNode;
}

void dfsLevel(int node,
	std::vector< std::vector<int> >& neighbours,
	std::vector<int>& level,
	int currentLevel,
	int& height) {
	level[node] = currentLevel;
	height = std::max(currentLevel, height);
	for (auto it = neighbours[node].begin(); it != neighbours[node].end(); ++it) {
		dfsLevel(*it, neighbours, level, currentLevel + 1, height);
	}
}

void dfs(int node,
	const std::vector<int>& tree,
	std::vector<int>& section,
	const std::vector<int>& level,
	std::vector< std::vector<int> >& neighbours,
	int nr) {
	/*
	if node is situated in the first
		section then section[node] = 1
	if node is situated at the beginning
		of some section then section[node] = tree[node]
	if none of those two cases occurs, then
		section[node] = section[tree[node]]
	*/
	if (level[node] < nr)
		section[node] = 1;
	else
		if (level[node] % nr == 0)
			section[node] = tree[node];
		else
			section[node] = section[tree[node]];

	for (auto it = neighbours[node].begin(); it != neighbours[node].end(); ++it)
		dfs(*it, tree, section, level, neighbours, nr);
}

/*
* At the beginning the stack is empty. We will then insert the elements of A in the stack.
* At the i-th step input[i] will be added next to the last element in the stack that has a smaller
* or equal value to input[i], and all the greater elements will be removed.
* The element that was in the stack on the position of input[i] before the insertion was done
* will become the left son of i, and input[i] will become the right son of the smaller element behind him.
* At every step the first element in the stack is the root of the cartesian tree.
* It’s easier to build the tree if the stack will hold the indexes of the elements, and not their value.
* @param input a reference to a vector of numbers(int) to be processed
* @param tree cartesian tree
*/
void computeTree(const std::vector<int>& input, std::vector<int>& tree, int& rootIndex) {
	std::stack<int> minStack;
	bool stackHasChanged;
	int leftSonPos;

	for (int i= 0; i < input.size(); ++i) {
		stackHasChanged = false;

		// compute the position of the first element that is 
		// equal or smaller than input[i]
		while (!minStack.empty() && input[minStack.top()] > input[i]) {
			leftSonPos = minStack.top();
			minStack.pop();
			stackHasChanged = true;
		}
		// modify tree as explained
		if (!minStack.empty()) {  // i is the right son of minStack.top()
			tree[i] = minStack.top();
		}
		if (stackHasChanged) {  // leftSonPos is the left son of i
			tree[leftSonPos] = i;
		}
		minStack.push(i);
	}

	//the first element in the stack is the root of
	//the tree, so it has no father
	while (minStack.size() > 1)
		minStack.pop();
	rootIndex = minStack.top();
	tree[rootIndex] = -1;
}