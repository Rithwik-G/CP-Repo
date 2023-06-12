// Source: https://codeforces.com/gym/102644/problem/F, https://cses.fi/problemset/task/1724
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

const ll SZ = 101;
const ll MOD = 1e9 + 7;

const ll INF = 3e18;

struct Matrix {
	ll a[SZ][SZ];

	void reset() {
		FOR(i, 0, SZ) FOR(j, 0, SZ) a[i][j]=INF;
	}

	Matrix operator *(Matrix other) {
		Matrix product;
		product.reset();
		FOR(i, 0, SZ) 
			FOR(j, 0, SZ)
				FOR(k, 0, SZ)  {
					if (a[i][j] == INF || other.a[j][k] == INF) continue;
					product.a[i][k] = min(product.a[i][k], a[i][j] + other.a[j][k]);
				}
					
				

		return product;
	}
};

Matrix exp(Matrix m, ll k) {
	Matrix ans;
	ans.reset();
	FOR(i, 0, SZ) ans.a[i][i]=0;

	while (k > 0) {
		if (k % 2 == 1) ans = ans*m;
		m = m*m;
		k/=2;
	}

	return ans;
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	Matrix adj;
	adj.reset();


	ll n, m, k;
	cin >> n >> m >> k;

	FOR(i, 0, m) {
		ll a, b, c;
		cin >> a >> b >> c;
		adj.a[b][a]=c;
	}

	Matrix ans = exp(adj, k);
	// ll res = INF;

	// Codeforces
	// FOR(i, 0, SZ) FOR(j, 0, SZ) res = min(res, ans.a[i][j]);
	// if (res == INF) cout << "IMPOSSIBLE" << endl;
	// else cout << res << endl;

	// CSES

	ll res = ans.a[n][1];
	if (res == INF) cout << -1 << endl;
	else cout << res << endl;

}












