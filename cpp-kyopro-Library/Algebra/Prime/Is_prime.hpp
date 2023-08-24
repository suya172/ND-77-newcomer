// 素数判定
bool isprime(int N) {
	bool ok = true;
	for (int i = 2; i * i <= N; i++)
		if (N % i == 0)
			ok = false;
	return ok;
}