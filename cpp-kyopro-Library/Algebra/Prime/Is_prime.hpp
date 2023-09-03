/**
 * @brief 素数判定 O(√N)
 * 
 * @param N 判定する数
 * @return true 素数である
 * @return false 素数でない
 */
bool isprime(int N) {
	bool ok = true;
	for (int i = 2; i * i <= N; i++)
		if (N % i == 0)
			ok = false;
	return ok;
}
