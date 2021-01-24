#include "ShortestPath.h"

void ShortestPath::Dijkstra(int s,  vector<int> &dist, vector<int> &last)
{
	vector<bool> reachState(VNum, false);
	for (int i = 0; i < VNum; i++) {
		if (i == s) {
			dist[i] = 0;
			last[i] = s;
		}
		else {
			dist[i] = INT_MAX;
			last[i] = -1;
		}
	}
	reachState[s] = 0;

	while (true) {
		// find the smallest scanning node
		int node = -1, minVal = INT_MAX;
		for (int i = 0; i < VNum; i++) {
			if (dist[i] < minVal && !reachState[i]) {
				node = i;
				minVal = dist[i];
				reachState[i] = true;
			}
		}
		if (node == -1) break; // no more reachable nodes
		for (int i = 0; i < VNum; i++) {
			if (E[node][i] < INT_MAX && !reachState[i]) {
				if (E[node][i] + dist[node] < dist[i]) {
					dist[i] = E[node][i] + dist[node];
					last[i] = node;
				}
			}
		}
	}
}
