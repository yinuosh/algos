#pragma once
#include "Header.h"
#include <map>
#include <set>

using namespace std;

class ShortestPath
{
private:
	vector<vector<int>> E;
	int VNum;

public:
	ShortestPath(vector<vector<int>> edges, int vNum) :VNum(VNum), E(edges) {};
	void Dijkstra(int s, vector<int> &dist, vector<int> &next);
	void Dijkstra(int s, int d, vector<int> path);
};

