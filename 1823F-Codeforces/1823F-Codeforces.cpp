// Source: https://codeforces.com/problemset/problem/1823/F
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

const ll N = 2e5 + 10;
const ll MX = 20;

vi adj[N];
ll lift[N][MX];
ll dep[N];

ll n, s, t;
const ll MOD = 998244353;

void dfs(ll cur, ll prev = 0, ll d = 0) {
	// cout << cur << prev << endl;
	lift[cur][0]=prev;
	dep[cur]=d;
	for (auto val: adj[cur]) {
		if (prev != val) dfs(val, cur, d+1);
	}
}

ll jump(ll a, ll x) {
	FOR(i, 0, MX) if ((1 << i) & x) a = lift[a][i];

	return a;
}

ll lca(ll a, ll b) {
	if (dep[a] < dep[b]) swap(a, b);

	a = jump(a, dep[a]-dep[b]);

	if (a == b) return a;

	for (ll i = MX - 1; i>= 0; i--) {
		if (lift[a][i] != lift[b][i]) {
			a=lift[a][i];
			b=lift[b][i];
		}
	}

	return lift[a][0];


}	

ll deg[N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> n >> s >> t;

	FOR(i, 0, n - 1) {
		ll a, b;
		cin >> a >> b;
		adj[a].pb(b);
		adj[b].pb(a);
		deg[a]++;
		deg[b]++;
	}


	dfs(s);

	FOR(j, 1, MX) FOR(i, 1, n + 1) lift[i][j] = lift[lift[i][j-1]][j-1];

	FOR(i, 1, n + 1) {
		if (i == t) {
			cout << 1 << ' ';
			continue;
		}
		ll LCA = lca(i, t);
		// cout << LCA << endl;
		if (LCA == t) cout << 0 << ' ';
		else cout << ((dep[t] - dep[LCA]) * deg[i]) % MOD << ' ';
	}
	cout << endl;


}












