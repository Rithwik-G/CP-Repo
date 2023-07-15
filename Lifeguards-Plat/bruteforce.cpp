// Source: http://www.usaco.org/index.php?page=viewproblem2&cpid=792
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

const ll N = 1e5 + 10;
const ll K = 101;

template<class T> bool ckmax(T& a, const T& b) { 
	return a < b ? a = b, 1 : 0; }

ll dp[N][K];
ll pref_dp[N][K];

int main() {
	freopen("lifeguards.in", "r", stdin);
	freopen("lifeguards.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	ll n, k;
	cin >> n >> k;

	vpii ranges(n);

	FOR(i, 0, n) {
		cin >> ranges[i].f >> ranges[i].s;
		ranges[i].s = -ranges[i].s;
	}

	sort(ranges.begin(), ranges.end());

	ll end = 0;

	vpii final;

	FOR(i, 0, n) {
		if (-ranges[i].s <= end) {
			k--;
		} else {
			final.pb({ranges[i].f, -ranges[i].s});
			end = -ranges[i].s;
		}
	}
	
	k = max(k, 0ll);
	ll ans = 0;
	for (int i = 0; i < final.size(); i++) {
		for (int j = k; j >= 0; j--) {
			if (j != k) ckmax(dp[i][j], dp[i][j+1]);
			if (j >= i + 1) continue;
			if (j == i) {
				dp[i][j] = final[i].s - final[i].f;
			} else 	{
				for (int prev = 0; prev <= j; prev++) {

					if (final[i].f > final[i-prev-1].s) ckmax(dp[i][j], dp[i-prev-1][j-prev] + final[i].s - final[i].f);
					else ckmax(dp[i][j], dp[i-prev-1][j-prev] + final[i].s - final[i-prev-1].s);
				}
			}

			if (n - i - 1 + j >= k) ans = max(ans, dp[i][j]);
		}
	}

	cout << ans << endl;



}












