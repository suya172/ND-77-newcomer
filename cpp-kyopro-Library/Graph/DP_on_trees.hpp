#include <vector>
#include <iostream>

using namespace std;

template<typename S, typename T, S (*merge)(S, S, T), S (*e)(), S (*add_root)(S), T (*cost_e)()>
struct DP_on_trees {
    struct edge {
        int to;
        T cost;
        edge(int t, T c) : to(t), cost(c) {}
    };
    using Graph = vector<vector<edge>>;
    vector<S> dp;
    Graph G;
    DP_on_trees(int N) : G(N) {
        dp.resize(N, e());
    }
    /**
     * @brief 有向辺の追加
     */
    void add_edge(int u, int v, T c) {
        G[u].emplace_back(edge(v, c));
    }
    /**
     * @brief DFSをする
     * 
     * @param v 始点
     * @param p 頂点vの親
     */
    void dfs(int v, int p = -1) {
        S dp_cum = e();
        int deg = G[v].size();
        for (int i = 0; i < deg; i++) {
            int u = G[v][i].to;
            if (u == p) continue;
            dfs(u, v);
            dp_cum = merge(dp_cum, dp[u], G[v][i].cost);
        }
        dp[v] = add_root(dp_cum);
    }
    /**
     * @brief dp配列の構築
     * 
     * @param s 根
     */
    void build(int s = 0) {
        dfs(s);
    }
    S operator[](int i) const {
        return dp[i];
    }
    friend ostream &operator<<(ostream &os, const DP_on_trees &r) {
        for (int i = 0; i < r.dp.size(); i++) {
            os << r.dp[i] << (i < r.dp.size() - 1 ? " " : "");
        }
        return os;
    }
};