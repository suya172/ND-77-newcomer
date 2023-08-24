#include <vector>
#include <queue>

using namespace std;

#define INF INT_MAX

//エッジの構造体
template <typename T = long long>
struct edge{
	int to;
	T cost;
	edge(int to, T cost) : to(to), cost(cost) {}
};

//ダイクストラ法(コストの配列と経路の配列をpairにして返す)
template <typename T>
pair<vector<T>, vector<int>> dijkstra(const vector<vector<edge<T>>> &G, int s) {
	vector<T> dist(G.size(), INF);
	vector<int> prev(G.size(), -1);
	priority_queue<pair<T, int>, vector<pair<T, int>>, greater<pair<T, int>>> Q;
	dist[s] = (T)0;
	Q.emplace(dist[s], s);
	while (!Q.empty()) {
		pair<T, int> p = Q.top();
		Q.pop();
		int v = p.second;
		if (dist[v] < p.first)
			continue;
		for (auto &e : G[v]) {
			if (dist[e.to] > dist[v] + e.cost) {
				dist[e.to] = dist[v] + e.cost;
				prev[e.to] = v;
				Q.emplace(dist[e.to], e.to);
			}
		}
	}
	return make_pair(dist, prev);
}
//経路復元
vector<int> get_path(const vector<int> &prev, int t) {
	vector<int> path;
	for (int cur = t; cur != -1; cur = prev[cur])
		path.push_back(cur);
	reverse(path.begin(), path.end());
	return path;
}