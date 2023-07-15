// Source: http://www.usaco.org/index.php?page=viewproblem2&cpid=972
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

template<class T> bool ckmax(T& a, const T& b) { 
	return a < b ? a = b, 1 : 0; }

const int N = 301;

int mx[N][N][N];
int dp[N][N];



int main() {
	freopen("pieaters.in", "r", stdin);
	freopen("pieaters.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m;
	cin >> n >> m;



	FOR(i, 0, m) {
		int l, r, w;
		cin >> w >> l >> r;

		FOR(i, l, r + 1) ckmax(mx[l][r][i], w);
	}

	for (int le = 1; le <= n; le++) {
		for (int l = 1; l + le <= n; l++) {
			int r = le + l;

			for (int i = l; i <= r; i++) {

				ckmax(mx[l][r][i], mx[l + 1][r][i]);
				ckmax(mx[l][r][i], mx[l][r - 1][i]);
				// cout << l << r << i << mx[l][r][i] << endl;
			}
		}
	}

	for (int le = 0; le <= n; le++) {
		for (int l = 1; l + le <= n; l++) {
			int r = le + l;

			for (int i = l; i < r; i++) {
				ckmax(dp[l][r], dp[l][i] + dp[i + 1][r]);
			}

			for (int i = l; i <= r; i++) {
				// cout << l << r << mx[l][r][i] << endl;
				ckmax(dp[l][r], dp[l][i - 1] + dp[i + 1][r] + mx[l][r][i]);
			}

			// cout << l << r << dp[l][r] << endl;
		}
	}

	cout << dp[1][n] << endl;

}












