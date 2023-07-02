// Source: http://www.usaco.org/index.php?page=viewproblem2&cpid=698
// 

#include "bits/stdc++.h"

using namespace std;

#define s second
#define f first
#define pb push_back

typedef long long ll;

typedef pair<ll, ll> pii;
typedef vector<pii> vpii;

typedef vector<ll> vi;

#define FOR(i, a, b) for (ll i = (a); i<b; i++)

const int N = 51;

int dp[N][N]; // answer for range [i, j]
int lis[N][N]; // lis for range [i, j]

template <class T> class MaxSegmentTree {
  private:
	const T DEFAULT = -1;  // Will overflow if T is an int

	vector<T> segtree;
	int len;

  public:
	MinSegmentTree(int len) : len(len), segtree(len * 2, DEFAULT) {}

	/** Sets the value at ind to val. */
	void set(int ind, T val) {
		ind += len;
		segtree[ind] = max(val, segtree[ind]);
		for (; ind > 1; ind /= 2) {
			segtree[ind / 2] = std::max(segtree[ind], segtree[ind ^ 1]);
		}
	}

	/** @return the minimum element in the range [start, end) */
	T range_min(int start, int end) {
		T sum = DEFAULT;
		for (start += len, end += len; start < end; start /= 2, end /= 2) {
			if (start % 2 == 1) { sum = std::max(sum, segtree[start++]); }
			if (end % 2 == 1) { sum = std::max(sum, segtree[--end]); }
		}
		return sum;
	}
};


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n;
	cin >> n;
	vi a(n);
	FOR(i, 0, n) cin >> a[i];


	for (int l = 0; l < n; l++) {
		for (int i = 0; i+l < n; i++) {
			int j = i + l;
			if (i == j) {
				lis[i][j] = 1;
				continue;
			}
			if (a[j] < a[i]) {
				lis[i][j] = 0;
				continue;
			}
			lis[i][j] = 2;
			if (l == 1) continue;

			for (int le = i + 1; le <= j; le++) {
				for (int ri = j - 1; ri >= le; ri--) {
					if (a[le] < a[i] || a[ri] > a[j]) continue;
					lis[i][j] = max(lis[i][j], lis[le][ri] + 2);
				}
			}
		}
	}

	for (int l = 0; l < n; l++) {
		for (int i = 0; i+l < n; i++) {
			int j = i + l;
			if (i == j) {
				dp[i][j] = 1;
				continue;
			}
			if (a[j] > a[i]) {
				dp[i][j] = 0;
				continue;
			}
			dp[i][j] = 2;
			if (l == 1) continue;

			MaxSegmentTree<int> aux(N);
			vi pref_lis(n, -1);
			aux.upd(a[j], 1);
			pref_lis[0]=1;


			for (int le = i + 1; le <= j; le++) {
				pref_lis[a[i + 1]]
			}

			for (int le = i + 1; le <= j; le++) {
				for (int ri = j - 1; ri >= le; ri--) {
					if (a[le] > a[i] || a[ri] < a[j]) continue;
					dp[i][j] = max(dp[i][j], lis[le][ri]);
				}
			}
		}
	}



}












