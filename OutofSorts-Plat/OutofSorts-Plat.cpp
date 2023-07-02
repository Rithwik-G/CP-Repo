// Source: http://www.usaco.org/index.php?page=viewproblem2&cpid=840
// AC
// Turns out this solution is wrong though, because the problem uses do-while loops
// For real solution, increment by 1 for every element in the largest correct prefix.

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


template <class T> class MaxSegmentTree {
  private:
	const T DEFAULT = 0;  // Will overflow if T is an ll

	vector<T> segtree;
	ll len;

  public:
	MaxSegmentTree(ll len) : len(len), segtree(len * 2, DEFAULT) {}

	/** Sets the value at ind to val. */
	void upd(ll ind, T val) {
		ind += len;
		segtree[ind] = max(val, segtree[ind]);
		for (; ind > 1; ind /= 2) {
			segtree[ind / 2] = std::max(segtree[ind], segtree[ind ^ 1]);
		}
	}

	/** @return the minimum element in the range [start, end) */
	T range_max(ll start, ll end) {
		T sum = DEFAULT;
		for (start += len, end += len; start < end; start /= 2, end /= 2) {
			if (start % 2 == 1) { sum = std::max(sum, segtree[start++]); }
			if (end % 2 == 1) { sum = std::max(sum, segtree[--end]); }
		}
		return sum;
	}
};


int main() {
	// freopen("sort.in", "r", stdin);
	// freopen("sort.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	ll n;
	cin >> n;

	vi a(n);
	bool sorted=true;
	FOR(i, 0, n) {
		cin >> a[i];
		if (i != 0 && a[i] < a[i-1]) sorted=false;
	}

	if (sorted) {
		if (n != 1) cout << n << endl;
		else cout << 0 << endl;
		return 0;
	}


	vi d = a;
	sort(d.begin(), d.end());
	d.resize(unique(d.begin(), d.end()) - d.begin());
	for (ll i = 0; i < n; ++i) {
		a[i] = lower_bound(d.begin(), d.end(), a[i]) - d.begin();
	}

	MaxSegmentTree<ll> mx(n);
	ll ans = 0;

	FOR(i, 0, n) {
		if (a[i] != i) break; // works without this loop but it really shouldn't
		ans++;
	}
	for (ll i = n - 1; i>= 0; i--) {

		ll cur = mx.range_max(0, a[i]);
		mx.upd(a[i], i);
		if (cur == 0) continue;

		ans += (cur - i + 1ll);
	}
	cout << ans << endl;

}












