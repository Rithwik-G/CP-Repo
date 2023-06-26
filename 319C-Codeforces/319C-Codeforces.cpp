// Source: https://codeforces.com/contest/319/problem/C
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

struct line {
	ll m, b;
	ll eval(ll x) {return m * x + b;}
	long long intersectX(line l) {return floor((long double) (b - l.b) / (l.m - m));}
};

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);


	ll n;
	cin >> n;

	vi a(n);
	vi b(n);

	FOR(i, 0, n) cin >> a[i];
	FOR(i, 0, n) cin >> b[i];

	deque<line> hull;

	hull.push_front({b[0], 0});
	ll ans = 0;
	FOR(i, 1, n) {
		// query at current line

		while (hull.size() >= 2 && hull[0].eval(a[i]) >= hull[1].eval(a[i])) hull.pop_front();

		// for (auto val: hull) cout << val.m << ' ' << val.b << endl;

		ans = hull[0].eval(a[i]);

		line cur = {b[i], ans};

		while (hull.size() >= 2 && hull[0].intersectX(hull[1]) >= cur.intersectX(hull[1])) hull.pop_front();

		hull.push_front(cur);
		// cout << ans << endl;

	}

	cout << ans << endl;
}












