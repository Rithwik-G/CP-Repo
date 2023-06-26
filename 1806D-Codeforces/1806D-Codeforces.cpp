// Source: https://codeforces.com/problemset/problem/1806/D
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

const ll MOD = 998244353;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	ll t;
	ll n;
	cin >> t;
	while (t--){
		ll n;
		cin >> n;
		// n--;
		ll f = 1;
		ll ans = 0;
		vi a(n);
		FOR(i, 1, n) {
			cin >> a[i];
		} 

		FOR(i, 1, n) {
			ans = (i * ans + (a[i] == 0) * f) % MOD;
			cout << ans << ' ';
			f = ((i - a[i]) * f) % MOD;
		}
		cout << endl;
	}

}












