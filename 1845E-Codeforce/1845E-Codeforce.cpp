// Source: https://codeforces.com/problemset/problem/1845/E
// 

#include "bits/stdc++.h"

using namespace std;

#define s second
#define f first
#define pb push_back

typedef long long ll;

typedef pair<int, int> pii;
typedef vector<pii> vpii;

typedef vector<int> vi;

#define FOR(i, a, b) for (int i = (a); i<b; i++)


const int N = 1505;
const int MOD = 1e9 + 7;


int lim = 55;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, K;
	cin >> n >> K;

	vi v(n);

	vector<vector<vector<int>>> dp(2, vector<vector<int>>(2 * lim + 1, vector<int>(K + 1)));


	FOR(i, 0, n) cin >> v[i];


	dp[0][lim][0] = 1;

	FOR(ii, 0, n) {
		int i = (i) % 2;
		int nxt = (i + 1) % 2;

		dp[nxt] = vector<vector<int>>(2 * lim + 1, vector<int>(K + 1));

		FOR(j, 0, 2 * lim + 1) {
			FOR(k, 0, K + 1) {
				if (dp[i][j][k] == 0) continue;

				FOR(z, 0, 2) {
					int nj = j + z - v[i];
					int nk = k + abs(nj - lim);
					if (nk <= K) dp[nxt][nj][nk] += dp[i][j][k];
				}

				cout << ii << j << k << dp[i][j][k] << endl;
				

			}
		}
	}
	int ans = 0;
	for (int i = K; i >= 0; i-=2) {
		// cout << i << endl;
		ans += dp[(n + 1) % 2][lim][i];
	}
	cout << ans << endl;


}












