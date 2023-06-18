// Source: http://www.usaco.org/current/index.php?page=viewproblem2&cpid=576
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

// Start

const ll N = 1e5;

#define lc i << 1
#define rc (i << 1) + 1

ll n;

ll st[4 * N];
ll a[N];

ll comb(ll a, ll b) { // MODIFY COMBINER FUNCTION
	return a+b;
}

void up(ll i) {
	st[i] = comb(st[lc], st[rc]);
}

void build(ll i = 1, ll l = 0, ll r = n) { // build segtree from array a
	if (l>=r) return;
	if (r - l == 1) {
		st[i]=a[l];
		return;
	}

	ll m = (l + r)/2;

	build(lc, l, m);
	build(rc, m, r);
	up(i);
}

void update(ll ind, ll val, ll i = 1, ll l = 0, ll r = n) { // update pos ind with value val
	if (l >= r) return;
	if (r - l == 1) {
		st[i] += val;
		return;
	}

	ll m = (l + r)/2;

	if (m > ind) update(ind, val, lc, l, m); // contained in left child
	else update(ind, val, rc, m, r); // contained in right child

	up(i); // update current index
}

ll query(ll ql, ll qr, ll i = 1, ll l = 0, ll r = n) { // query from [ql, qr)
	
	if (l >= r) return 0; // identity
	if (ql <= l && qr >= r) { // fully contained
		return st[i];
	}

	if (r - l == 1) return 0; // leaf node

	ll m = (l + r)/2;

	ll acc = 0; // SET DEFAULT VALUE

	if (m >= ql) acc = comb(query(ql, qr, lc, l, m), acc);
	if (m <= qr) acc = comb(acc, query(ql, qr, rc, m, r));

	return acc;
}



vi adj[N];

ll sz[N];
ll p[N];
ll dep[N];
ll id[N];
ll tp[N];
ll t = 0;

ll dfs_sz(ll cur, ll par) {
	sz[cur] = 1;
	p[cur] = par;
	for (ll chi : adj[cur]) {
		if (chi == par) continue;
		dep[chi] = dep[cur] + 1;
		p[chi] = cur;
		sz[cur] += dfs_sz(chi, cur);
	}
	return sz[cur];
}
// ll v[N];
void dfs_hld(ll cur, ll p, ll top) {
	tp[cur] = top;
	id[cur]=t++;
	// cout << cur << endl;
	// update(cur, v[cur]);
	ll comb_sz = -1;
	ll comb_val = -1;
	for (ll x: adj[cur]) {
		if (x != p) {
			if (sz[x] > comb_sz) {
				comb_sz = sz[x];
				comb_val = x;
			}
		}
	}
	if (comb_val == -1) return;
	dfs_hld(comb_val, cur, top);
	for (ll x: adj[cur]) {
		if (x != p && x != comb_val) {
			dfs_hld(x, cur, x);
		}
	}
}


void updatePath(ll x, ll y, ll val) {
	while (tp[x] != tp[y]) {
		if (dep[tp[x]] < dep[tp[y]]) swap(x, y);
		// cout << id[x] << id[tp[x]] << endl;
		update(id[tp[x]], val);
		update(id[x] + 1, -val);
		x = p[tp[x]];
	}
	// cout << y << endl;
	if (dep[x] > dep[y]) swap(x, y);
	update(id[x], val);
	update(id[y] + 1, -val);


}


int main() {
	freopen("maxflow.in", "r", stdin);
	freopen("maxflow.out", "w", stdout);

	cin.tie(0)->sync_with_stdio(0);
	ll q;
	cin >> n >> q;

	for (ll i = 0; i < n-1; i++) {
		ll a, b;
		cin >> a >> b;

		adj[a].pb(b);
		adj[b].pb(a);
	}	

	dfs_sz(1, 1);
	dfs_hld(1, 1, 1);

	FOR(i, 0, q) {
		ll a, b;
		cin >> a >> b;
		updatePath(a, b, 1);
	}
	ll ans = 0;
	FOR(i, 0, n) {
		ans = max(ans, query(0, i+1));
	}
	cout << ans << endl;
}












