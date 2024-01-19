#include <vector>
#include <stack>
#include <cassert>

using namespace std;

using vi = vector<int>;
using pii = pair<int, int>;

struct RollbackUnionFind {
    vi par;
    stack<pii> hist;
    int inner_snap;
    RollbackUnionFind(int n) : inner_snap(0) {
        par.assign(n, -1);
    }
    int leader(int x) {
        if (par[x] < 0) return x;
        else return leader(par[x]);
    }
    bool merge(int x, int y) {
        x = leader(x);
        y = leader(y);
        hist.emplace(x, par[x]);
        hist.emplace(y, par[y]);
        if (x == y) return false;
        if (par[x] > par[y]) swap(x, y);
        par[x] += par[y];
        par[y] = x;
        return true;
    }
    bool same(int x, int y) {
        return leader(x) == leader(y);
    }
    int size(int x) {
        return -par[leader(x)];
    }
    void undo() {
        par[hist.top().first] = hist.top().second;
        hist.pop();
        par[hist.top().first] = hist.top().second;
        hist.pop();
    }
    void snap() {
        inner_snap = int(hist.size() >> 1);
    }
    int get_state() {
        return int(hist.size() >> 1);
    }
    void rollback(int state = -1) {
        if (state == -1) state = inner_snap;
        state <<= 1;
        assert(state <= (int)hist.size());
        while (state < (int)hist.size()) {
            undo();
        }
    }
};