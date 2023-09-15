#include <vector>

template<typename T, int FAC_MAX>
struct Comb {
    std::vector<T> fac, ifac;
    Comb() {
        fac.resize(FAC_MAX, 1);
        ifac.resize(FAC_MAX, 1);
        for (int i = 1; i < FAC_MAX; i++) {
            fac[i] = fac[i - 1] * T(i);
        }
        ifac[FAC_MAX - 1] = T(1) / fac[FAC_MAX - 1];
        for (int i = FAC_MAX - 2; i > 0; i--) {
            ifac[i] = ifac[i + 1] * T(i + 1);
        }
    }
    /**
     * @brief 順列の個数(nPr)を求める
     */
    T nPr(int n, int r) {
        if (r < 0 || n < r) return T(0);
        return fac[n] * ifac[n - r];
    }
    /**
     * @brief 組み合わせの個数(nCr)を求める
     */
    T nCr(int n, int r) {
        if (r < 0 || n < r) return T(0);
        return fac[n] * ifac[n - r] * ifac[r];
    }
    /**
     * @brief 重複組み合わせの個数(nHr)を求める
     */
    T nHr(int n, int r) {
        if (n == 0 && r == 0) return T(1);
        if (n <= 0 || r < 0) return T(0);
        return nCr(n + r - 1, r);
    }
    /**
     * @brief 階乗(n!)を求める
     */
    T factorial(int n) {
        return nPr(n, n);
    }
};
