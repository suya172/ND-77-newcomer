#include <iostream>
#include <vector>

using namespace std;

/**
 * @brief 全方位木dp
 * 
 * @tparam S dp配列の型
 * @tparam T 辺の重みの型
 * @tparam (*merge)(S, S, T) Sに対する二項演算(Tはその辺の重み)
 * @tparam (*e)() 二項演算mergeの単位元
 * @tparam (*add_root)(S) mergeしてまとめたdp配列の値から、新たな部分木に対してdp配列の値を求める
 * @tparam (*cost_e)() 二項演算mergeに与えるTについての単位元
 */
template<typename S, typename T, S (*merge)(S, S, T), S (*e)(), S (*add_root)(S), T (*cost_e)()>
struct Rerooting {
    struct edge {
        int to;
        T cost;
        edge(int t, T c) : to(t), cost(c) {}
    };
    using Graph = vector<vector<edge>>;
    vector<vector<S>> dp;
    vector<S> ans;
    Graph G;
    Rerooting(int N) : G(N) {
        dp.resize(N);
        ans.assign(N, e());
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
    S dfs(int v, int p = -1) {
        S dp_cum = e();
        int deg = G[v].size();
        dp[v] = vector<S>(deg, e());
        for (int i = 0; i < deg; i++) {
            int u = G[v][i].to;
            if (u == p) continue;
            dp[v][i] = dfs(u, v);
            dp_cum = merge(dp_cum, dp[v][i], G[v][i].cost);
        }
        return add_root(dp_cum);
    }
    /**
     * @brief BFSをする
     * 
     * @param v 始点
     * @param dp_p 計算を始める時点でのDP配列の値
     * @param p 頂点vの親
     */
    void bfs(int v, const S &dp_p, int p = -1) {
        int deg = G[v].size();
        for (int i = 0; i < deg; i++) {
            if (G[v][i].to == p) dp[v][i] = dp_p;
        }
        vector<S> dp_l(deg + 1, e()), dp_r(deg + 1, e());
        for (int i = 0; i < deg; i++) {
            dp_l[i + 1] = merge(dp_l[i], dp[v][i], G[v][i].cost);
        }
        for (int i = deg - 1; i >= 0; i--) {
            dp_r[i] = merge(dp_r[i + 1], dp[v][i], G[v][i].cost);
        }
        ans[v] = add_root(dp_l[deg]);
        for (int i = 0; i < deg; i++) {
            int u = G[v][i].to;
            if (u == p) continue;
            bfs(u, add_root(merge(dp_l[i], dp_r[i + 1], cost_e())), v);
        }
    }
    /**
     * @brief dp配列の構築
     * 
     * @param s 根
     */
    void build(int s = 0) {
        dfs(s);
        bfs(s, e());
    }
    S operator[](int i) const {
        return ans[i];
    }
    friend ostream &operator<<(ostream &os, const Rerooting &r) {
        for (int i = 0; i < r.ans.size(); i++) {
            os << r.ans[i] << (i < r.ans.size() - 1 ? " " : "");
        }
        return os;
    }
};