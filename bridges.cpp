#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

using namespace std;

class Graph {
private:
	vector<vector<int> > adjacency;
	vector<int> discovery;
	vector<int> fup;
	set<int> bridges;
	map<pair<int, int>, int> bridge_number;
	int time;
public:
	Graph(int n);

	void init(int k);
	void find_bridges(int vertex, int parent);
	void print_answer();
	int get_discovery(int vertex) {
		return discovery[vertex];
	}
};

Graph::Graph(int n) {
	adjacency.assign(n, vector<int>());
	discovery.assign(n, 0);
	fup.assign(n, 0);
	time = 0;
}

void Graph::init(int k) {
	int u, v;
	for (int i = 0; i < k; i++) {
		cin >> u >> v;
		u--;
		v--;
		adjacency[u].push_back(v);
		adjacency[v].push_back(u);
		if (bridge_number[make_pair(u, v)]) {
			bridge_number[make_pair(u, v)] = -1;
			bridge_number[make_pair(v, u)] = -1;
		}
		else {
			bridge_number[make_pair(u, v)] = i + 1;
			bridge_number[make_pair(v, u)] = i + 1;
		}
	}
}

void Graph::find_bridges(int vertex, int parent = -1) {
	discovery[vertex] = time++;
	fup[vertex] = discovery[vertex];
	for (auto u : adjacency[vertex]) {
		if (u != parent) {
			if (discovery[u]) {
				fup[vertex] = ((fup[vertex] <= discovery[u]) ? fup[vertex] : discovery[u]);
			}
			else {
				find_bridges(u, vertex);
				fup[vertex] = ((fup[vertex] <= fup[u]) ? fup[vertex] : fup[u]);
			}
		}
	}
	if (parent != -1 && fup[vertex] > discovery[parent]) {
		int answer = bridge_number[make_pair(vertex, parent)];
		if (answer != -1) {
			bridges.insert(answer);
		}
	}
}

void Graph::print_answer() {
	cout << bridges.size() << endl;
	for (auto u : bridges) {
		cout << u << endl;
	}
}

int main() {
	int n, m;
	cin >> n >> m;

	Graph graph(n);
	graph.init(m);

	for (int i = 0; i < n; i++) {
		if (graph.get_discovery(i) == 0) {
			graph.find_bridges(i);
		}
	}

	graph.print_answer();
	return 0;
}