#include <ccomplex>
#include <cmath>
#include <algorithm>
#include <vector>

namespace geom{
    using namespace std;
    using D = long double;
    using point = complex<D>;
    const D EPS = 1e-7;
    const D PI = acos(D(-1));    

    /**
     * @brief 誤差を考慮した等号
     */
    inline bool equal(const D &a, const D &b) {
        return fabs(a - b) < EPS;
    }

    /**
     * @brief 単位ベクトル
     */
    point unitVec(const point &a) {
        return a / abs(a);
    }

    /**
     * @brief 法線ベクトル
     */
    point normalVec(const point &a) {
        return a * point(0, -1);
    }

    /**
     * @brief 内積
     */
    D dot(const point &a, const point &b) {
        return (a.real() * b.real() + a.imag() * b.imag());
    }

    /**
     * @brief 外積のz要素
     */
    D cross(const point &a, const point &b) {
        return (a.real() * b.imag() - a.imag() * b.real());
    }

    /**
     * @brief 反時計周りに theta 回転
     */
    point rotate(const point &p, const D &theta) {
        return point(cos(theta) * p.real() - sin(theta) * p.imag(), sin(theta) * p.real() + cos(theta) * p.imag());
    }

    /**
     * @brief 反時計回りに90度回転
     */
    point rotate_90(const point &p) {
        return point(-p.imag(), p.real());
    }

    /**
     * @brief 弧度法から度数法
     */
    D radian_to_degree(const D &d) {
        return d * 180.0 / PI;
    }

    /**
     * @brief 度数法から弧度法
     */
    D degree_to_radian(const D &d) {
        return d * PI / 180.0;
    }

    /**
     * @brief 直線
     */
    struct Line {
        point a, b;
        Line() = default;
        /**
         * @brief a, bを通る直線
         */
        Line(point a, point b) : a(a), b(b) {}
        /**
         * @brief Ax + By + C = 0 の直線
         */
        Line(D A, D B, D C) {
            C = -C;
            if (equal(A, 0)) {
                a = point(0, C / B);
                b = point(1, C / B);
            } else if (equal(B, 0)) {
                a = point(C / A, 0);
                b = point(C / A, 1);
            } else {
                a = point(0, C / B);
                b = point(C / A, 0);
            }
        }
    };

    /**
     * @brief 線分
     */
    struct Segment : Line {
        Segment() = default;
        Segment(point a, point b) : Line(a, b) {}
        /**
         * @brief 線分の長さ
         */
        D dist() {
            return abs(a - b);
        }
    };
    
    /**
     * @brief 円
     */
    struct Circle {
        point p;
        D r;
        Circle() = default;
        Circle(point p, D r) : p(p), r(r) {}
    };
    
    /**
     * @brief 2直線が直行するか
     */
    bool orthogonal(const Line &a, const Line &b) {
        return equal(dot(a.b - a.a, b.b - b.a), 0);
    }

    /**
     * @brief 2直線が平行であるか
     */
    bool parallel(const Line &a, const Line &b) {
        return equal(cross(a.b - a.a, b.b - b.a), 0);
    }

    /**
     * @brief 点が直線上にあるかどうか
     */
    bool isPointOnLine(const point &a, const Line &l) {
        return parallel(Line(a, l.a), Line(a, l.b));
    }

    /**
     * @brief 点が線分上にあるかどうか
     */
    bool isPointOnSegment(const point &a, const Segment &l) {
        return (abs(l.a - a) + abs(l.b - a) < abs(l.a - l.b) + EPS);
    }

    /**
     * @brief 点と直線の距離
     */
    D distance_Line_Point(const Line &l, const point &p) {
        return abs(cross(l.b - l.a, p - l.a)) / abs(l.b - l.a);
    }

