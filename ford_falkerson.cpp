#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX = 1000000001;

class Transport_network {
private:
	vector<vector<int>> residual;
	int color;
	vector<int> colors;
	int source, sink;
	int dfs(int vertex, int minimum);
public:
	Transport_network(int n);
	void addEdge(int v, int u, int throughput);
	int FordFulkerson(int source, int sink);
};

int main() {
	int n, m;
	cin >> n >> m;
	Transport_network transport_network(n);
	for (int i = 0; i < m; i++) {
		int v, u, throughput;
		cin >> v >> u >> throughput;
		transport_network.addEdge(v, u, throughput);
	}
	cout << transport_network.FordFulkerson(1, n) << endl;
	return 0;
}

Transport_network::Transport_network(int n) {
	residual.assign(n, vector<int>(n, 0));
	colors.assign(n, 0);
	color = 1;
}

void Transport_network::addEdge(int v, int u, int throughput) {
	residual[v - 1][u - 1] += throughput;
}

int Transport_network::dfs(int vertex, int minimum = MAX) {
	if (vertex == sink) {
		return minimum;
	}
	else {
		colors[vertex] = color;
		for (int to = 0; to < residual.size(); to++) {
			if (residual[vertex][to] && colors[to] != color) {
				int result;
				if (result = dfs(to, min(minimum, residual[vertex][to]))) {
					residual[vertex][to] -= result;
					residual[to][vertex] += result;
					return result;
				}
			}
		}
		return 0;
	}
}

int Transport_network::FordFulkerson(int source, int sink) {
	this->source = source - 1;
	this->sink = sink - 1;
	int result, max_flow = 0;
	while (result = dfs(this->source)) {
		max_flow += result;
		color++;
	}
	return max_flow;
}