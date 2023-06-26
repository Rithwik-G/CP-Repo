// Source: https://cses.fi/problemset/task/2064
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
const ll MOD = 1e9 + 7;

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

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n;
	cin >> n;
	if (n % 2 == 1) {
		cout << 0 << endl;
		return 0;
	}
	n/=2;
	int ans = 1;
	FOR(i, 1, n+1) {
		ans = (4 * i - 2) * ans % MOD * binpow(i + 1, MOD-2) % MOD;
	}

	cout << ans << endl;
}