    /**
     * @brief 点と線分の距離
     */
    D distance_Segment_Point(const Segment &l, const point &p) {
        if(dot(l.b - l.a, p - l.a) < EPS)
            return abs(p - l.a);
        if(dot(l.a - l.b, p - l.b) < EPS)
            return abs(p - l.b);
        return abs(cross(l.b - l.a, p - l.a)) / abs(l.b - l.a);
    }

    /**
     * @brief 2直線の交点
     */
    point CrossPoint(const Line &s, const Line &t) {
        D d1 = cross(s.b - s.a, t.b - t.a);
        D d2 = cross(s.b - s.a, s.b - t.a);
        if (equal(abs(d1), 0) && equal(abs(d2), 0)) return t.a;
        return t.a + (t.b - t.a) * (d2 / d1);
    }

    const int COUNTER_CLOCKWISE = 1;
    const int CLOCKWISE = -1;
    const int ONLINE_BACK = 2;
    const int ONLINE_FRONT = -2;
    const int ON_SEGMENT = 0;
    /**
     * @brief 点p0, p1, p2 の位置関係
     *
     * @return int 1: 反時計回り, -1: 時計回り, 2: c, a, bの順で同一直線上, -2: a, b, cの順で同一直線上, 0: cが線分a, b上に存在
     */
    int ccw(point &p0, point &p1, point &p2)
    {
        point a = p1 - p0;
        point b = p2 - p0;
        if (cross(a, b) > EPS)
            return COUNTER_CLOCKWISE;
        if (cross(a, b) < -EPS)
            return CLOCKWISE;
        if (dot(a, b) < 0)
            return ONLINE_BACK;
        if (norm(a) < norm(b))
            return ONLINE_FRONT;
        return ON_SEGMENT;
    }

    /**
     * @brief 線分s, tが交差するか
     * @param bound 端点を含むか
     */
    bool intersect(Segment &s, Segment &t, bool bound = true) {
        return ccw(s.a, s.b, t.a) * ccw(s.a, s.b, t.b) < bound && ccw(t.a, t.b, s.a) * ccw(t.a, t.b, s.b) < bound;
    }

    /**
     * @brief 2線分の距離
     */
    D distance_Segment_Segment(Segment &s, Segment &t) {
        if (intersect(s, t)) return D(0);
        D ans = distance_Segment_Point(s, t.a);
        ans = min(ans, distance_Segment_Point(s, t.b));
        ans = min(ans, distance_Segment_Point(t, s.a));
        ans = min(ans, distance_Segment_Point(t, s.b));
        return ans;
    }

    /**
     * @brief 垂線の足
     */
    point projection(const Line &l, const point &p) {
        D t = dot(p - l.a, l.a - l.b) / norm(l.a - l.b);
        return l.a + (l.a - l.b) * t;
    }
    point projection(const Segment &l, const point &p) {
        D t = dot(p - l.a, l.a - l.b) / norm(l.a - l.b);
        return l.a + (l.a - l.b) * t;
    }

    /**
     * @brief lを軸としてpを対称移動させた点
     */
    point reflection(const Line &l, const point &p) {
        return p + (projection(l, p) - p) * D(2);
    }

    /**
     * @brief 2円の関係
     * @return int 共通接線の個数, 0: 内包, 1: 内接, 2: 2点で交わる, 3: 外接, 4: 交点を持たない
     */
    int intersect(const Circle &a, const Circle &b) {
        D d = abs(a.p - b.p);
        if (d > a.r + b.r + EPS) return 4;
        if (equal(d, a.r + b.r)) return 3;
        if (equal(d, abs(a.r - b.r))) return 1;
        if (d < abs(a.r - b.r) - EPS) return 0;
        return 2;
    }

