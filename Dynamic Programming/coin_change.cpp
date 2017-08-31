#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdint>

using namespace std;

vector<vector<int64_t>> memo;
vector<int> coins;

int64_t num_ways(int s, int i) {
	if (s < 0 || i >= memo[0].size()) 
		return 0;
	
	if (memo[s][i] != -1)
		return memo[s][i];
	
	memo[s][i] = num_ways(s - coins[i], i) + num_ways(s, i + 1);
	return memo[s][i];
}

int main() {
	int n, m;
	cin >> n >> m;

	// 1 - Prepare the coins array
	coins.resize(m);
	for (int i = 0; i < m; i++) {
		cin >> coins[i];
	}
	sort(coins.begin(), coins.end());
	
	// 2 - Prepare the memoization table
	memo.resize(n + 1);
	memo[0].resize(m);
	for (int j = 0; j < m; j++) {
		memo[0][j] = 1;
	}
	for (int i = 1; i < n + 1; i++) {
		memo[i].resize(m);
		for (int j = 0; j < m; j++) {
			memo[i][j] = -1;
		}
	}
	if (coins[0] < memo.size()) {
		memo[coins[0]][0] = 1;
		cout << num_ways(n, 0);
	}
	else {
		cout << 0;
	}

	return 0;
}