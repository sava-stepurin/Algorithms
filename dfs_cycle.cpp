#include <iostream>
#include <vector>

using namespace std;

class Graph {
public:
	vector<int> color;
	vector<vector<int>> adjacents;
	vector<int> result;
	int is_cycle;

	Graph(int n) {
		color.resize(n, 0);
		adjacents.resize(n, vector<int>());
		is_cycle = false;
	}

	void init(int m);
	void DFS(int vertex);
};

void Graph::init(int m) {
	int u, v;
	for (int i = 0; i < m; i++) {
		cin >> u >> v;
		u--;
		v--;
		adjacents[u].push_back(v);
	}
}

void Graph::DFS(int vertex) {
	color[vertex] = 1;
	for (int i = 0; i < adjacents[vertex].size(); i++) {
		if (color[adjacents[vertex][i]] == 0) {
			DFS(adjacents[vertex][i]);
		}
		else if (color[adjacents[vertex][i]] == 1) {
			is_cycle = true;
		}
	}
	result.push_back(vertex);
	color[vertex] = 2;
}

int main() {
	int n, m;
	cin >> n >> m;
	Graph graph(n);
	graph.init(m);
	for (int i = 0; i < n; i++) {
		if (graph.color[i] == 0) {
			graph.DFS(i);
		}
	}
	if (graph.is_cycle) {
		cout << "-1" << endl;
	}
	else {
		for (int i = graph.result.size() - 1; i >= 0; i--) {
			cout << graph.result[i] + 1 << ' ';
		}
	}
	return 0;
}