    /**
     * @brief 2円の交点
     */
    vector<point> CrossPoint(const Circle &a, const Circle &b) {
        vector<point> res;
        int mode = intersect(a, b);
        D d = abs(a.p - b.p);
        if (mode == 4) return res;
        if (mode == 0) return res;
        if (mode == 3) {
            D t = a.r / (a.r + b.r);
            res.emplace_back(a.p + (b.p - a.p) * t);
            return res;
        }
        if (mode == 1) {
            if (b.r < a.r - EPS) {
                res.emplace_back(a.p + (b.p - a.p) * (a.r / d));
            } else {
                res.emplace_back(b.p + (a.p - b.p) * (b.r / d));
            }
            return res;
        }
        D rc1 = (a.r * a.r + d * d - b.r * b.r) / (2 * d);
        D rs1 = sqrt(a.r * a.r - rc1 * rc1);
        if (a.r - abs(rc1) < EPS) rs1 = 0;
        point e12 = (b.p - a.p) / abs(b.p - a.p);
        res.emplace_back(a.p + rc1 * e12 + rs1 * e12 * point(0, 1));
        res.emplace_back(a.p + rc1 * e12 + rs1 * e12 * point(0, -1));
        return res;
    }

    /**
     * @brief 点が円の内部(円周上含む)に含まれるか
     */
    bool inCircle(const Circle &C, const point &p) {
        D d = abs(C.p - p);
        return (equal(d, C.r) || d < C.r - EPS);
    }

    /**
     * @brief 直線と円の交点 
     */
    vector<point> CrossPoint(const Line &l, const Circle &c) {
        vector<point> res;
        D d = distance_Line_Point(l, c.p);
        if (d > c.r + EPS) return res;
        point h = projection(l, c.p);
        if (equal(d, c.r)) {
            res.emplace_back(h);
            return res;
        }
        point e = unitVec(l.b - l.a);
        D ph = sqrt(c.r * c.r - d * d);
        res.emplace_back(h - e * ph);
        res.emplace_back(h + e * ph);
        return res;
    }

    /**
     * @brief 点pを通って円cに接する接線の接点
     */
    vector<point> tangentPoint(const point &p, const Circle &c) {
        return CrossPoint(c, Circle(p, sqrt(norm(c.p - p) - c.r * c.r)));
    }

    /**
     * @brief 2円の共通接線 
     */
    vector<Line> commonTangentLine(const Circle &a, const Circle &b) {
        vector<Line> res;
        D g = abs(a.p - b.p);
        if (equal(g, 0)) return res;
        point u = unitVec(b.p - a.p);
        point v = rotate(u, PI / 2);
        for (auto &s : {-1, 1}) {
            D h = (a.r + b.r * s) / g;
            if (equal(h * h, 1)) {
                res.emplace_back(Line(a.p + (h > 0 ? u : -u) * a.r, a.p + (h > 0 ? u : -u) * a.r + v));
            } else if (1 - h * h > 0) {
                point U = u * h, V = v * sqrt(1 - h * h);
                res.emplace_back(Line(a.p + (U + V) * a.r, b.p - (U + V) * (b.r * s)));
                res.emplace_back(Line(a.p + (U - V) * a.r, b.p - (U - V) * (b.r * s)));
            }
        }
        return res;
    }

    /**
     * @brief 内接円
     */
    Circle Inscribed_Circle(point &a, point &b, point &c) {
        D A = abs(b - c), B = abs(a - c), C = abs(a - b);
        point p(A * real(a) + B * real(b) + C * real(c), A * imag(a) + B * imag(b) + C * imag(c));
        p /= (A + B + C);
        D r = distance_Line_Point(Line(a, b), p);
        return Circle(p, r);
    }

    /**
     * @brief 3点を通る円 (3角形の外接円)
     */
    Circle Circumscribed_Circle(point &a, point &b, point &c) {
        Line s((a + b) / D(2), (a + b) / D(2) + rotate_90(b - a));
        Line t((b + c) / D(2), (b + c) / D(2) + rotate_90(c - b));
        point v = CrossPoint(s, t);
        return Circle(v, abs(v - a));
    }

    using Polygon = vector<point>;

