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

    /**
     * @brief 点a, b, c の位置関係
     * 
     * @return int 1: 反時計回り, -1: 時計回り, 2: c, a, bの順で同一直線上, -2: a, b, cの順で同一直線上, 0: cが線分a, b上に存在
     */
    int ccw(const point &a, point &b, point &c) {
        b -= a;
        c -= a;
        if (cross(b, c) > EPS) return 1;
        if (cross(b, c) < -EPS) return -1;
        if (dot(b, c) < 0) return 2;
        if (norm(b) < norm(c)) return -2;
        return 0;
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
     * @return int 0: 内包, 1: 内接, 2: 2点で交わる, 3: 外接, 4: 交点を持たない
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
     * @brief 3点を通る円 (3角形の外接円)
     */
    Circle Circumscribed_Circle(point &a, point &b, point &c) {
        Line s((a + b) / D(2), (a + b) / D(2) + rotate_90(b - a));
        Line t((b + c) / D(2), (b + c) / D(2) + rotate_90(c - b));
        point v = CrossPoint(s, t);
        return Circle(v, abs(v - a));
    }
}