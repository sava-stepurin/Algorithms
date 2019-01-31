#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int INF = 100000;

class Graph {
private:
	struct Edge {
		int from, to, weight;
		Edge(int v, int u, int w) {
			from = v;
			to = u;
			weight = w;
		}
	};
	vector<Edge> edges;
	vector<int> distance;
	vector<int> parent;

	void relax(Edge edge);
	int BellmanFord();
public:
	Graph(int n);
	void add_edge(int v, int u, int weight);
	vector<int> negative_cycle();
};

int main() {
	int n;
	cin >> n;
	Graph graph(n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int weight;
			cin >> weight;
			if (weight != INF) {
				graph.add_edge(i, j, weight);
			}
		}
	}
	vector<int> result = graph.negative_cycle();
	if (result.size() == 0) {
		cout << "NO\n";
	}
	else {
		cout << "YES\n";
		cout << result.size() + 1 << "\n";
		for (int i = 0; i < result.size(); i++) {
			cout << result[i] << " ";
		}
		cout << result[0] << "\n";
	}
	return 0;
}

Graph::Graph(int n) {
	distance.assign(n, 0);
	parent.assign(n, -1);
}

void Graph::add_edge(int v, int u, int weight) {
	edges.push_back(Edge(v, u, weight));
}

void Graph::relax(Edge edge) {
	if (distance[edge.to] > distance[edge.from] + edge.weight) {
		distance[edge.to] = distance[edge.from] + edge.weight;
		parent[edge.to] = edge.from;
	}
}

int Graph::BellmanFord() {
	for (int i = 0; i < distance.size(); i++) {
		for (auto edge : edges) {
			relax(edge);
		}
	}
	for (auto edge : edges) {
		if (distance[edge.to] > distance[edge.from] + edge.weight) {
			return edge.to;
		}
	}
	return -1;
}

vector<int> Graph::negative_cycle() {
	int vertex = BellmanFord();
	if (vertex == -1) {
		return vector<int>();
	}
	else {
		for (int i = 0; i < parent.size(); i++) {
			vertex = parent[vertex];
		}
		vector<int> result;
		result.push_back(vertex + 1);
		int temp = parent[vertex];
		while (temp != vertex) {
			result.push_back(temp + 1);
			temp = parent[temp];
		}
		reverse(result.begin(), result.end());
		return result;
	}
}