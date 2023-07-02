// Source: https://codeforces.com/problemset/problem/1815/D
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

const ll MOD = 998244353;

map<ll, pii> val;

pii solve(ll n) {
	if (val.find(n) != val.end()) return val[n];
	if (n == 0) return {0, 1};
	if (n == 1) return {1, 1};
	if (n % 2 == 1) {
		auto cur = solve(n / 2);

		return val[n] = {(2ll * cur.f + cur.s) % MOD, cur.s};
	} else {
		auto cur1 = solve(n / 2);
		auto cur2 = solve(n / 2 - 1);

		return val[n] = {(2ll * cur1.f + 2ll * cur2.f) % MOD, (cur1.s + cur2.s) % MOD};
	}
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	ll t;
	cin >> t;

	while (t--) {
		ll n, m;
		cin >> n >> m;

		if (m == 1) cout << n % MOD << endl;
		else if (m == 2) cout << solve(n).f << endl;
		else if(n%2==0){
            cout << (((n/2)%MOD)*((n/2+1)%MOD))%MOD << endl;
        }
        else{
            cout << (((n/2+1)%MOD)*((n/2+1)%MOD))%MOD << endl;
        } 

		vi sum;
	// 	ll i;
	// 	for (i = 0; (1 << i) <= n; i++) {
	// 		sum.pb(n & (1 << i));
	// 	}

	// 	sum.pb(n & (1 << i));

	// 	reverse(sum.begin(), sum.end());

	// 	ll log = sum.size();

	// 	vector<vi> f(log, vi(2));
	// 	vector<vi> g(log, vi(2));

	// 	f[0][0] = 1;
	// 	f[0][1] = 1;
	// 	g[0][0] = 0;
	// 	g[0][1] = 1;
	// 	// cout << log << endl;
	// 	for (ll i = 1, div = log - 1; i < log; i++, div--) {
	// 		f[i][0] = f[i-1][0] + f[i-1][1];
	// 		f[i][1] = f[i - 1][0];

	// 		g[i][0] = 2 * g[i - 1][0] + 2 * g[i - 1][1];
	// 		g[i][1] = 2 * g[i - 1][0] + f[i - 1][0];
	// 	}

	// 	cout << g[log-1][sum[log-1]] << endl;
	// }

}












