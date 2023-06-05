

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


const ll N = 1e5 + 10;
const ll MX = 20;
const ll INF = 1e17;

pii e[N];
vpii adj[N];

ll d[N];
ll anc[N][MX];
ll dist[N][MX];
ll dist2[N][MX];
bool shop[N];
ll subt_dist[N];



ll n, s, q, se;

ll jmp(ll x, ll d) {
	if (d < 0) return x;
	for (ll i = MX-1; i>= 0; i--) if ((1 << i) & (d)) x = anc[x][i];

	return x;
}

ll best_shop(ll x, ll d) {
	ll best = subt_dist[x];
	ll acc = 0;
	for (ll i = MX-1; i>= 0; i--) {
		if ((1 << i) & (d)) {
			best = min(best, acc + dist2[x][i]);
			acc += dist[x][i];
			x = anc[x][i];
			// cout << x << endl;
		}
	}
	return best;
}
int p[N];
void find_d(ll cur = se, ll pr = 0, ll w = 0) {
	FOR(i, 0, MX) {
		dist2[cur][i]=INF;
	}
	ll i = cur;
	if (shop[cur]) {
		subt_dist[i]=0;
	}
	else {
		subt_dist[i] = INF;
	}
	// if (shop[pr]) {
	// 	dist2[i][0] = w;
	// }
	// else {
	// 	dist2[i][0]=INF;
	// }
	// cout << w << endl;
	anc[cur][0]=pr;
	dist[cur][0]=w;
	for (auto val: adj[cur]) {
		if (val.f != pr) {
			d[val.f] = d[cur] + 1;
			find_d(val.f, cur, val.s);
			subt_dist[i] = min((ll) subt_dist[i], subt_dist[val.f]+val.s);
		}
	}
	p[i]=pr;
	dist2[i][0] = w;
	
}

int main() {
	FOR(i, 0, MX) {
		dist2[0][i]=INF;
	}
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> n >> s >> q >> se;
	ll w;
	FOR(i, 0, n - 1) {
		cin >> e[i].f >> e[i].s >> w;

		adj[e[i].f].pb({e[i].s, w});
		adj[e[i].s].pb({e[i].f, w});
	}

	FOR(i, 0, s) {
		cin >> w;
		shop[w]=true;
	}



	find_d();

	FOR(i, 1, n + 1) {
		dist2[i][0]+=subt_dist[p[i]];
	}

	FOR(j, 1, MX) FOR(i, 1, n + 1) anc[i][j] = anc[anc[i][j-1]][j-1];
	FOR(j, 1, MX) FOR(i, 1, n + 1) dist[i][j] = dist[anc[i][j-1]][j-1] + dist[i][j-1];
	// FOR(i, 1, n + 1) dist2[i][0] = subt_dist[p[i]];
	FOR(j, 1, MX) FOR(i, 1, n + 1) dist2[i][j] = min(dist2[i][j-1], dist[i][j-1] + dist2[anc[i][j-1]][j-1]);

	FOR(i, 0, q) {
		ll a, r;
		cin >> a >> r;
		a--;
		ll v1, v2;
		tie(v1, v2) = e[a];

		if (d[v1] < d[v2]) swap(v1, v2);

		if (jmp(r, d[r]-d[v1]) == v1) {
			ll act = best_shop(r, d[r]-d[v1]);
			if (act == INF) cout << "oo" << endl;
			else cout << act << endl;
		} else {
			cout << "escaped" << endl; 
		}
	}

}












