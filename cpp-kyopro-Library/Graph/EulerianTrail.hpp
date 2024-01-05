#include <vector>

using namespace std;
using ll = long long;
using vll = vector<ll>;
using vvll = vector<vll>;
using vb = vector<bool>;
using Graph = vvll;

struct EulerianTrail {
    Graph G;
    vll order;
    ll root;
    ll N;

    void dfs(vb &seen, ll now) {
        seen[now] = true;
        for (auto &next : G[now]) {
            if (seen[next]) continue;
            order.emplace_back(next);
            dfs(seen, next);
            order.emplace_back(now);
        }
    }

    EulerianTrail(Graph &g, ll root = 0) : G(g), root(root) {
        order.emplace_back(root);
        N = G.size();
        vb seen(N, false);
        dfs(seen, root);
    }
};