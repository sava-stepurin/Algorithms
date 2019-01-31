#include <iostream>
#include <cstring>
#include <sstream>
#include <vector>
using namespace std;

void prefix_function(string& str, vector<int>& prefix) {
	prefix[0] = 0;
	for (int i = 1; i < str.size(); i++) {
		int temp = prefix[i - 1];
		while (temp > 0 && str[temp] != str[i]) {
			temp = prefix[temp - 1];
		}
		prefix[i] = ((str[temp] == str[i]) ? (temp + 1) : 0);
	}
}

int main() {
	string str;
	cin >> str;
	vector<int> prefix(str.size());
	prefix_function(str, prefix);
	for (int i = 0; i < prefix.size(); i++) {
		cout << prefix[i] << ' ';
	}
	return 0;
}