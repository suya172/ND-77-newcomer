#include <iostream>
#include <vector>

using namespace std;

/**
 * @brief 重み付きunion find
 * 
 * @tparam T 重みの型
 */
template<class T>
struct Weighted_UnionFind {
    vector<int> par;
    vector<int> rank;
    vector<T> diff_weight;
    /**
     * @brief Construct a new Weighted_UnionFind object
     * 
     * @param n 要素数
     * @param e 重みの単位元
     */
    Weighted_UnionFind(int n = 1, T e = 0) {
        par.resize(n);
        rank.resize(n);
        diff_weight.resize(n);
        for (int i = 0; i < n; i++) {
            par[i] = i;
            rank[i] = 0;
            diff_weight[i] = e;
        }
    }
    /**
     * @brief 要素 x の根を求める
     */
    int leader(int x) {
        if (par[x] == x) {
            return x;
        } else {
            int r = root(par[x]);
            diff_weight[x] += diff_weight[par[x]];
            return par[x] = r; 
        }
    }
    /**
     * @brief 要素 x の重みを求める
     */
    T weight(int x) {
        leader(x);
        return diff_weight[x];
    }
    /**
     * @brief 要素 a と要素 b が同じ集合に存在するか
     */
    bool same(int a, int b) {
        return leader(a) == leader(b);
    }
    /**
     * @brief 要素 x と要素 y を重み w で併合する (weight(y) = weight(x) + w)
     */
    bool merge(int x, int y, T w) {
        w += weight(x);
        w -= weight(y);
        x = leader(x);
        y = leader(y);
        if (x == y) return false;
        if (rank[x] < rank[y]) {
            swap(x, y);
            w = -w;
        }
        if (rank[x] == rank[y]) {
            rank[x]++;
        }
        par[y] = x;
        diff_weight[y] = w;
        return true;
    }
    /**
     * @brief 要素 x と要素 y の重みの差 (xとyが同じ集合に属することが前提)
     * @return T weight(y) - weight(x)
     */
    T diff(int x, int y) {
        assert(leader(x) != leader(y));
        return weight(y) - weight(x);
    }
};
