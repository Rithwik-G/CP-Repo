// Source: https://codeforces.com/gym/102644/problem/E
// AC

#include "bits/stdc++.h"

using namespace std;

#define s second
#define f first
#define pb push_back

typedef unsigned int ll;

typedef pair<ll, ll> pii;
typedef vector<pii> vpii;

typedef vector<ll> vi;

#define FOR(i, a, b) for (int i = (a); i<b; i++)

const ll SZ = 65;
const ll MOD = 1e9 + 7;

struct Matrix {
	unsigned int a[SZ][SZ];

	void reset() {
		FOR(i, 0, SZ) FOR(j, 0, SZ) a[i][j]=0;
	}

	Matrix operator *(Matrix other) {
		Matrix product;
		product.reset()
		FOR(i, 0, SZ) 
			FOR(j, 0, SZ)
				FOR(k, 0, SZ) {
					product.a[i][k] = (product.a[i][k] + a[i][j] * other.a[j][k]);
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


	ll n;
	cin >> n;

	Matrix m;
	m.reset();

	FOR(xi, 0, 8) {
		FOR(yi, 0, 8) {
			FOR(xj, 0, 8) {
				FOR(yj, 0, 8) {
					if ((abs(yj-yi) == 1 && abs(xj-xi)==2) || (abs(yj-yi) == 2 && abs(xj-xi)==1)) m.a[8*xi + yi][8*xj + yj] = 1;

				}
			}
		}
	}

	FOR(i, 0, 65) {
		m.a[64][i] = 1;
	}
	Matrix ans = exp(m, n + 1);
	// int res = 0;
	// FOR(i, 0, 64) {
	// 	res += ans.a[64][i];
	// }
	cout << ans.a[64][0] << endl;
}












