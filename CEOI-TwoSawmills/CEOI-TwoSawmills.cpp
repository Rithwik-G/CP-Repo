// Source: https://szkopul.edu.pl/problemset/problem/ovRIpLFK3IhyFPjnVXeZtGxH/site/?key=statement
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

const int N = 2e4 + 10;


int dist[N];
int wood[N];
int sum[N];

int dp[4][N];
int base[N];
const int INF = 1e9;

int C(int j, int i) { // returns cost of range from (j, i]
	return (sum[i] - sum[j]) - dist[j + 1] * (wood[i] - wood[j]);
}

void solve(ll k, ll ia, ll ib, ll ja, ll jb) { // solves range [ia, ib) assuming the previous DP can be from [ja, jb]
	if (ia == ib) return;

	ll i = (ia + ib) / 2;
	ll arg_j = -1;

	dp[k][i] = INF;

	for (ll j = ja; j <= jb; j++) {
		ll v = C(j, i) + dp[k - 1][j];
		if (v < dp[k][i]) {

			arg_j = j;
			dp[k][i] = v;
		}
	}

	cout << i << k << ja << jb << arg_j << ' ' << dp[k][i] << endl;

	solve(k, ia, i, ja, arg_j);
	solve(k, i + 1, ib, arg_j, jb);

}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n;

	cin >> n;

	FOR(i, 1, n + 1) {
		cin >> wood[i] >> dist[i];
	}

	reverse(wood + 1, wood + n + 1);
	reverse(dist + 1, dist + n + 1);

	FOR(i, 1, n + 1) {
		dist[i] += dist[i-1];

		sum[i] = sum[i-1] + dist[i]*wood[i];

		cout << sum[i] << endl;
	}

	FOR(i, 1, n + 1) wood[i] += wood[i-1];

	// cout << sum[2] << endl;

	memset(dp, 0x3F, sizeof(dp));
	dp[0][0]=0;
	FOR(i, 1, 4) {
		solve(i, 1, n + 1, 0, n);
	}

	cout << dp[3][n] << endl;



}












