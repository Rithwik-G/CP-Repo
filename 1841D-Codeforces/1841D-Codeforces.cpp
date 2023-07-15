// Source: https://codeforces.com/problemset/problem/1841/D
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

const int INF = 1e9+1;
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int t;
	cin >> t;

	while (t--) {
		int n;
		cin >> n;

		vpii v(n);

		FOR(i, 0, n) cin >> v[i].f >> v[i].s;

		sort(v.begin(), v.end());

		vi dp(n + 1, INF);
		dp[0]=0;

		FOR(i, 0, n) {

			dp[i + 1] = min(dp[i + 1], dp[i] + 1);

			FOR(j, i + 1, n) {
				if (v[j].f <= v[i].s) {
					int nxt = lower_bound(v.begin(), v.end(), make_pair(v[j].s, INF)) - v.begin();
					dp[nxt] = min(dp[nxt], dp[i] + (nxt - 2 - i));
				}
			}
		}

		cout << dp[n] << endl;
	}

}












