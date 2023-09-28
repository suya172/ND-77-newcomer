#include <iostream>
#include <algorithm>

template <int MOD>
struct Static_Modint {
    static const int mod = MOD;
    unsigned int x;
    /**
     * @brief Construct a new Static_Modint object
     * 
     */
    Static_Modint() : x(0) {}
    /**
     * @brief Construct a new Static_Modint object
     * 
     * @param sig 代入する数
     */
    Static_Modint(signed int sig) {x = (sig < 0 ? sig % mod + mod : sig % mod);}
    /**
     * @brief Construct a new Static_Modint object
     * 
     * @param sig 代入する数
     */
    Static_Modint(signed long long sig) {x = (sig < 0 ? sig % mod + mod : sig % mod);}
    /**
     * @brief mod を取った値を返す
     * 
     */
    int val() const {
        return (int)x;
    }
    /**
     * @brief 累乗
     * 
     * @param n 何乗するか
     */
    Static_Modint pow(int n) const {
        long long a = x, res = 1;
	    while (n > 0) {
		    if (n & 1) res = res * a % mod;
		    a = a * a % mod;
		    n >>= 1;
	    }
	    return Static_Modint(res);
    }
    /**
     * @brief 逆元(存在しなければエラー)
     */
    Static_Modint inv() const {
        long long a = x, b = mod, u = 1, v = 0;
        while (b) {
            long long t = a / b;
            a -= t * b;
            std::swap(a, b);
            u -= t * v;
            std::swap(u, v);
        }
        return Static_Modint(u);
    }
    /**
     * @brief 代入
     */
    Static_Modint &operator=(signed long long sig) {x = (sig < 0 ? sig % mod + mod : sig % mod); return *this;}
    /**
     * @brief 代入
     */
    Static_Modint &operator=(signed long sig) {x = (sig < 0 ? sig % mod + mod : sig % mod); return *this;}
    /**
     * @brief 代入
     */
    Static_Modint &operator=(signed int sig) {x = (sig < 0 ? sig % mod + mod : sig % mod); return *this;}
    /**
     * @brief 加算代入
     */
    Static_Modint &operator+=(Static_Modint that) {if ((x += that.x) >= mod) x -= mod; return *this;}
    /**
     * @brief 加算代入
     */
    Static_Modint &operator+=(signed long long that) {Static_Modint t = that; *this += t; return *this;}
    /**
     * @brief 加算代入
     */
    Static_Modint &operator+=(signed long that) {Static_Modint t = that; *this += t; return *this;}
    /**
     * @brief 加算代入
     */
    Static_Modint &operator+=(signed int that) {Static_Modint t = that; *this += t; return *this;}
    /**
     * @brief 減算代入
     */
    Static_Modint &operator-=(Static_Modint that) {if ((x += mod - that.x) >= mod) x -= mod; return *this;}
    /**
     * @brief 減算代入
     */
    Static_Modint &operator-=(signed long long that) {Static_Modint t = that; *this -= t; return *this;}
    /**
     * @brief 減算代入
     */
    Static_Modint &operator-=(signed long that) {Static_Modint t = that; *this -= t; return *this;}
    /**
     * @brief 減算代入
     */
    Static_Modint &operator-=(signed int that) {Static_Modint t = that; *this -= t; return *this;}
    /**
     * @brief 乗算代入 
     */
    Static_Modint &operator*=(Static_Modint that) {x = (unsigned long long)x * that.x % mod; return *this;}
    /**
     * @brief 乗算代入
     */
    Static_Modint &operator*=(signed long long that) {Static_Modint t = that; *this *= t; return *this;}
    /**
     * @brief 乗算代入
     */
    Static_Modint &operator*=(signed long that) {Static_Modint t = that; *this *= t; return *this;}
    /**
     * @brief 乗算代入
     */
    Static_Modint &operator*=(signed int that) {Static_Modint t = that; *this *= t; return *this;}
    /**
     * @brief 除算代入
     */
    Static_Modint &operator/=(Static_Modint that) {return *this *= that.inverse();}
    /**
     * @brief 除算代入
     */
    Static_Modint &operator/=(signed long long that) {Static_Modint t = that; *this /= t; return *this;}
    /**
     * @brief 除算代入
     */
    Static_Modint &operator/=(signed long that) {Static_Modint t = that; *this /= t; return *this;}
    /**
     * @brief 除算代入
     */
    Static_Modint &operator/=(signed int that) {Static_Modint t = that; *this /= t; return *this;}
    /**
     * @brief 加算 
     */
    Static_Modint operator+(Static_Modint that) const {return Static_Modint(*this) += that;}
    /**
     * @brief 減算
     */
    Static_Modint operator-(Static_Modint that) const {return Static_Modint(*this) -= that;}
    /**
     * @brief 乗算
     */
    Static_Modint operator*(Static_Modint that) const {return Static_Modint(*this) *= that;}
    /**
     * @brief 除算 
     */
    Static_Modint operator/(Static_Modint that) const {return Static_Modint(*this) /= that;}
    /**
     * @brief 合同 
     */
    bool operator==(Static_Modint that) const {return x == that.x;}
    /**
     * @brief 合同でない
     */
    bool operator!=(Static_Modint that) const {return x != that.x;}
    /**
     * @brief -1倍
     */
    Static_Modint operator-() const {Static_Modint t; t.x = (x == 0 ? 0 : mod - x); return t;}
    /**
     * @brief 出力
     */
    friend std::ostream &operator<<(std::ostream &os, const Static_Modint &a) {os << a.val(); return os;}
};

