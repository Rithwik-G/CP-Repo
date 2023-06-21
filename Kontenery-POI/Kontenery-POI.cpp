// Source: https://szkopul.edu.pl/problemset/problem/oNnWY6ZuzzhvG-jCmijiXkIk/site/?key=statement
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
const int sqrt_n = 300;
const int max_n = 1e5 + 10;
int vals[max_n];
int dp[max_n + sqrt_n][sqrt_n];
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, k;
	cin >> n >> k;

	while (k--) {
		int a, l, d;
		cin >> a >> l >> d;

		if (d >= sqrt_n) {
			for (int i = 0; i < l; i++) vals[a + i * d]++;
		} else {
			dp[a][d]++;
			dp[a + l * d][d]--;
		}

	}

	FOR(j, 1, sqrt_n) FOR(i, j, n + 1) dp[i][j] += dp[i-j][j];

	FOR(i, 1, n +1) {
		FOR(j, 1, sqrt_n) vals[i] += dp[i][j];

		cout << vals[i] << ' ';
	}
	cout << endl;

}












