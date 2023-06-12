// Source: https://codeforces.com/gym/102644/problem/C, https://cses.fi/problemset/task/1722

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

const ll SZ = 2;
const ll MOD = 1e9 + 7;

struct Matrix {
	long long a[SZ][SZ];

	Matrix operator *(Matrix other) {
		Matrix product{{{0, 0}, {0, 0}}};
		FOR(i, 0, SZ) 
			FOR(j, 0, SZ)
				FOR(k, 0, SZ) {
					product.a[i][k] = (product.a[i][k] + a[i][j] * other.a[j][k]) % MOD;
				}

		return product;
	}
};


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	Matrix m{{{0, 1}, {1, 1}}};

	Matrix ans{{{1, 0}, {0, 1}}};

	ll n;
	cin >> n;

	while (n > 0) {
		if (n % 2 == 1) ans = ans*m;
		m = m*m;
		n/=2;
	}

	cout << ans.a[0][1] << endl;

}












