// Source: https://codeforces.com/contest/1826/problem/E
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
const ll N = 5010;
bitset<N> adj[N];

vi toposort;
bool v[N];
vi nxt[N];
vi pre[N];
ll m, n;
void dfs(ll cur) {
	v[cur]=true;
	FOR(i, 0, n) if(adj[i][cur] && !v[i]) dfs(i);

	toposort.pb(cur);
}
ll dp[N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> m >> n;

	vi cost(n);
	FOR(i, 0, n) {
		adj[i].set();
		cin >> cost[i];
	}

	vector<vpii> ratings(m, vpii(n));

	FOR(i, 0, m) {

		FOR(j, 0, n) {
			cin >> ratings[i][j].f;
			ratings[i][j].s = j;
		}
	}

	bitset<N> cur_bs;
	bitset<N> temp_bs;

	FOR(city, 0, m) {
		sort(ratings[city].begin(), ratings[city].end());

		cur_bs.reset();
		temp_bs.reset(); // bug - too much memory	
		temp_bs[ratings[city][0].s]=1;
		adj[ratings[city][0].s] &= cur_bs;
		FOR(i, 1, n) {
			if (ratings[city][i].f != ratings[city][i-1].f) cur_bs |= temp_bs;
			adj[ratings[city][i].s] &= cur_bs;
			temp_bs[ratings[city][i].s]=1;
			
		}
	}
	// FOR(i, 0, n) {
	// 	FOR(j, 0, n) {
	// 		if (adj[i][j]) {
	// 			nxt[j].pb(i);
	// 			pre[i].pb(j);
	// 		}
	// 	}
	// }

	FOR(i, 0, n) if (!v[i]) dfs(i);



	reverse(toposort.begin(), toposort.end());
	ll ans = 0;

	FOR(j, 0, n) {

		int i = toposort[j];

		ll best = 0;
		FOR(bef, 0, n) {
			if (adj[i][bef]) best = max(best, dp[bef]);
		}
		dp[i] = best + cost[i];
		ans = max(ans, dp[i]);
	}

	cout << ans  << endl;
	

}












