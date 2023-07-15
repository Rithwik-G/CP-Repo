// Source: http://usaco.org/index.php?page=viewproblem2&cpid=1068

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

const ll N = 3001;

ll dp[2][N][2];
const int MOD = 1e9 + 7;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	
	ll n;
	cin >> n;


	vpii v(2 * n);

	FOR(i, 0, n) {
		cin >> v[i].f;
		v[i].s = 0; // if it is not a cow (cow's should come first)
	}

	FOR(i, n, 2 * n) {
		cin >> v[i].f;
		v[i].s = 1;
	}

	sort(v.begin(), v.end());

	dp[0][0][0] = 1;

	FOR(i, 0, 2*n) {

		int cur_i = (i) % 2;
		
		int nxt_i = (i + 1) % 2;
		memset(dp[nxt_i], 0, sizeof(dp[cur_i]));
		FOR(j, 0, n) {
			FOR(k, 0, 2) {
				if (dp[cur_i][j][k] == 0) continue;
				ll cur = dp[cur_i][j][k];
				if (!v[i].s) { // Cow
					dp[nxt_i][j][1] = (dp[nxt_i][j][1]+cur) % MOD;
					dp[nxt_i][j + 1][k] = (dp[nxt_i][j + 1][k]+cur) % MOD;
				} else {
					if (j > 0) dp[nxt_i][j - 1][k] = (dp[nxt_i][j - 1][k]+j * cur) % MOD;
					if (!k) dp[nxt_i][j][k] = (cur + dp[nxt_i][j][k]) % MOD;
				}
			}
		}
	}

	cout << (dp[2*n % 2][0][1] + dp[2*n % 2][0][0]) % MOD << endl;

}












