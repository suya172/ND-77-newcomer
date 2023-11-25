#include <iostream>
#include <set>

using namespace std;
using ll = long long;
using pll = pair<ll, ll>;

struct range_set {
    set<pll> s;
    const ll INF = 5e18;
    range_set() {
        s.emplace(INF, INF);
        s.emplace(-INF, -INF);
    }

    bool contains(ll x) const {
        auto it = prev(s.lower_bound(make_pair(x + 1, x + 1)));
        auto [l, u] = *it;
        return l <= x && x <= u;
    }

    bool insert(ll x) {
        auto nit = s.lower_bound(make_pair(x + 1, x + 1));
        auto it = prev(nit);
        auto [l, u] = *it;
        auto [nl, nu] = *nit;
        if (l <= x && x <= u)
            return false;
        if (u == x - 1) {
            if (nl == x + 1) {
                s.erase(it);
                s.erase(nit);
                s.emplace(l, nu);
            } else {
                s.erase(it);
                s.emplace(l, x);
            }
        } else {
            if (nl == x + 1) {
                s.erase(nit);
                s.emplace(x, nu);
            } else {
                s.emplace(x, x);
            }
        }
        return true;
    }

    bool erase(ll x) {
        auto it = prev(s.lower_bound(make_pair(x + 1, x + 1)));
        auto [l, u] = *it;
        if (l < x && x < u) {
            s.erase(it);
            s.emplace(l, x - 1);
            s.emplace(x + 1, u);
            return true;
        }
        if (l == x) {
            s.erase(it);
            if (x == u) return true;
            s.emplace(x + 1, u);
            return true;
        }
        if (u == x) {
            s.erase(it);
            if (x == l) return true;
            s.emplace(l, x - 1);
            return true;
        }
        return false;
    }

    int mex(ll x = 0) const {
        auto [l, u] = *prev(s.lower_bound(make_pair(x + 1, x + 1)));
        if (l <= x && x <= u) {
            return u + 1;
        } else {
            return x;
        }
    }

    friend ostream &operator<<(ostream &os, const range_set &ss) {
        for (auto &p : ss.s) {
            os << "[" << p.first << "," << p.second + 1 << ")" << " ";
        }
    }
};