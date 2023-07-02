// Source: http://www.usaco.org/index.php?page=viewproblem2&cpid=794
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

const ll MOD = 1e9 + 7;

int main() {
	// freopen("sprinklers.in", "r", stdin);
	// freopen("sprinklers.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	ll n;
	cin >> n;

	vi vals(n);

	FOR(i, 0, n) {
		ll a;
		cin >> a;
		cin >> vals[a];
	}

	vi bottom(n);

	ll cur_min = 100000;

	FOR(i, 0, n) {
		cur_min = min(cur_min, vals[i]);
		bottom[i] = cur_min;
	}

	vi top(n);
	ll cur_max = 0;
	for (ll i = n - 1; i >= 0; i--) {
		cur_max = max(cur_max, vals[i]);
		top[i]=cur_max;
	}	

	vi endpolls(n, 0);

	FOR(i, 1, n) {
		if (bottom[i] >= top[i]) continue;
		for (ll j = top[i - 1]; j > top[i]; j--) {
			endpolls[j] = i-1;
		}
	}

	for (ll i = bottom[n-1]; i <= top[n-1]; i++) {
		endpolls[i]=n-1;
	}

	reverse(endpolls.begin(), endpolls.end());

	vi pref(n);
	vi sum(n);

	FOR(i, 0, n) {
		if (i != 0) {
			pref[i] = pref[i-1];
			sum[i] = sum[i-1];
		}
		pref[i] += endpolls[i];
		sum[i] += i * endpolls[i];
	}

	ll ans = 0;

	FOR(i, 0, n) {
		if (bottom[i] >= top[i]) continue;
		ll b = n - 1 - bottom[i];
		ll t = n - 1 - top[i];
		cout << i << (sum[b] - sum[t]) - (pref[b] - pref[t]) * (t) - (b - t) * (b - t + 1) * (i) / 2 << endl;
		ans = (((ans + (sum[b] - sum[t]) - (pref[b] - pref[t]) * (t)) % MOD)  -  (((b - t) * (b - t + 1) * (i) / 2) % MOD) + MOD) % MOD;
	}


	cout << ans << endl;

}












