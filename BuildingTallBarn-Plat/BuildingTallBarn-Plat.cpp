// Source: 

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


int main() {
	// freopen("tallbarn.in", "r", stdin);
	// freopen("tallbarn.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, k;
	cin >> n >> k;

	vector<double> w(n);

	FOR(i, 0, n) cin >> w[i];

	double l = 0;
	double r = 1e18;

	vi cur_sol(n);
	vi best_sol(n);
	FOR(_, 0, 200){
		double m = 0.5d * (l + r);

		int tot = 0;

		FOR(i, 0, n) {
			tot += cur_sol[i] = floor((-1.0d + sqrt(1.0d + 4 * w[i]/m)) * 0.5d);
		}

		if (tot <= k) {
			r = m;
			swap(cur_sol, best_sol);
		} else {
			l = m;
		}

	}

	double ans = 0;
	ll tot = 0;
	FOR(i, 0, n) {
		tot += cur_sol[i];
		ans += w[i] / ((double) cur_sol[i]);
	}

	cout << round(ans - (k-tot)*r) << endl;

}












