#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const double INF = 100000000;

class Graph {
private:
	vector<pair<int, int>> vertex_coordinates;
	vector<double> distance;
	vector<bool> used;

	double Prim();
	double count_distance(int u, int v);
public:
	Graph(int n);
	void add_vertex(int x, int y);
	double mst();
};

int main() {
	int n;
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	cin >> n;
	Graph graph(n);
	for (int i = 0; i < n; i++) {
		int x, y;
		cin >> x >> y;
		graph.add_vertex(x, y);
	}
	cout.precision(20);
	cout << graph.mst() << "\n";
}

Graph::Graph(int n) {
	distance.assign(n, INF);
	used.assign(n, false);
	distance[0] = 0;
}

void Graph::add_vertex(int x, int y) {
	vertex_coordinates.push_back(make_pair(x, y));
}

double Graph::count_distance(int u, int v) {
	return sqrt((vertex_coordinates[u].first - vertex_coordinates[v].first) * (vertex_coordinates[u].first - vertex_coordinates[v].first) +
		(vertex_coordinates[u].second - vertex_coordinates[v].second) * (vertex_coordinates[u].second - vertex_coordinates[v].second));
}

double Graph::Prim() {
	double result = 0;
	for (int i = 0; i < vertex_coordinates.size(); i++) {
		int min_vertex = -1;
		for (int vertex = 0; vertex < vertex_coordinates.size(); vertex++) {
			if (!used[vertex] && (min_vertex == -1 || distance[min_vertex] > distance[vertex])) {
				min_vertex = vertex;
			}
		}
		used[min_vertex] = true;
		result += distance[min_vertex];
		for (int u = 0; u < vertex_coordinates.size(); u++) {
			if (!used[u] && distance[u] > count_distance(min_vertex, u)) {
				distance[u] = count_distance(min_vertex, u);
			}
		}
	}
	return result;
}

double Graph::mst() {
	return Prim();
}