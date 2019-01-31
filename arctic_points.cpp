#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

const int MAX = 1000000000;

class Graph {
private:
	vector<vector<int>> adjacent;
	vector<int> discovery;
	vector<int> up;
	vector<bool> is_artic;
	int timer;
	void find_artic_point_(int vertex, int parent);
public:
	Graph(int n) {
		adjacent.resize(n, vector<int>());
		discovery.resize(n);
		up.resize(n, MAX);
		is_artic.resize(n, false);
		timer = 1;
	}

	void add_edge(int v, int u) {
		adjacent[u - 1].push_back(v - 1);
		adjacent[v - 1].push_back(u - 1);
	}

	vector<int> find_artic_point();
};

void Graph::find_artic_point_(int vertex, int parent = -1) {
	discovery[vertex] = ++timer;
	int children_count = 0;
	for (int i = 0; i < adjacent[vertex].size(); i++) {
		if (adjacent[vertex][i] != parent) {
			if (discovery[adjacent[vertex][i]] != 0) {
				up[vertex] = min(up[vertex], discovery[adjacent[vertex][i]]);
			}
			else {
				find_artic_point_(adjacent[vertex][i], vertex);
				if (up[adjacent[vertex][i]] >= discovery[vertex] && parent != -1) {
					is_artic[vertex] = true;
				}
				up[vertex] = min(up[vertex], up[adjacent[vertex][i]]);
				children_count++;
			}
			if (parent == -1 && children_count > 1) {
				is_artic[vertex] = true;
			}
		}
	}
}

vector<int> Graph::find_artic_point() {
	for (int i = 0; i < adjacent.size(); i++) {
		if (discovery[i] == 0) {
			find_artic_point_(i);
		}
	}
	vector<int> result;
	for (int i = 0; i < is_artic.size(); i++) {
		if (is_artic[i]) {
			result.push_back(i + 1);
		}
	}
	return result;
}

int main() {
	int n, m;
	cin >> n >> m;
	Graph graph(n);
	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;
		graph.add_edge(u, v);
	}
	vector<int> result = graph.find_artic_point();
	cout << result.size() << endl;
	for (int i = 0; i < result.size(); ++i) {
		cout << result[i] << endl;
	}
	return 0;
}