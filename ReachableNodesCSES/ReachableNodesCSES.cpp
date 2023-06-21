// Source: https://cses.fi/problemset/task/2138
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

const int N = 5e4 + 10;

bitset<N> b[N];
vi adj[N];

bool v[N];

int n;

void dfs(int cur) {
	v[cur]=true;
	b[cur][cur]=1;
	for (auto val: adj[cur]) {
		if (!v[val]) dfs(val);
		b[cur] |= b[val];
	}
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	int m;
	cin >> n >> m;

	FOR(i, 0, m) {
		int a, b;
		cin >> a >> b;
		adj[a].pb(b);
	}

	for (int i = 1; i <= n; i++) {
		if (!v[i]) { dfs(i); }
	}

	FOR(i, 1, n + 1) cout << b[i].count() << ' ';
	cout << endl;

}












