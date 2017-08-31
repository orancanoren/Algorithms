#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;

typedef unsigned int uint;

const double UNKNOWN = -1.0;

// BOTTOM UP APPROACH

double cut_rod_dynamic(vector< double > & table, uint i, const vector< double > & prices) {
	if (table[i] != -1.0)
		return table[i];
	
	double current_max = UNKNOWN;
	for (uint j = 0; j < i; j++) {
		current_max = max(current_max, prices[j] + table[table.size() - j]);
	}
}

double cut_rod(const vector< double > & prices) {
	const uint rod_length = prices.size();
	vector< double > table(rod_length, UNKNOWN);
	table[rod_length - 1] = prices[rod_length - 1];

	double max_revenue = UNKNOWN;
	for (uint i = rod_length - 1; i >= 0; i--) {
		max_revenue = max(max_revenue, cut_rod_dynamic(table, i, prices));
	}

	return max_revenue;
}

int main() {
	uint stick_length;
	cout << "------- Rod Cutting Problem -------" << endl
		<< "Enter the length of the rod:" << endl;
	cin >> stick_length;
	cout << "For each length in range [1, " << stick_length << "] enter the price of" << endl
		<< "rod corresponding to that length" << endl
		<< "(" << stick_length << " space seperated numbers) >>";
	vector< double > prices(stick_length);
	for (uint i = 0; i < stick_length; i++) {
		cin >> prices[i];
	}
	
	cout << "Optimal price: " << cut_rod(prices) << endl;
	return 0;
}