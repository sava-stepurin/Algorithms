#include <iostream>
#include <cstring>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

void z_function(string& str, vector<int>& z) {
	z[0] = str.size();
	int left = 0, right = 0;
	for (int i = 1; i < str.size(); i++) {
		if (i > right) {
			z[i] = 0;
		}
		else {
			z[i] = min(z[i - left], right - i + 1);
		}
		while (i + z[i] < str.size() && str[i + z[i]] == str[z[i]]) {
			++z[i];
		}
		if (i + z[i] - 1 > right) {
			left = i;
			right = i + z[i] - 1;
		}
	}
}

int main() {
	string str;
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	cin >> str;
	vector<int> z(str.size());
	z_function(str, z);
	for (int i = 0; i < z.size(); i++) {
		cout << z[i] << ' ';
	}
	return 0;
}