#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

const int MAX = 1000000001;

class Transport_network {
private:
	vector<vector<int>> residual;
	int color;
	vector<int> colors;
	int source, sink;
	vector<int> parent;
	vector<vector<int>> adjacent_list;
	queue<int> bfs_queue;
	int bfs();
public:
	Transport_network(int n);
	void addEdge(int v, int u, int throughput);
	long long int EdmondsKarp(int source, int sink);
};

int main() {
	std::ios_base::sync_with_stdio(false);
	std::cin.tie(0);
	int n, m;
	cin >> n >> m;
	Transport_network transport_network(n);
	for (int i = 0; i < m; i++) {
		int v, u, throughput;
		cin >> v >> u >> throughput;
		transport_network.addEdge(v, u, throughput);
	}
	cout << transport_network.EdmondsKarp(1, n);
	return 0;
}

Transport_network::Transport_network(int n) {
	residual.assign(n, vector<int>(n, 0));
	colors.assign(n, 0);
	adjacent_list.resize(n);
	parent.assign(n, -1);
	color = 1;
}

void Transport_network::addEdge(int v, int u, int throughput) {
	residual[v - 1][u - 1] = throughput;
	adjacent_list[u - 1].push_back(v - 1);
	adjacent_list[v - 1].push_back(u - 1);
}

int Transport_network::bfs() {
	while (!bfs_queue.empty()) {
		bfs_queue.pop();
	}
	bfs_queue.push(source);
	bool found = false;
	while (!bfs_queue.empty() && !found) {
		int from = bfs_queue.front();
		bfs_queue.pop();
		for (int to : adjacent_list[from]) {
			if (residual[from][to] && colors[to] != color) {
				colors[to] = color;
				parent[to] = from;
				if (to == sink) {
					found = true;
					break;
				}
				bfs_queue.push(to);
			}
		}
		colors[from] = color;
	}
	if (!found) {
		return 0;
	}
	else {
		int min_flow = residual[parent[sink]][sink];
		int vertex = sink;
		while (vertex != source) {
			if (residual[parent[vertex]][vertex] < min_flow) {
				min_flow = residual[parent[vertex]][vertex];
			}
			vertex = parent[vertex];
		}
		vertex = sink;
		while (vertex != source) {
			residual[parent[vertex]][vertex] -= min_flow;
			residual[vertex][parent[vertex]] += min_flow;
			vertex = parent[vertex];
		}
		return min_flow;
	}
}

long long int Transport_network::EdmondsKarp(int source, int sink) {
	this->source = source - 1;
	this->sink = sink - 1;
	long long int result, max_flow = 0;
	while (result = bfs()) {
		max_flow += result;
		color++;
	}
	return max_flow;
}