    /**
     * @brief 面積
     */
    D area(const Polygon &p) {
        D res = 0;
        int n = p.size();
        for (int i = 0; i < n - 1; i++) {
            res += cross(p[i], p[i + 1]);
        }
        res += cross(p[n - 1], p[0]);
        return res / D(2);
    }
    D area(const Circle &c) {
        return PI * c.r * c.r;
    }

    /**
     * @brief 多角形が凸かどうか
     */
    bool convex(Polygon &p) {
        int n = p.size();
        int now, pre, nxt;
        for (int i = 0; i < n; i++) {
            pre = (i - 1 + n) % n;
            nxt = (i + 1) % n;
            now = i;
            if (ccw(p[pre], p[now], p[nxt]) == -1) {
                return false;
            }
        }
        return true;
    }

    /**
     * @brief 凸包
     * @param mode 1直線上の3点を含めるか
     */
    Polygon ConvexHull(vector<point> &p, bool mode = false) {
        int n = p.size(), k = 0;
        int u = (mode ? -1 : 1);
        sort(p.begin(), p.end(), [](const point &a, const point &b) {
            return (a.real() != b.real() ? a.real() < b.real() : a.imag () < b.imag());
        });
        vector<point> ch(2 * n);
        for (int i = 0; i < n; ch[k++] = p[i++]) {
            while (k >= 2 && cross(ch[k - 1] - ch[k - 2], p[i] - ch[k - 1]) < u * EPS) {
                k--;
            }
        }
        for (int i = n - 2, t = k + 1; i >= 0; ch[k++] = p[i--]) {
            while (k >= t && cross(ch[k - 1] - ch[k - 2], p[i] - ch[k - 1]) < u * EPS) {
                k--;
            }
        }
        ch.resize(k - 1);
        return ch;
    }

    const int OUT = 0;
    const int ON = 1;
    const int IN = 2;
    /**
     * @brief 点が多角形に含まれるか
     * @return int 0: 含まれない, 1: 辺上に存在, 2: 含まれる
     */
    int contain(const Polygon &g, point &p) {
        bool in = false;
        int n = g.size();
        for (int i = 0; i < n; i++) {
            point a = g[i] - p, b = g[(i + 1) % n] - p;
            if (a.imag() > b.imag()) swap(a, b);
            if (a.imag() <= EPS && EPS < b.imag() && cross(a, b) < -EPS) in = !in;
            if (equal(cross(a, b), 0) && dot(a, b) <= 0) return ON;
        }
        return (in ? IN : OUT);
    }

    /**
     * @brief 多角形p を直線l で切断した左側の頂点集合
     */
    vector<point> convexCut(Polygon &p, Line &l) {
        vector<point> res;
        int n = p.size();
        for (int i = 0; i < n; i++) {
            point now = p[i];
            point nxt = p[(i + 1) % n];
            if (ccw(l.a, l.b, now) != CLOCKWISE) res.emplace_back(now);
            if (ccw(l.a, l.b, now) * ccw(l.a, l.b, nxt) < 0) {
                res.emplace_back(CrossPoint(Line(now, nxt), l));
            }
        }
        return res;
    }

    /**
     * @brief 凸多角形の直径
     */
    D convex_Diameter(Polygon &g) {
        int n = g.size();
        int is = 0, js = 0;
        for (int i = 1; i < n; i++) {
            if (g[i].imag() > g[is].imag()) is = i;
            if (g[i].imag() < g[js].imag()) js = i;
        }
        D maxdis = norm(g[is] - g[js]);
        int maxi, maxj, i, j;
        i = maxi = is;
        j = maxj = js;
        do {
            if (cross(g[(i + 1) % n] - g[i], g[(j + 1) % n] - g[j]) >= 0) {
                j = (j + 1) % n;
            } else {
                i = (i + 1) % n;
            }
            if (norm(g[i] - g[j]) > maxdis) {
                maxdis = norm(g[i] - g[j]);
                maxi = i;
                maxj = j;
            }
        } while (i != is || j != js);
        return sqrt(maxdis);
    }

