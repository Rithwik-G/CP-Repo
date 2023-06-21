// Source: https://codeforces.com/problemset/problem/1830/C
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

mt19937_64 gen(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<ll> rnd(0,LLONG_MAX);

const ll N = 3e5 + 10;
const ll MOD = 998244353;
ll c[N];

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
	return (fact[n] * ((invfact[k] * invfact[n - k]) % MOD)) % MOD;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	calcChoose(N);

	FOR(i, 0, N/2) c[2*i] = (choose(2 * i, i) * binpow(i + 1, MOD - 2)) % MOD;

	ll t;
	cin >> t;



	while (t--) {
		map<ll, ll> counts;
		ll n, k;
		cin >> n >> k;

		vi diff(n + 3);
		diff[1] = rnd(gen);

		for (ll i = 0; i < k; i++) {
			ll l, r;
			cin >> l >> r;
			ll hash = rnd(gen);
			diff[l] ^= hash;
			diff[r + 1] ^= hash;
		}
		ll cur = 0;

		FOR(i, 1, n + 1) {
			cur ^= diff[i];
			counts[cur]++;
		}
		ll ans = 1;
		for (auto val: counts) {
			assert(val.s != 0);
			ans = (ans * c[val.s]) % MOD;
		}

		cout << ans << endl;
	}

}












