#include <iostream>
#include <vector>
using namespace std;

const int INF = 30000;

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
	void relax(Edge edge);
	void BellmanFord();
public:
	Graph(int n);
	void add_edge(int v, int u, int weight);
	vector<int>& distances();
};

int main() {
	int n, m;
	cin >> n >> m;
	Graph graph(n);
	for (int i = 0; i < m; i++) {
		int v, u, weight;
		cin >> v >> u >> weight;
		graph.add_edge(v, u, weight);
	}
	vector<int> result = graph.distances();
	for (int i = 0; i < result.size(); i++) {
		cout << result[i] << ' ';
	}
	return 0;
}

Graph::Graph(int n) {
	distance.assign(n, INF);
	distance[0] = 0;
}

void Graph::add_edge(int v, int u, int weight) {
	edges.push_back(Edge(v - 1, u - 1, weight));
}

void Graph::relax(Edge edge) {
	if (distance[edge.from] != INF && distance[edge.to] > distance[edge.from] + edge.weight) {
		distance[edge.to] = distance[edge.from] + edge.weight;
	}
}

void Graph::BellmanFord() {
	for (int i = 0; i < distance.size(); i++) {
		for (auto edge : edges) {
			relax(edge);
		}
	}
}

vector<int>& Graph::distances() {
	BellmanFord();
	return distance;
}