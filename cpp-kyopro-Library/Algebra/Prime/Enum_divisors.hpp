#include <vector>
#include <algorithm>

using namespace std;

/**
 * @brief 約数列挙 O(√N)
 * 
 * @param N 約数列挙する数
 * @return vector<long long> Nの約数(昇順)
 */
vector<long long> enum_divisors(long long N) {
    vector<long long> res;
    for (long long i = 1; i * i <= N; ++i) {
        if (N % i == 0) {
            res.push_back(i);
            if (N / i != i)
                res.push_back(N / i);
        }
    }
    sort(res.begin(), res.end());
    return res;
}