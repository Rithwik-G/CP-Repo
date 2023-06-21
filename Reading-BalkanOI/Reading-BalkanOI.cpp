// Source: https://www.acmicpc.net/problem/7081
// Result:

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

const ll SZ = 150;
const ll MOD = 1e9 + 7;

struct Matrix {
	long long a[SZ][SZ];

	void reset() {
		FOR(i, 0, SZ) FOR(j, 0, SZ) a[i][j]=0;
	}

	Matrix operator *(Matrix other) {
		Matrix product;
		product.reset();

		FOR(i, 0, SZ) 
			FOR(j, 0, SZ)
				FOR(k, 0, SZ) {
					product.a[i][k] = (product.a[i][k] + a[i][j] * other.a[j][k]) % MOD;
					// cout << i << ' ' << j << ' ' << k << ' ' << product.a[i][k] << ' ' << a[i][j] << endl;
				}

		return product;
	}
};

Matrix exp(Matrix m, ll k) {
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

	ll n, m;
	cin >> n >> m;

	Matrix adj;
	adj.reset();

	FOR(i, 0, 27) FOR(j, 0, 27) adj.a[i * 5][j * 5] = 1;

	FOR(i, 0, 27) FOR(c, 1, 5) adj.a[i * 5 + c][i * 5 + c - 1] = 1;

	FOR(i, 1, 27) adj.a[5*i][0] = 1;



	adj.a[0][0]=1;

	FOR(i, 0, m) {
		char l1, l2;
		ll w;
		cin >> l1 >> l2 >> w;
		ll a = l1 - 'a' + 1;
		ll b = l2 - 'a' + 1;
		adj.a[5 * a][5*b] = adj.a[5 * b][5*a] = 0;
		adj.a[5 * a][5 * b + w - 1] = 1;
		adj.a[5 * b][5 * a + w - 1] = 1;
	}

	Matrix ans = exp(adj, n + 1);

	ll res = 0;

	FOR(i, 0, 26) {
		res = (res+ans.a[5*i][0]) % MOD;
	}



	cout << res << endl;



}

