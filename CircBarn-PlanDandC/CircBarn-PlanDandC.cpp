// Source: http://www.usaco.org/index.php?page=viewproblem2&cpid=626
// Divide and Conquer
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

const ll N = 1010;
const ll K = 8;
const ll INF = 1e15;
ll dp[K][N];
ll sum[N];
ll pref[N];

ll n, k;

void solve(ll k, ll ia, ll ib, ll ja, ll jb) {
	if (ia == ib) return;

	ll i = (ia + ib) / 2;
	ll arg_j = -1;

	dp[k][i] = INF;

	for (ll j = ja; j <= jb; j++) {
		// cout << ja << jb << endl;
		ll v = sum[i] - sum[j] - (pref[i] - pref[j]) * (j + 1) + dp[k - 1][j];

		if (v < dp[k][i]) {

			arg_j = j;
			dp[k][i] = v;
		}
	}

	// cout << i << k << arg_j << ' ' << dp[k][i] << endl;

	solve(k, ia, i, ja, arg_j);
	solve(k, i + 1, ib, arg_j, jb);


}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	freopen("cbarn.in", "r", stdin);
	freopen("cbarn.out", "w", stdout);

	cin >> n >> k;

	vi vals(n + 1);

	FOR(i, 1, n + 1) cin >> vals[i];

	// reverse(vals.begin() + 1, vals.end());
	
	memset(dp, 0x3F, sizeof(dp));

	dp[0][0]=0;
	ll res = INF;

	FOR(i, 0, n) {
		FOR(i, 1, n+1) pref[i] = pref[i-1] + vals[i];
		FOR(i, 1, n + 1) sum[i] = sum[i-1] + vals[i] * i;
		FOR(j, 1, k+1) solve(j, 1, n+1, 0, n);
		rotate(vals.begin() + 1, vals.begin() + 2, vals.end());
		res = min(res, dp[k][n]);
		// break;
	}

	cout << res << endl;

}












