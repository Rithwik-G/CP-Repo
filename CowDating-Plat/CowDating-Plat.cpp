// Source: http://www.usaco.org/index.php?page=viewproblem2&cpid=924
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

const ll N = 1e6 + 5;

// double prob[N];

// struct node {
// 	double val0;
// 	double pref0;
// 	double suff0;

// 	double val1;
// 	double pref1;
// 	double suff1;
// };

// double comb(double a0, double a1, double b0, double b1) {
// 	return a0 * b1 + a1 * b0;
// }

// node solve(ll l, ll r) {
// 	node cur;
// 	if (r - l == 1) {
// 		cur.val0 = cur.suff0 = cur.pref0 = 1 - prob[l];
// 		cur.val1 = cur.suff1 = cur.pref1 = prob[l];
// 		return cur;
// 	}

// 	ll m = (l + r)/2;

// 	node right = solve(l, m);
// 	node left = solve(m, r);

// 	cur.val0 = left.val0 * right.val0;
// 	cur.pref0 = max(left.pref0, left.val0);
// 	cur.suff0 = max(right.suff, comb(left.suff, right.val));

// 	cur.val = max(max(right.val, left.val), comb(right.pref, left.suff));
// 	cur.pref = max(left.pref, comb(left.val, right.pref));
// 	cur.suff = max(right.suff, comb(left.suff, right.val));

// 	cout << l << r << ' ' << cur.val << endl;
// 	return cur;

// }


int main() {
	freopen("cowdate.in", "r", stdin);
	freopen("cowdate.out", "w", stdout);

	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	ll n;
	cin >> n;

	vector<double> v(n);

	pii best = {-1, -1};
	double ans = -1;

	FOR(i, 0, n) {
		cin >> v[i];
		v[i] *= 0.000001;
		if (v[i] > ans) {
			ans = (v[i]) / (1.0 - v[i]);
			best = {i, i};
		}
	}


	ll l = 0;
	ll r = 0;
	double cur_sum = 0;

	double P = 1;
	double s = 0;

	while (l != n) {
		while (r != n && cur_sum < 1) {
			cur_sum += (v[r]) / (1.0 - v[r]);

			P *= (1.0 - v[r]);

			r++;
		}

		if (P * cur_sum > ans) {
			ans = P * cur_sum;

		}

		// cout << l << r << ' ' << P << ' ' << cur_sum << endl;

		cur_sum -= (v[l]) / (1.0 - v[l]);
		P /= (1.0 - v[l]);

		l++;

	}

	// cout << best.f << best.s << endl;

	// double P = 1;
	// double s = 0;

	// FOR(i, best.f, best.s + 1) {
	// 	s += (v[i]) / (1.0-v[i]);
	// 	P *= (1.0 - v[i]);

	// }

	cout << (long long) (ans * 1e6) << endl;

	



	// a /= 1e6;
	// double maxdp = a;
	// double mindp = 0;

	// double ans = a;

	// FOR(i, 1, n) {

	// 	cin >> a;
	// 	a /= 1e6;
	// 	if (a < 0.5) {
	// 		maxdp = maxdp * (1 - 2 * a) + a;
	// 		// mindp = mindp * (1 - 2 * a) + a;
	// 	}

	// 	else {
	// 		// mindp = maxdp * (1 - 2 * a) + a;
	// 		maxdp = mindp * (1 - 2 * a) + a;
	// 	}
	// 	cout << maxdp << mindp << endl;
	// 	ans = max(ans, maxdp);
	// }

	// cout << ans << endl;

}











