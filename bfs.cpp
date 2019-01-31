#include <iostream>
#include <vector>
#include <queue>

using namespace std;

class Graph {
public:
	vector<int> color;
	vector<vector<int>> adjacents;
	vector<int> parent;
	queue<int> BFS_queue;
	int is_way;

	Graph(int n) {
		color.resize(n, 0);
		adjacents.resize(n, vector<int>());
		parent.resize(n, -1);
		is_way = false;
	}

	void init(int m);
	void BFS(int vertex);
};

void Graph::init(int m) {
	int u, v;
	for (int i = 0; i < m; i++) {
		cin >> u >> v;
		u--;
		v--;
		adjacents[u].push_back(v);
		adjacents[v].push_back(u);
	}
}

void Graph::BFS(int vertex) {
	color[vertex] = 1;
	BFS_queue.push(vertex);
	while (BFS_queue.size()) {
		int current;
		current = BFS_queue.front();
		BFS_queue.pop();
		for (int i = 0; i < adjacents[current].size(); i++) {
			if (color[adjacents[current][i]] == 0) {
				parent[adjacents[current][i]] = current;
				color[adjacents[current][i]] = 1;
				BFS_queue.push(adjacents[current][i]);
			}
		}
	}
	color[vertex] = 2;
}

int main() {
	int n, m, first, second;
	cin >> n >> m >> first >> second;
	first--;
	second--;
	Graph graph(n);
	graph.init(m);
	graph.BFS(first);
	if (graph.parent[second] == -1 && first != second) {
		cout << "-1" << endl;
	}
	else {
		vector<int> result;
		int current = second;
		while (current >= 0 && current != first) {
			result.push_back(current + 1);
			current = graph.parent[current];
		}
		cout << result.size() << endl;
		cout << first + 1 << ' ';
		for (int i = result.size() - 1; i >= 0; i--) {
			cout << result[i] << ' ';
		}
	}
	return 0;
}