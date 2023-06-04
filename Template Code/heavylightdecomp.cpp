/*
Replace max() with any associative function for HLD

update() => update(a, b)
path() => path(a, b)
*/


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

const int N = 2e5 + 5;

vi adj[N];
int n;

int st[4*N];
int sz[N];
int p[N];
int dep[N];
int id[N];
int tp[N];
int t = 0;
void update(int idx, int val) {
	idx=id[idx];
	st[idx += n] = val;
	for (idx /= 2; idx; idx /= 2) st[idx] = max(st[2 * idx], st[2 * idx + 1]);
}

int query(int lo, int hi) {
	int ra = 0, rb = 0;
	for (lo += n, hi += n + 1; lo < hi; lo /= 2, hi /= 2) {
		if (lo & 1) ra = max(ra, st[lo++]);
		if (hi & 1) rb = max(rb, st[--hi]);
	}
	return max(ra, rb);
}

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
int v[N];
void dfs_hld(int cur, int p, int top) {
	tp[cur] = top;
	id[cur]=t++;
	// cout << cur << endl;
	update(id[cur], v[cur]);
	int max_sz = -1;
	int max_val = -1;
	for (int x: adj[cur]) {
		if (x != p) {
			if (sz[x] > max_sz) {
				max_sz = sz[x];
				max_val = x;
			}
		}
	}
	if (max_val == -1) return;
	dfs_hld(max_val, cur, top);
	for (int x: adj[cur]) {
		if (x != p && x != max_val) {
			dfs_hld(x, cur, x);
		}
	}
}

int path(int x, int y) {
	int ret = 0;

	while (tp[x] != tp[y]) {
		if (dep[tp[x]] < dep[tp[y]]) swap(x, y);

		ret = max(ret, query(id[tp[x]], id[x]));
		x = p[tp[x]];
	}

	if (dep[x] > dep[y]) swap(x, y);
	ret = max(ret, query(id[x], id[y]));

	return ret;
}

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin >> n;

	for (int i = 0; i < n; i++) cin >> v[i];
	for (int i = 0; i < n-1; i++) {
		int a, b;
		cin >> a >> b;
		a--;b--;
		adj[a].pb(b);
		adj[b].pb(a);
	}	

	dfs_sz(1, 1);
	dfs_hld(1, 1, 1);
}