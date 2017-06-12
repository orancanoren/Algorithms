#include <iostream>
#include <stack>
#include <vector>
#include <algorithm>
#include <cassert>
using namespace std;

struct Interval {
	Interval(int left, int right) : left(left), right(right) { }
	Interval() { }
	int left;
	int right;

	// overload a comparison operator for std::sort
	bool operator < (const Interval & RHS) {
		if (this->left < RHS.left) {
			return true;
		}
		else {
			return false;
		}
	}
};

void printStack(stack<Interval> & st) {
	Interval current = st.top();
	st.pop();
	if (!st.empty()) {
		printStack(st);
	}
	cout << current.left << " " << current.right << endl;
}

int main() {
	int numIntervals;
	vector<Interval> intervals;
	cout << "--------------" << endl
		<< "Merging Intervals" << endl
		<< "Run-time: O(nlog(n))" << endl
		<< "Space: O(n)" << endl
		<< "--------------" << endl
		<< "How many intervals are you passing to the algorithm?" << endl
		<< ">> ";
	cin >> numIntervals;
	assert(numIntervals > 0); // assumint there exists at least one interval
	intervals.resize(numIntervals);
	
	// Obtain the intervals
	auto iter = intervals.begin();
	for (int interval_i = 0; interval_i < numIntervals; interval_i++) {
		int left, right;
		cout << "Enter space seperated interval bounds in <left> <right> order" << endl
			<< ">> ";
		cin >> left >> right;
		*iter = Interval(left, right);
		iter++;
	}

	// Sort the intervals with respect to left boundary
	sort(intervals.begin(), intervals.end());

	// Iterate over sorted intervals
	stack<Interval> disjointIntervals;
	disjointIntervals.push(intervals[0]);
	for (int i = 1; i < numIntervals; i++) {
		if (intervals[i].left <= disjointIntervals.top().right) {
			// Merge the two intervals by modifying top of the stack
			disjointIntervals.top().right = intervals[i].right;
		}
		else {
			disjointIntervals.push(intervals[i]);
		}
	}

	// The stack we have consists of disjoint intervals covering all the intervals in the input
	// Print merged intervals starting with the smallest one first
	printStack(disjointIntervals);

	return 0;
}