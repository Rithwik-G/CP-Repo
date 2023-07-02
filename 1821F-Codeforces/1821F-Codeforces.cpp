// Source: https://codeforces.com/problemset/problem/1821/F
// hella sketch AC

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
const ll N = 1e6;

ll fact[N];
ll invfact[N];

ll binpow(ll x, ll n) { // binary exponentiation
	x %= MOD;
	ll cur = 1;
	while (n > 0) {
		if (n % 2==1) {cur = cur * x % MOD;}
 
		x = x * x % MOD;
		n /= 2;
	}
	return cur;
}

void calcChoose(ll n) { // preprocessing
	fact[0]=1;
	invfact[0]=1;
	for (ll i = 1; i < n; i++) fact[i] = (fact[i-1]*i) % MOD;
	for (ll i = 1; i < n; i++) invfact[i] = binpow(fact[i], MOD - 2) % MOD;
}

ll choose(ll n, ll k) { // calculate choose in O(1)
	if (k > n) return 0;
	return (fact[n] * ((invfact[k] * invfact[n - k]) % MOD)) % MOD;
}


int main() {
	calcChoose(N);
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	ll n, m, k;

	cin >> n >> m >> k;
	ll ans = 0;
	// ll f = 0;
	// ll prev = 0;	
	for (ll x = m; x >= 0; x--) {
		// cout << n - x*(2 * k + 1) - (m - x) * (k + 1) + m << ' ' << m << ' ' << x << endl;
		ll cur_f = choose(n - x*(2 * k + 1) - (m - x) * (k + 1) + m, m) * choose(m, x) % MOD;

		// f = cur_f - f;

		// cout << f * binpow(2, m - x) << ' ' << cur_f << endl;

		// ans = (ans + f * binpow(2, m - x)) % MOD;

		ans = (ans + (cur_f * binpow(2, m - x)) * (x & 1 ? -1 : 1)) % MOD;
	}

	cout << ans << endl;

}












