

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

const int N = 3e5;
const ll MX = 100;
ll v[N];
int dp[N][MX];

int main() {
	// freopen("262144.in", "r", stdin);
	// freopen("262144.out", "w", stdout);

	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n;
	cin >> n;
	ll ans = 0;
	FOR(i, 1, n + 1) {
		cin >> v[i];
		dp[i][v[i]]=i+1;
		ans = max(ans, v[i]);
	}

	FOR(j, 1, 4) {
		FOR(i, 1, n + 1) {
			if (dp[i][j-1] == 0) continue;
			dp[i][j] = dp[dp[i][j-1]][j-1];

			// cout << dp[i][j-1] << dp[dp[i][j-1]][j-1] << endl;
			if (dp[i][j] > 0) ans = max(ans, j);
		}
	}

	cout << ans << endl;



}












