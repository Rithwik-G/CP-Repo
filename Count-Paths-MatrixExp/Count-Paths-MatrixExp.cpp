// Source: https://codeforces.com/gym/102644/problem/D, https://cses.fi/problemset/result/6219683/
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

const ll SZ = 101;
const ll MOD = 1e9 + 7;

struct Matrix {
	long long a[SZ][SZ];

	void reset() {
		FOR(i, 0, SZ) FOR(j, 0, SZ) a[i][j]=0;
	}

	Matrix operator *(Matrix other) {
		Matrix product{{{0, 0}, {0, 0}}};
		FOR(i, 0, SZ) 
			FOR(j, 0, SZ)
				FOR(k, 0, SZ) {
					product.a[i][k] = (product.a[i][k] + a[i][j] * other.a[j][k]) % MOD;
					// cout << i << ' ' << j << ' ' << k << ' ' << product.a[i][k] << ' ' << a[i][j] << endl;
				}

		return product;
	}
};

Matrix exp(Matrix m, int k) {
	Matrix ans;
	ans.reset();
	FOR(i, 0, SZ) ans.a[i][i]=1;

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
	int n, m, k;
	cin >> n >> m >> k;
	Matrix adj;
	adj.reset();
	FOR(i, 0, m) {
		int a, b;
		cin >> a >> b;
		adj.a[b][a]+=1;
	}

	Matrix ans = exp(adj, k);

	int res = 0;


	// CODEFORCES
	// FOR(i, 0, SZ) FOR(j, 0, SZ) res = (res + ans.a[i][j]) % MOD;

	// cout << res << endl;

	cout << ans.a[n][1] << endl; // CSES

}












