#include <vector>
#include "../Mod_pow.hpp"

using namespace std;

// miller-rabin素数判定法 A := 素数の集合
// Mod_pow.hppを使う
bool is_prime(long long N, vector<long long> A) {
	if (N <= 1)
		return false;
	if (N == 2)
		return true;
	if (N % 2 == 0)
		return false;
	long long s = 0, d = N - 1;
	while (d % 2 == 0) {
		++s;
		d >>= 1;
	}
	for (auto a : A) {
		if (a % N == 0) return true;
		long long t, x = pow_mod(a, d, N);
		if (x != 1) {
			for (t = 0; t < s; ++t) {
				if (x == N - 1) break;
				x = (long long)(x) * x % N;
			}
			if (t == s)
				return false;
		}
	}
	return true;
}