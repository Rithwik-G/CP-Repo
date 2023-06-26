// Source: https://codeforces.com/contest/1083/problem/E
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

struct line {
	ll m, b;
	ll eval(ll x) {return m * x + b;}
	long double intersectX(line l) {return (long double) (b - l.b) / (l.m - m);}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	ll n;
	cin >> n;

	vector<array<ll, 3> > inp(n);

	FOR(i, 0 , n) {
		FOR(j, 0, 3) cin >> inp[i][j];
	}

	sort(inp.begin(), inp.end());

	deque<line> hull;
	hull.push_front({0, 0});

	ll ans = 0;

	FOR(i, 0, n) {
		while (hull.size() >= 2 && hull.back().eval(inp[i][1]) <= hull[hull.size() - 2].eval(inp[i][1])) hull.pop_back();

		ll best = hull.back().eval(inp[i][1]) + inp[i][0] * inp[i][1] - inp[i][2];

		ans = max(ans, best);

		line cur = {-inp[i][0], best};

		while (hull.size() >= 2 && hull[0].intersectX(hull[1]) <= cur.intersectX(hull[1])) hull.pop_front();

		hull.push_front(cur);
	}

	cout << ans << endl;

}












