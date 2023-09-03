#include <cmath>
#include <numeric>
#include <iostream>

using ll = long long;
using namespace std;

struct Fraction {
    ll num, den;
    /**
     * @brief 約分
     * 
     */
    void simplify() {
        ll d = gcd(abs(num), abs(den));
        num /= (den >= 0 ? d : -d);
        den /= (den >= 0 ? d : -d);
    }
    /**
     * @brief 整数から分数を構築
     * 
     * @param n 整数
     */
    Fraction(ll n = 0) : num(n), den(1) {};
    /**
     * @brief a / b の分数を構築
     * 
     * @param a 分子
     * @param b 分母
     */
    Fraction(ll a, ll b) : num(a), den(b) {
        simplify();
    };
    /**
     * @brief 出力
     */
    friend ostream &operator<<(ostream &os, const Fraction &f) {
        if (f.den == 1) {
            os << f.num;
        } else {
            os << f.num <<  '/' << f.den;
        }
        return os;
    }
    friend Fraction operator+(const Fraction &a, const Fraction &b) {
        return {a.num * b.den + b.num * a.den, a.den * b.den};
    }
    friend Fraction operator-(const Fraction &a, const Fraction &b) {
        return {a.num * b.den - b.num * a.den, a.den * b.den};
    }
    friend Fraction operator*(const Fraction &a, const Fraction &b) {
        ll gcd_tmp1 = gcd(a.num, b.den), gcd_tmp2 = gcd(b.num, a.den);
        return {(a.num / gcd_tmp1) * (b.num / gcd_tmp2), (a.den / gcd_tmp2) * (b.den / gcd_tmp1)};
    }
    friend Fraction operator/(const Fraction &a, const Fraction &b) {
        ll gcd_tmp1 = gcd(a.num, b.num), gcd_tmp2 = gcd(b.den, a.den);
        return {(b.num >= 0 ? 1 : -1) * (a.num / gcd_tmp1) * (b.den / gcd_tmp2), (b.num >= 0 ? 1 : -1) * (a.den / gcd_tmp2) * (b.num / gcd_tmp1)};
    }
    friend bool operator==(const Fraction &a, const Fraction &b) {
        return a.num == b.num && a.den == b.den;
    }
    friend bool operator!=(const Fraction &a, const Fraction &b) {
        return a.num != b.num || a.den != b.den;
    }
    friend bool operator>(const Fraction &a, const Fraction &b) {
        return a.num * b.den > b.num * a.den;
    }
    friend bool operator>=(const Fraction &a, const Fraction &b) {
        return a.num * b.den >= b.num * a.den;
    }
    friend bool operator<(const Fraction &a, const Fraction &b) {
        return a.num * b.den < b.num * a.den;
    }
    friend bool operator<=(const Fraction &a, const Fraction &b) {
        return a.num * b.den <= b.num * a.den;
    }
};
