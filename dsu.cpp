#include <iostream>
#include <vector>
#include <cstring>
#include <sstream>
using namespace std;

class DSU {
private:
	vector<int> tree;
	vector<int> rank;
	void make_set(int vertex);
	int find_set(int vertex);
public:
	DSU(int n);
	void union_sets(int first_vertex, int second_vertex);
	bool in_one_set(int first_vertex, int second_vertex);
};

struct Command {
	string command;
	int from, to;
	Command(string text, int v, int u) {
		command = text;
		from = v - 1;
		to = u - 1;
	}
};

int main() {
	int n, m, k;
	cin >> n >> m >> k;
	DSU dsu(n);
	for (int i = 0; i < m; i++) {
		int v, u;
		cin >> v >> u;
	}
	vector<Command> commands;
	for (int i = 0; i < k; i++) {
		string text;
		int v, u;
		cin >> text >> v >> u;
		commands.push_back(Command(text, v, u));
	}
	vector<bool> answers;
	for (int i = k - 1; i >= 0; i--) {
		if (commands[i].command == "cut") {
			dsu.union_sets(commands[i].from, commands[i].to);
		}
		else {
			answers.push_back(dsu.in_one_set(commands[i].from, commands[i].to));
		}
	}
	for (int i = answers.size() - 1; i >= 0; i--) {
		if (answers[i]) {
			cout << "YES\n";
		}
		else {
			cout << "NO\n";
		}
	}
	return 0;
}

void DSU::make_set(int vertex) {
	tree[vertex] = vertex;
	rank[vertex] = 0;
}

DSU::DSU(int n) {
	tree.assign(n, 0);
	rank.assign(n, 0);
	for (int i = 0; i < n; i++) {
		make_set(i);
	}
}

int DSU::find_set(int vertex) {
	if (vertex == tree[vertex]) {
		return vertex;
	}
	return tree[vertex] = find_set(tree[vertex]);
}

void DSU::union_sets(int first_vertex, int second_vertex) {
	first_vertex = find_set(first_vertex);
	second_vertex = find_set(second_vertex);
	if (first_vertex != second_vertex) {
		if (rank[second_vertex] > rank[first_vertex]) {
			swap(first_vertex, second_vertex);
		}
		tree[second_vertex] = first_vertex;
		if (rank[second_vertex] == rank[first_vertex]) {
			++rank[first_vertex];
		}
	}
}

bool DSU::in_one_set(int first_vertex, int second_vertex) {
	return (find_set(first_vertex) == find_set(second_vertex));
}