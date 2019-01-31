#include <iostream>
#include <vector>

using namespace std;

void update(long long int x, long long int y, long long int z, long long int value, vector<vector<vector<long long int>>>& binary_indexed_tree) {
	for (int i = x; i < binary_indexed_tree.size(); i |= i + 1) {
		for (int j = y; j < binary_indexed_tree.size(); j |= j + 1) {
			for (int k = z; k < binary_indexed_tree.size(); k |= k + 1) {
				binary_indexed_tree[i][j][k] += value;
			}
		}
	}
}

long long int sum(long long int x, long long int y, long long int z, vector<vector<vector<long long int>>>& binary_indexed_tree) {
	long long int result = 0;
	for (int i = x; i >= 0; i = (i & (i + 1)) - 1) {
		for (int j = y; j >= 0; j = (j & (j + 1)) - 1) {
			for (int k = z; k >= 0; k = (k & (k + 1)) - 1) {
				result += binary_indexed_tree[i][j][k];
			}
		}
	}
	return result;
}

long long int get_sum(long long int x, long long int y, long long int z, vector<vector<vector<long long int>>>& binary_indexed_tree) {
	if (x >= 0 && y >= 0 && z >= 0) {
		return sum(x, y, z, binary_indexed_tree);
	}
	else {
		return 0;
	}
}

int main() {
	long long int n;
	cin >> n;
	vector<vector<vector<long long int>>> binary_indexed_tree(n, vector<vector<long long int>>(n, vector<long long int>(n)));
	int command;
	cin >> command;
	while (command != 3) {
		if (command == 1) {
			long long int x, y, z, value;
			cin >> x >> y >> z >> value;
			update(x, y, z, value, binary_indexed_tree);
		}
		else if (command == 2) {
			long long int x1, y1, z1, x2, y2, z2;
			cin >> x1 >> y1 >> z1 >> x2 >> y2 >> z2;
			cout << sum(x2, y2, z2, binary_indexed_tree) - get_sum(x2, y2, z1 - 1, binary_indexed_tree)
				- get_sum(x2, y1 - 1, z2, binary_indexed_tree) - get_sum(x1 - 1, y2, z2, binary_indexed_tree)
				+ get_sum(x1 - 1, y1 - 1, z2, binary_indexed_tree) + get_sum(x1 - 1, y2, z1 - 1, binary_indexed_tree) 
				+ get_sum(x2, y1 - 1, z1 - 1, binary_indexed_tree) - get_sum(x1 - 1, y1 - 1, z1 - 1, binary_indexed_tree) << endl;
		}
		cin >> command;
	}
	return 0;
}