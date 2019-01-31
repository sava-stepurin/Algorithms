#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int gcd(int a, int b) {
	while (b != 0) {
		a %= b;
		swap(a, b);
	}
	return a;
}

vector<int> init(vector<int> array) {
	int k = 0;
	for (; (1 << k) < array.size(); k++);
	array.resize((1 << k), 0);
	vector<int> tree(2 * array.size() - 1);
	for (int i = 0; i < array.size(); i++) {
		tree[i + array.size() - 1] = array[i];
	}
	for (int i = array.size() - 2; i >= 0; i--) {
		tree[i] = gcd(tree[2 * i + 1], tree[2 * i + 2]);
	}
	return tree;
}

int get(int left, int right, vector<int>& tree) {
	left += tree.size() / 2;
	right += tree.size() / 2;
	int result = 0;
	while (left <= right) {
		if (left % 2 == 0) {
			result = gcd(result, tree[left++]);
		}
		if (right % 2 == 1) {
			result = gcd(result, tree[right--]);
		}
		if (left > right) {
			break;
		}
		left = (left - 1) / 2;
		right = (right - 1) / 2;
	}
	return result;
}

int main() {
	int n;
	cin >> n;
	vector<int> array(n);
	for (int i = 0; i < n; i++) {
		int value;
		cin >> value;
		array[i] = value;
	}
	vector<int> tree = init(array);
	int k;
	cin >> k;
	for (int i = 0; i < k; i++) {
		int left, right;
		cin >> left >> right;
		cout << get(left - 1, right - 1, tree) << endl;
	}
	return 0;
}