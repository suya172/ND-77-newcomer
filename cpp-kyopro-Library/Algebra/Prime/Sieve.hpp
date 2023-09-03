#include <vector>

using namespace std;

/**
 * @brief  エラトステネスの篩　O(max log log max)
 * 
 * @param max 篩の最大値
 * @return vector<bool> 素数かどうかの表
 */
vector<bool> sieve(size_t max){
	vector<bool> IsPrime;
	if(max+1 > IsPrime.size())
		IsPrime.resize(max+1,true);
	IsPrime[0] = false;
	IsPrime[1] = false;
	for(size_t i=2; i*i<=max; ++i)
		if(IsPrime[i])
			for(size_t j=2; i*j<=max; ++j)
				IsPrime[i*j] = false;
	return IsPrime;
}