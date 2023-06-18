// Source: https://www.spoj.com/problems/QTREE3/en/
// 

/*
Replace max() with any associative function for HLD

update() => update(ind, val)
path() => path(st, en)
*/
// Source: http://www.usaco.org/index.php?page=viewproblem2&cpid=921

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

const ll N = 2e5 + 5;

// Start

#define lc i << 1
#define rc (i << 1) + 1

ll n;

pii st[4 * N];
vi adj[N];

ll sz[N];
ll p[N];
ll dep[N];
ll id[N];
ll tp[N];
ll t = 0;
const ll INF = 1e9;

pii comb(pii a, pii b) { // MODIFY COMBINER FUNCTION
	return min(a, b);
}

void up(ll i) {
	st[i] = min(st[lc], st[rc]);
}


void update(ll ind, pii val, ll i = 1, ll l = 0, ll r = n) { // update pos ind with value val
	if (l >= r) return;
	if (r - l == 1) {
		st[i] = val;
		return;
	}

	ll m = (l + r)/2;

	if (m > ind) update(ind, val, lc, l, m); // contained in left child
	else update(ind, val, rc, m, r); // contained in right child

	up(i); // update current index
}

pii query(ll ql, ll qr, ll i = 1, ll l = 0, ll r = n) { // query from [ql, qr)
	
	if (l >= r) return {INF, INF}; // identity
	if (ql <= l && qr >= r) { // fully contained
		return st[i];
	}

	if (r - l == 1) return {INF, INF}; // leaf node

	ll m = (l + r)/2;

	pii acc = {INF, INF}; // SET DEFAULT VALUE

	if (m >= ql) acc = comb(query(ql, qr, lc, l, m), acc);
	if (m <= qr) acc = comb(acc, query(ql, qr, rc, m, r));

	return acc;
}
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

pii path(ll x, ll y) {
	pii ret = {INF, INF};

	while (tp[x] != tp[y]) {
		if (dep[tp[x]] < dep[tp[y]]) swap(x, y);

		ret = comb(ret, query(id[tp[x]], id[x]));
		// cout << query(5, 6) << endl;
		x = p[tp[x]];
	}

	if (dep[x] > dep[y]) swap(x, y);
	ret = comb(ret, query(id[x], id[y]));

	return ret;
}

ll q;
int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin >> n >> q;

	FOR(i, 0, 4*N) st[i]={INF, INF};

	for (ll i = 0; i < n-1; i++) {
		ll a, b;
		cin >> a >> b;

		adj[a].pb(b);
		adj[b].pb(a);
	}	

	dfs_sz(1, 1);
	dfs_hld(1, 1, 1);

	FOR(i, 0, q) {
		ll t;
		cin >> t;
		ll a;
		cin >> a;
		if (t == 0) {
			
			if (query(id[a], id[a] + 1).first != INF) {
				update(id[a], {INF, INF});
			} else {
				update(id[a], {dep[a], a});
			}
		} else {
			ll val = (path(1, a).second);
			if (val == INF) cout << -1 << endl;
			else cout << val << endl;
		}
	}
}












