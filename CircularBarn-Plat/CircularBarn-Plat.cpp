// Source: http://www.usaco.org/index.php?page=viewproblem2&cpid=626
// Convex Hull Trick
// EEK


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


inline namespace _LineContainer {
bool _Line_Comp_State;
struct Line {
	// k is slope, m is intercept, p is llersection poll
	mutable ll k, m, p;
	bool operator<(const Line &o) const {
		return _Line_Comp_State ? p < o.p : k < o.k;
	}
};

struct LineContainer : multiset<Line> {
	long long div(long long a, long long b) {
		return a / b - ((a ^ b) < 0 && a % b);
	}

	bool isect(iterator x, iterator y) {
		if (y == end()) {
			x->p = LLONG_MAX;
			return false;
		}
		if (x->k == y->k) x->p = x->m > y->m ? LLONG_MAX : -LLONG_MAX;
		else x->p = div(y->m - x->m, x->k - y->k);
		return x->p >= y->p;
	}

	void add(long long k, long long m) {
		auto z = insert({k, m, 0}), y = z++, x = y;
		while (isect(y, z)) z = erase(z);
		if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
		while ((y = x) != begin() && (--x)->p >= y->p) isect(x, erase(y));
	}

	long long query(long long x) {
		assert(!empty());
		_Line_Comp_State = 1;
		auto l = *lower_bound({0, 0, x});
		_Line_Comp_State = 0;
		return l.k * x + l.m;
	}
};
}
int n, k;
int ans = 1e9;
void solve(vi &vals) {

	vi pref(n + 1, 0);
	vi sum(n + 1, 0);


	FOR(i, 1, n + 1) {
		pref[i] = i * vals[i] + pref[i-1];
	}

	FOR(i, 1, n + 1) {
		sum[i] = vals[i] + sum[i-1];
	}

	vector<LineContainer> hulls(k + 1);

	hulls[0].add(-1, 0);
	int dp;
	FOR(i, 1, n + 1) {
		FOR(j, 1, k + 1) {
			// if (j > i) continue;
			dp = hulls[j - 1].query(sum[i]) + pref[i];
			cout << i << j << ' ' << dp << endl;
			hulls[j].add(-(i + 1), dp - pref[i] + sum[i] * (i + 1));
		}
	}

	ans = min(ans, dp);
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);


	cin >> n >> k;

	vi vals(n + 1);

	FOR(i, 1, n + 1) cin >> vals[i];

	// reverse(vals.begin() + 1, vals.end());
	FOR(i, 0, n) {
		
		solve(vals);
		// FOR(i, 1, n + 1)
		// cout << ans << endl;
		rotate(vals.begin() + 1, vals.begin() + 2, vals.end());
		// break;
	}

	cout << ans << endl;

}












