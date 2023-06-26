// Source: http://www.usaco.org/index.php?page=viewproblem2&cpid=624
// AC

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


template <class T> class SumSegmentTree {
  private:
	const T DEFAULT = 0;

	vector<T> segtree;
	int len;

  public:
	SumSegmentTree(int len) : len(len), segtree(len * 2, DEFAULT) {}

	void update(int ind, T val) {
		ind += len;
		segtree[ind] += val;
		for (; ind > 1; ind /= 2) {
			segtree[ind / 2] = segtree[ind] + segtree[ind ^ 1];
		}
	}

	T query(int start, int end) {
		T sum = DEFAULT;
		for (start += len, end += len; start < end; start /= 2, end /= 2) {
			if (start % 2 == 1) { sum += segtree[start++]; }
			if (end % 2 == 1) { sum += segtree[--end]; }
		}
		return sum;
	}
};



SumSegmentTree<int> r(1e6 + 10);
SumSegmentTree<int> l(1e6 + 10);

const int MX = 1e6 + 10;

vi rem[MX];

int binsearch() {
	int ri = 1e6 + 1;
	int le = 0;

	int ans = 100000000;

	while (le < ri) {
		int mid = (le + ri)/2;
		// cout << mid << endl;
		int upper = max(r.query(0, mid), l.query(0, mid));
		int lower = max(r.query(mid, 1e6 + 4), l.query(mid, 1e6 + 4));

		ans = min(ans, max(upper, lower));

		if (upper < lower) le = mid + 1;
		else ri = mid;

	}

	return ans;
}
int ans = 100000000;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	freopen("balancing.in", "r", stdin);
	freopen("balancing.out", "w", stdout);


	int n;
	cin >> n;



	FOR(i, 0, n) {
		int a, b;
		cin >> a >> b;

		rem[a].pb(b);
		r.update(b, 1);
	}

	FOR(i, 0, 1e6) {
		if (rem[i].size() == 0) continue;

		for (int removal: rem[i]) {
			r.update(removal, -1);
			l.update(removal, 1);
		}

		ans = min(ans, binsearch());
		// cout << i << ans << endl;
	}
	cout << ans << endl;

}












