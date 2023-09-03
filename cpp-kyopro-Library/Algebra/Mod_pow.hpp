/**
 * @brief 冪乗計算(繰り返し二乗法) O(log n)
 * 
 * @param a 底
 * @param n 指数
 * @param mod 法
 * @return long long a^n を mod で割ったあまり
 */
long long pow_mod(long long a, long long n, long long mod) {
	long long res = 1;
	while (n > 0) {
		if (n & 1) res = res * a % mod;
		a = a * a % mod;
		n >>= 1;
	}
	return res;
}