/*
Replace max() with any associative function for HLD

update() => update(ind, val)
path() => path(st, en)
*/
// Source: http://usaco.org/index.php?page=viewproblem2&cpid=102

#include "bits/stdc++.h"


using namespace std;

#define s second
#define f first
#define pb push_back

typedef long long ll;

typedef pair<int, int> pii;
typedef vector<pii> vpii;

typedef vector<int> vi;

#define FOR(i, a, b) for (int i = (a); i<b; i++)

const int N = 1e5 + 5;

// Start

// const int N = 1e5;

#define lc i << 1
#define rc (i << 1) + 1

int n;

int st[4 * N];
int a[N];

int comb(int a, int b) { // MODIFY COMBINER FUNCTION
	return a+b;
}

void up(int i) {
	st[i] = comb(st[lc], st[rc]);
}


void update(int ind, int val, int i = 1, int l = 0, int r = n) { // update pos ind with value val
	if (l >= r) return;
	if (r - l == 1) {
		st[i] += val;
		return;
	}

	int m = (l + r)/2;

	if (m > ind) update(ind, val, lc, l, m); // contained in left child
	else update(ind, val, rc, m, r); // contained in right child

	up(i); // update current index
}

int query(int ql, int qr, int i = 1, int l = 0, int r = n) { // query from [ql, qr)
	
	if (l >= r) return 0; // identity
	if (ql <= l && qr >= r) { // fully contained
		return st[i];
	}

	if (r - l == 1) return 0; // leaf node

	int m = (l + r)/2;

	int acc = 0; // SET DEFAULT VALUE

	if (m >= ql) acc = comb(query(ql, qr, lc, l, m), acc);
	if (m <= qr) acc = comb(acc, query(ql, qr, rc, m, r));

	return acc;
}

vi adj[N];

int sz[N];
int p[N];
int dep[N];
int id[N];
int tp[N];
int t = 0;

int dfs_sz(int cur, int par) {
	sz[cur] = 1;
	p[cur] = par;
	for (int chi : adj[cur]) {
		if (chi == par) continue;
		dep[chi] = dep[cur] + 1;
		p[chi] = cur;
		sz[cur] += dfs_sz(chi, cur);
	}
	return sz[cur];
}
// int v[N];
void dfs_hld(int cur, int p, int top) {
	tp[cur] = top;
	id[cur]=t++;
	// cout << cur << endl;
	// update(cur, v[cur]);
	int comb_sz = -1;
	int comb_val = -1;
	for (int x: adj[cur]) {
		if (x != p) {
			if (sz[x] > comb_sz) {
				comb_sz = sz[x];
				comb_val = x;
			}
		}
	}
	if (comb_val == -1) return;
	dfs_hld(comb_val, cur, top);
	for (int x: adj[cur]) {
		if (x != p && x != comb_val) {
			dfs_hld(x, cur, x);
		}
	}
}

int value(int x) {
	return query(0, id[x] + 1);
}

void updatePath(int x, int y, int val) {
	while (tp[x] != tp[y]) {
		if (dep[tp[x]] < dep[tp[y]]) swap(x, y);
		// cout << id[x] << id[tp[x]] << endl;
		update(id[tp[x]], val);
		update(id[x] + 1, -val);
		// cout << id[tp[x]] << id[x] + 1 << endl;
		x = p[tp[x]];
	}
	// cout << y << endl;
	if (dep[x] > dep[y]) swap(x, y);
	// update(id[x] + 1, id[y] + 1, val); // exclude LCA
	cout << id[x] + 1 << id[y] + 1 << endl;
	update(id[x] + 1, val);
	update(id[y] + 1, -val);
	// update(id[x], id[x] + 1, -val);

}

int q;
int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin >> n >> q;

	// for (int i = 1; i <= n; i++) cin >> a[i];
	for (int i = 0; i < n-1; i++) {
		int a, b;
		cin >> a >> b;

		adj[a].pb(b);
		adj[b].pb(a);
	}	

	dfs_sz(1, 1);
	dfs_hld(1, 1, 1);
	// cout << q << endl;
	FOR(i, 0, q) {
		char t;
		cin >> t;
		if (t == 'P') {
			int a, b;
			cin >> a >> b;
			updatePath(a, b, 1);
		} else {
			int a, b;
			cin >> a >> b;

			if (dep[a] > dep[b]) swap(a, b);
			cout << value(b) << endl;
		}
	}
}