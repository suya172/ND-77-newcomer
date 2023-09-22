#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <numeric>

using namespace std;

struct SuffixArray {
    vector<int> SA;
    string S;
    /**
     * @brief SuffixArrayの構築
     */
    void Build(const string& s) {
        S = s;
        SA.resize(S.size());        
        iota(SA.begin(), SA.end(), 0);
        sort(SA.begin(), SA.end(), [&](const int &a, const int &b) {
            if (S[a] == S[b]) return a > b;
            return (S[a] < S[b]);
        });
        vector<int> classes(S.size()), c(S.size()), cnt(S.size());
        for (int i = 0; i < S.size(); i++) {
            c[i] = S[i];
        }
        for (int len = 1; len < S.size(); len <<= 1) {
            for (int i = 0; i < S.size(); i++) {
                if (i > 0 && c[SA[i - 1]] == c[SA[i]] && SA[i - 1] + len < S.size() && c[SA[i - 1] + len / 2] == c[SA[i] + len / 2]) {
                    classes[SA[i]] = classes[SA[i - 1]];
                } else {
                    classes[SA[i]] = i;
                }
            }
            iota(cnt.begin(), cnt.end(), 0);
            copy(SA.begin(), SA.end(), c.begin());
            for (int i = 0; i < SA.size(); i++) {
                int s1 = c[i] - len;
                if (s1 >= 0) {
                    SA[cnt[classes[s1]]++] = s1;
                }
            }
            classes.swap(c);
        }
    }

    /**
     * @brief SuffixArrayの構築
     */
    SuffixArray (string s = "") {
        Build(s);
    }

    /**
     * @brief SuffixArrayのサイズ
     */
    int size() const {
        return SA.size();
    }

    /**
     * @brief 二分探索用評価関数
     */
    bool lt_substr(string &t, int si = 0, int ti = 0) {
        int sn = S.size(), tn = t.size();
        while (si < sn && ti < tn) {
            if (S[si] < t[ti]) return true;
            if (S[si] > t[ti]) return false;
            si++;
            ti++;
        }
        return (si >= sn && ti < tn);
    }

    /**
     * @brief 二分探索 (t を接頭辞に持つ S の接尾辞であって辞書順最小のものの index)
     */
    int lower_bound(string &t) {
        int l = -1, r = SA.size();
        while (r - l > 1) {
            int mid = (l + r) / 2;
            if (lt_substr(t, SA[mid])) l = mid;
            else r = mid;
        }
        return r;
    }

    /**
     * @brief 二分探索 (t を接頭辞に持つ S の接尾辞であって辞書順最小のものの index と辞書順最大のものの indx の pair)
     * 
     * @param t 
     * @return pair<int, int> 
     */
    pair<int, int> lower_upper_bound(string &t) {
        int idx = lower_bound(t);
        int l = idx - 1, r = SA.size();
        t.back()++;
        while (r - l > 1) {
            int mid = (l + r) / 2;
            if (lt_substr(t, SA[mid])) l = mid;
            else r = mid;
        }
        t.back()--;
        return make_pair(idx, r);
    }

    int operator[] (int i) const {
        return SA[i];
    }

    friend ostream &operator<<(ostream &os, const SuffixArray &SA_) {
        for (int i = 0; i < SA_.size(); i++) {
            os << i << ":" << SA_.S.substr(SA_[i]) << endl;
        }
        return os;
    }
};

struct LCP_Array {
    vector<int> lcp, rank;

    /**
     * @brief SuffxArrayからLongestCommonPrefixArrayを構築する
     * 
     * @param SA 
     */
    void Build(SuffixArray &SA) {
        string &S = SA.S;
        rank.resize(S.size());
        for (int i = 0; i < S.size(); i++) {
            rank[SA[i]] = i;
        }
        lcp.resize(S.size());
        lcp[0] = 0;
        for (int i = 0, h = 0; i < S.size(); i++) {
            if (rank[i] + 1 < S.size()) {
                for (int j = SA[rank[i] + 1]; max(i, j) + h < S.length() && S[i + h] == S[j + h]; h++) continue;
                lcp[rank[i] + 1] = h;
                if (h > 0) h--;
            }
        }
    }

    /**
     * @brief SuffxArrayからLongestCommonPrefixArrayを構築する
     */
    LCP_Array(SuffixArray &SA) {
        Build(SA);
    }

    /**
     * @brief LCP_Arrayのサイズ
     */
    int size() {
        return lcp.size();
    }
 
    int operator[](int i) {
        return lcp[i];
    }
};