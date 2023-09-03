#include <vector>
#include <queue>

using namespace std;

/**
 * @brief トポロジカルソート O(V + E) (E := 辺の本数, V := 頂点の個数)
 * 
 * @param G グラフ
 * @param indegree 入次数
 * @param V 頂点数
 * @return vector<int> トポロジカル順のうち昇順で一番はじめのもの(G が DAG でなければ {-1} を返す)
 */
vector<int> topological_sort(vector<vector<int>> &G, vector<int> &indegree, int V) {
	priority_queue<int, vector<int>, greater<>> Q;
	vector<bool> seen(V, false);
	vector<int> order;
	order.clear();
	for (int i =0; i < V; i++)
		if (indegree[i] == 0)
			Q.push(i);
	while (!Q.empty()) {
		int v = Q.top();
		Q.pop();
		seen[v] = true;
		order.push_back(v);
		for (auto next : G[v]) {
			if (seen[next])
				continue;
			indegree[next]--;
			if (indegree[next] == 0)
				Q.push(next);
		}
	}
	bool flag = false;
	for (int i = 0; i < V; i++)
		if (indegree[i] != 0)
			flag = true;
	if (flag)
		return {-1};
	else
		return order;
}