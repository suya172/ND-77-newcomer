#include <bits/stdc++.h>
#include <sys/time.h>
#include <atcoder/all>

using namespace std;
using namespace atcoder;

using ll = long long;
using ull = unsigned long long;
using ld = long double;
using vi = vector<int>;
using vvi = vector<vi>;
using vvvi = vector<vvi>;
using vl = vector<long>;
using vvl = vector<vl>;
using vll = vector<ll>;
using vvll = vector<vll>;
using vvvll = vector<vvll>;
using vb = vector<bool>;
using vvb = vector<vb>;
using pii = pair<int, int>;
using pll = pair<ll, ll>;
using vpii = vector<pii>;
using vpll = vector<pll>;
using vstr = vector<string>;
constexpr ll INF_LL=5e18;
constexpr int INF_I=1LL<<30;
constexpr ll inf = 1e12 + 7;
#define rep1(i,n) for(int i=0; i<((int)(n)); i++)
#define reps(i,n) for(int i=1; i<=((int)(n)); i++)
#define rep3(i, a, b) for (int i = a; i < b; i++)
#define rep4(i, a, b, c) for (int i = a; i < b; i += c)
#define overload4(a, b, c, d, e, ...) e
#define rep(...) overload4(__VA_ARGS__, rep4, rep3, rep1)(__VA_ARGS__)
#define vector_cin(x) for(auto &n : (x)) cin >> n
#define ALL(x) (x).begin(), (x).end()
#define YesNo(x) ((x) ? "Yes": "No")
#define pb emplace_back
inline void to_lower(const std::string::iterator &begin, const std::string::iterator &end) {transform(begin, end, begin, ::tolower);}
inline void to_upper(const std::string::iterator &begin, const std::string::iterator &end) {transform(begin, end, begin, ::toupper);}
#define mp make_pair
#define mt make_tuple
template <class... T>
constexpr auto min(T... a) {
return min(initializer_list<common_type_t<T...>>{a...});
}

template <class... T>
constexpr auto max(T... a) {
return max(initializer_list<common_type_t<T...>>{a...});
}
template <typename T>
bool chmax(T &a, const T& b) {if (a < b){a = b;return true;}return false;}

template <typename T>
bool chmin(T &a, const T& b) {if (a > b){a = b;return true;}return false;}
ll ceilint(ll x, ll y) {return (x + y - 1) / y;}
void Main();
int main() {std::cin.tie(nullptr);std::ios_base::sync_with_stdio(false);std::cout << std::fixed << std::setprecision(15);Main();return 0;}

template <typename T1, typename T2>
ostream &operator<<(ostream &os, const pair<T1, T2> &p) { os << "(" << p.first << "," << p.second << ")"; return os; }
template <typename T1, typename T2>
istream &operator>>(istream &is, pair<T1, T2> &p) { is >> p.first >> p.second; return is; }
template <typename T>
ostream &operator<<(ostream &os, const vector<T> &v) { for (int i = 0; i < (int)v.size(); i++) { os << v[i] << (i + 1 != (int)v.size() ? " ": "");}return os;}
template <typename T>
ostream &operator<<(ostream &os, const vector<vector<T>> &v) { for (int i = 0; i < (int)v.size(); i++) { os << v[i] << endl;} return os;}
template <typename T>
ostream &operator<<(ostream &os, const vector<vector<vector<T>>> &v) { for (int i = 0; i < (int)v.size(); i++) { os << "i = " << i << endl; os << v[i];}return os;}
template <typename T>
istream &operator>>(istream &is, vector<T> &v) { for (T &in : v) is >> in; return is; }
template <typename T, typename S>
ostream &operator<<(ostream &os, const map<T, S> &mp) { for (auto &[key, val] : mp) { os << key << ":" << val << " ";} return os;}
template <typename T>
ostream &operator<<(ostream &os, const set<T> &st) { auto itr = st.begin(); for (int i = 0; i < (int)st.size(); i++) {os << *itr << (i + 1 != (int)st.size() ? " ": "");itr++;}return os;}
template <typename T>
ostream &operator<<(ostream &os, const multiset<T> &st){ auto itr = st.begin(); for (int i = 0; i < (int)st.size(); i++) { os << *itr << (i + 1 != (int)st.size() ? " ": "");itr++;}return os;}
template <typename T>
ostream &operator<<(ostream &os, queue<T> q){ while (q.size()) { os << q.front() << " ";q.pop(); }return os;}
template <typename T>
ostream &operator<<(ostream &os, deque<T> q) { while (q.size()) { os << q.front() << " "; q.pop_front();} return os;}
template <typename T>
ostream &operator<<(ostream &os, stack<T> st) { while (st.size()){ os << st.top() << " "; st.pop();} return os;}
template <class T, class Container, class Compare>
ostream &operator<<(ostream &os, priority_queue<T, Container, Compare> pq) { while (pq.size()) {os << pq.top() << " ";pq.pop();}return os;}
namespace debug {
    void dump_init(const source_location location = std::source_location::current()) {
        cerr << "\033[32m[dump] \033[m\033[36m" << location.file_name() << ":" << location.line() << ":" << location.function_name() << "\033[m ";
    }
    template <typename T>
    void dump(const T a, const string label = "", const source_location location = source_location::current()) {
            dump_init(location);
            if (label == "") {
                cerr << a << endl;
                return;
            }
        cerr << label << " : " << a << endl;
    }
}
#ifdef __LOCAL
#define debug(...) debug::dump(__VA_ARGS__, #__VA_ARGS__)
#else
#define debug(...) void(0);
#endif