#include <vector>

using namespace std;

#define INF INT_MAX

// エッジの構造体
template <typename T = long long>
struct edge{
	int to;
	T weight;
	edge(int to,T weight) : to(to),weight(weight){}
};

// ワーシャルフロイド法 n := 頂点数
template <typename T>
vector<vector<T>> warshall_floyd(vector<vector<edge<T>>> &G, int n) {
	vector<vector<T>> dist(n + 1, vector<T>(n + 1, INF));
	for (int i = 0; i < n; i++) {
		for (auto e : G[i])
			dist[i][e.to] = e.weight;
		dist[i][i] = 0;
	}
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			for (int k = 0; k < n; k++)
				if (dist[j][i] != INF && dist[i][k] != INF)
					dist[j][k] = min(dist[j][k], dist[j][i] + dist[i][k]);
	return dist;
}