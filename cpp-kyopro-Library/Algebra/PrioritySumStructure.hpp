#include <queue>

using namespace std;

/**
 * @brief 多重集合の中で上位 K 個の要素の総積をとる
 * 
 * @tparam T 集合の要素の型
 * @tparam (*op)(T, T) 二項演算
 * @tparam (*rop)(T, T) 二項演算の逆関数
 * @tparam (*e)() 単位元
 * @tparam comp 比較関数
 * @tparam rcomp 比較関数の逆
 */
template <class T, T (*op)(T, T), T (*rop)(T, T), T (*e)(), typename comp = less<T>, typename rcomp = greater<T>>
struct PrioritySumStructure {
    size_t k;
    T sum;
    priority_queue<T, vector<T>, comp> in, d_in;
    priority_queue<T, vector<T>, rcomp> out, d_out;
    PrioritySumStructure(int k) : k(k) {
        sum = e();
    }
    /**
     * @brief 上位K個のバランスを取る
     * 
     */
    void balance() {
        while (in.size() - d_in.size() < k && !out.empty()) {
            auto p = out.top();
            out.pop();
            if (!d_out.empty() && p == d_out.top()) {
                d_out.pop();
            } else {
                sum = op(sum, p);
                in.emplace(p);
            }
        }
        while (in.size() - d_in.size() > k) {
            auto p = in.top();
            in.pop();
            if (!d_in.empty() && p == d_in.top()) {
                d_in.pop(); 
            } else {
                sum = rop(sum, p);
                out.emplace(p);
            }
        }
        while (!d_in.empty() && in.top() == d_in.top()) {
            in.pop();
            d_in.pop();
        }
    }
    /**
     * @brief クエリ
     */
    T query() const {
        return sum;
    }
    /**
     * @brief 要素の挿入
     */
    void insert(T x) {
        in.emplace(x);
        sum = op(sum, x);
        balance();
    }
    /**
     * @brief 要素の削除
     */
    void erase(T x) {
        assert(size());
        if (!in.empty() && in.top() == x) {
            sum = rop(sum, x);
            in.pop();
        } else if (!in.empty() && rcomp()(in.top(), x)) {
            sum = rop(sum, x);
            d_in.emplace(x);
        } else {
            d_out.emplace(x);
        }
        balance();
    }
    /**
     * @brief Kを設定する
     */
    void set_K(size_t kk) {
        k = kk;
        balance();
    }
    /**
     * @brief Kの取得 
     */
    size_t get_K() const {
        return k;
    }
    /**
     * @brief 要素数の取得
     */
    size_t size() const {
        return in.size() + out.size() - d_in.size() - d_out.size();
    }
};

template<typename T>
T sum_op(T a, T b) {
    return a + b;
}

template<typename T>
T sum_rop(T a, T b) {
    return a - b;
}

template<typename T>
T sum_e() {
    return T(0);
}

template<typename T>
using MaxSumK = PrioritySumStructure<T, sum_op<T>, sum_rop<T>, sum_e<T>, greater<T>, less<T>>;

template<typename T>
using MinSumK = PrioritySumStructure<T, sum_op<T>, sum_rop<T>, sum_e<T>, less<T>, greater<T>>;