// Source: https://codeforces.com/problemset/problem/1838/E

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

const ll MOD = 1e9 + 7;

ll binpow(ll x, ll n, ll m = MOD) {
	assert(n >= 0);
	x %= m;  // note: m * m must be less than 2^63 to avoid ll overflow
	ll res = 1;
	while (n > 0) {
		if (n % 2 == 1) { res = res * x % m; }
		x = x * x % m;
		n /= 2;
	}
	return res;
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int t;
	cin >> t;

	while (t--) {
		int n, m, k, d;
		cin >> n >> m >> k;
		FOR(i, 0, n) cin >> d; // junk

		ll ans = 0;
		ll choose = 1;

		FOR(i, 0, n) {
			if (i != 0) choose = (choose * (m - i + 1ll) % MOD * binpow(i, MOD - 2, MOD)) % MOD;
			ans = (ans + choose * binpow(k - 1ll, m - i, MOD)) % MOD;

			
			// cout << choose << endl;
		}

		ans = (binpow(k, m) - ans + MOD) % MOD;

		cout << ans << endl;

		
	}

}












