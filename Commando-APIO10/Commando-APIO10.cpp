// Source: https://dmoj.ca/problem/apio10p1
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

inline namespace _LineContainer {
bool _Line_Comp_State;
struct Line {
	// k is slope, m is llercept, p is llersection poll
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

const int N = 1e6 + 5;

// int vals[N]; // MLE
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	LineContainer hull;

	hull.add(0, 0);

	ll n, a, b, c;
	cin >> n >> a >> b >> c;

	ll dp;
	int cur = 0;
	FOR(i, 1, n + 1) {
		int d;
		cin >> d;
		cur += d;
		dp = hull.query(cur) + a * cur*cur + b * cur + c;
		hull.add(-2 * a * cur,dp + a * cur*cur - b * cur);
	}
	cout << dp << endl;



}












