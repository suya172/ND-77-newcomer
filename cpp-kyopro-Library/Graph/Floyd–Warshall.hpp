#include <vector>

using namespace std;

#define INF INT_MAX

/**
 * @brief 辺の構造体
 *
 * @tparam long コストの型
 */
template <typename T = long long>
struct edge{
	int to;
	T weight;
	edge(int to,T weight) : to(to),weight(weight){}
};

/**
 * @brief ワーシャルフロイド法 O(n^3)
 * 
 * @tparam T コストの型
 * @param G グラフ
 * @param n 頂点数
 * @return vector<vector<T>> 最短距離のリスト
 */
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