using Modint998244353 = Static_Modint<998244353>;
using Modint1000000007 = Static_Modint<1000000007>;

struct Dynamic_Modint {
    int mod;
    unsigned int x;
    /**
     * @brief 法を設定する(最初に呼ぶ)
     * 
     * @param m 法
     */
    void set_mod(int m) {
        mod = m;
    }
    /**
     * @brief Construct a new Dynamic_Modint object
     */
    Dynamic_Modint() : x(0) {}
    /**
     * @brief Construct a new Dynamic_Modint object
     *
     * @param sig 代入する数
     * @param m 法
     */
    Dynamic_Modint(signed int sig, int m) {mod = m; x = (sig < 0 ? sig % mod + mod : sig % mod);}
    /**
     * @brief Construct a new Dynamic_Modint object
     *
     * @param sig 代入する数
     * @param m 法
     */
    Dynamic_Modint(signed long long sig, int m) {mod = m; x = (sig < 0 ? sig % mod + mod : sig % mod);}
    /**
     * @brief mod を取った値を返す
     */
    int val() const {
        return (int)x;
    }
    /**
     * @brief 累乗
     * 
     * @param n 何乗するか
     */
    Dynamic_Modint pow(int n) const {
        long long a = x, res = 1;
	    while (n > 0) {
		    if (n & 1) res = res * a % mod;
		    a = a * a % mod;
		    n >>= 1;
	    }
        return Dynamic_Modint(res, mod);
    }
    /**
     * @brief 逆元(存在しなければエラー)
     */
    Dynamic_Modint inverse() const {
        long long a = x, b = mod, u = 1, v = 0;
        while (b) {
            long long t = a / b;
            a -= t * b;
            std::swap(a, b);
            u -= t * v;
            std::swap(u, v);
        }
        return Dynamic_Modint(u, mod);
    }
    /**
     * @brief 加算代入
     */
    Dynamic_Modint &operator+=(Dynamic_Modint that) {if ((x += that.x) >= mod) x -= mod; return *this;}
    /**
     * @brief 減算代入
     */
    Dynamic_Modint &operator-=(Dynamic_Modint that) {if ((x += mod - that.x) >= mod) x -= mod; return *this;}
    /**
     * @brief 乗算代入 
     */
    Dynamic_Modint &operator*=(Dynamic_Modint that) {x = (unsigned long long)x * that.x % mod; return *this;}
    /**
     * @brief 除算代入
     */
    Dynamic_Modint &operator/=(Dynamic_Modint that) {return *this *= that.inverse();}
    /**
     * @brief 加算 
     */
    Dynamic_Modint operator+(Dynamic_Modint that) const {return Dynamic_Modint(*this) += that;}
    /**
     * @brief 減算
     */
    Dynamic_Modint operator-(Dynamic_Modint that) const {return Dynamic_Modint(*this) -= that;}
    /**
     * @brief 乗算
     */
    Dynamic_Modint operator*(Dynamic_Modint that) const {return Dynamic_Modint(*this) *= that;}
    /**
     * @brief 除算 
     */
    Dynamic_Modint operator/(Dynamic_Modint that) const {return Dynamic_Modint(*this) /= that;}
    /**
     * @brief 合同 
     */
    bool operator==(Dynamic_Modint that) const {return x == that.x;}
    /**
     * @brief 合同でない
     */
    bool operator!=(Dynamic_Modint that) const {return x != that.x;}
    /**
     * @brief -1倍
     */
    Dynamic_Modint operator-() const {Dynamic_Modint t; t.x = (x == 0 ? 0 : mod - x); return t;}
    /**
     * @brief 出力
     */
    friend std::ostream &operator<<(std::ostream &os, const Dynamic_Modint &a) {os << a.val(); return os;}
};