    /**
     * @brief 最近点対の距離
     */
    D closest_pair(vector<point> &ps) {
        if (ps.size() <= 1) throw(0);
        sort(ps.begin(), ps.end(), [](const point &a, const point &b) {
            return (a.real() != b.real() ? a.real() < b.real() : a.imag() < b.imag());
        });
        auto comp_y = [&](const point &a, const point &b) {
            return a.imag() < b.imag();
        };
        vector<point> beet(ps.size());
        const D INF = 1e18;
        function<D(int, int)> rec = [&](int l, int r) {
            if (r - l <= 1) return INF;
            int mid = (l + r) >> 1;
            auto x = ps[mid].real();
            auto ret = min(rec(l, mid), rec(mid, r));
            inplace_merge(ps.begin() + l, ps.begin() + mid, ps.begin() + r, comp_y);
            int ptr = 0;
            for (int i = l; i < r; i++) {
                if (abs(ps[i].real() - x) >= ret) continue;
                for (int j = 0; j < ptr; j++) {
                    auto luz = ps[i] - beet[ptr - j - 1];
                    if (luz.imag() >= ret) break;
                    ret = min(ret, abs(luz));
                }
                beet[ptr++] = ps[i];
            }
            return ret;
        };
        return rec(0, (int)ps.size());
    }

    /**
     * @brief 偏角ソートの比較関数 (-π ≤ arg ≤ π)
     */
    bool Declination_comp(point &a, point &b) {
        return arg(a) < arg(b);
    }

    /**
     * @brief 点のソートの比較関数
     */
    bool Point_comp(point &a, point &b) {
        return (a.real() != b.real() ? a.imag() < b.imag() : a.real() < b.real());
    }

    /**
     * @brief 直線の重複を取り除く
     */
    vector<Line> merge(vector<Line> L) {
        auto comp = [](Line &a, Line &b) {
            point l = a.b - a.a;
            point m = b.b - b.a;
            if (l.real() < 0)
                l *= -1;
            if (m.real() < 0)
                m *= -1;
            if (equal(a.a.real(), a.b.real()) && l.imag() > -EPS)
                l *= -1;
            if (equal(b.a.real(), b.b.real()) && m.imag() > -EPS)
                m *= -1;
            return Declination_comp(l, m);
        };
        vector<Line> ans;
        vector<bool> ok(L.size(), true);
        sort(L.begin(), L.end(), comp);
        for (int i = 0; i < L.size(); i++) {
            if (!ok[i]) continue;
            ans.emplace_back(L[i]);
            for (int j = i + 1; j < L.size(); j++) {
                point l = L[i].b - L[i].a;
                point m = L[j].b - L[j].a;
                if (l.real() < 0)
                    l *= -1;
                if (m.real() < 0)
                    m *= -1;
                if (equal(L[i].a.real(), L[i].b.real()) && l.imag() > -EPS)
                    l *= -1;
                if (equal(L[j].a.real(), L[j].b.real()) && m.imag() > -EPS)
                    m *= -1;
                if (!equal(arg(l), arg(m)))
                    break;
                if (!ok[j]) continue;
                if (parallel(L[i], L[j]) && isPointOnLine(L[i].a, L[j])) {
                    ok[j] = false;
                }
            }
        }
        return ans;
    }

    inline ostream &operator<<(ostream &os, const point &p) {
        os << '(' << p.real() << ',' << p.imag() << ')';
        return os;
    }

    inline ostream &operator<<(ostream &os, const Line &l) {
        os << l.a << " to " << l.b;
        return os;
    }

    inline ostream &operator<<(ostream &os, const Segment &l) {
        os << Line(l);
        return os;
    }

    inline ostream &operator<<(ostream &os, const Circle &c) {
        os << "center:" << c.p << " radius:" << c.r; 
        return os;
    }

    inline ostream &operator<<(ostream &os, const Polygon &p) {
        int n = p.size();
        for (int i = 0; i < n; i++) {
            os << p[i] << ',';
        }
        return os;
    }
}