#include <vector>
#include <queue>

using namespace std;

// DAGをトポロジカルソートする(いくつかある中で昇順で一番初めのものを返す) G := Graph, indegree := 入次数, V := 頂点数
vector<int> topological_sort(vector<vector<int>> &G, vector<int> &indegree, int V) {
	priority_queue<int, vector<int>, greater<>> Q; //降順プライオリティキュー
	vector<bool> seen(V, false);
	vector<int> order;
	order.clear();
	for (int i =0; i < V; i++)
		if (indegree[i] == 0)//入次数が0
			Q.push(i);
	while (!Q.empty()) {
		int v = Q.top();
		Q.pop();
		seen[v] = true;
		order.push_back(v);
		for (auto next : G[v]) {
			if (seen[next])
				continue;
			indegree[next]--;//辺を取り除く
			if (indegree[next] == 0)//入次数が0になった
				Q.push(next);
		}
	}
	bool flag = false;
	for (int i = 0; i < V; i++)
		if (indegree[i] != 0)
			flag = true; //DAGではない
	if (flag)
		//DAGではない時は-1のみの配列を返す
		return {-1};
	else
		//トポロジカルソート順(いくつかある中で昇順で一番初めのものを返す)
		return order;
}