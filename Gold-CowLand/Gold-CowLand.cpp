// Source: http://www.usaco.org/index.php?page=viewproblem2&cpid=921

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

int comb(int a, int b) {
	return a ^ b;
}

void update(int idx, int val) {
	idx=id[idx];
	st[idx += n] = val;
	for (idx /= 2; idx; idx /= 2) st[idx] = comb(st[2 * idx], st[2 * idx + 1]);
}

int query(int lo, int hi) {
	int ra = 0, rb = 0;
	for (lo += n, hi += n + 1; lo < hi; lo /= 2, hi /= 2) {
		if (lo & 1) ra = comb(ra, st[lo++]);
		if (hi & 1) rb = comb(rb, st[--hi]);
	}
	return comb(ra, rb);
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
	update(cur, v[cur]);
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

int path(int x, int y) {
	int ret = 0;

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
int q;
int main() {
	freopen("cowland.in", "r", stdin);
	freopen("cowland.out", "w", stdout);

	cin.tie(0)->sync_with_stdio(0);
	cin >> n >> q;

	for (int i = 1; i <= n; i++) cin >> v[i];
	for (int i = 0; i < n-1; i++) {
		int a, b;
		cin >> a >> b;

		adj[a].pb(b);
		adj[b].pb(a);
	}	

	dfs_sz(1, 1);
	dfs_hld(1, 1, 1);
	// cout << path(0, 4) << endl;
	FOR(i, 0, q) {
		int a, b, c;
		cin >> a >> b >> c;

		if (a == 1) {
			update(b, c);
		} else {

			cout << path(b, c) << endl;
		}
	}
}












