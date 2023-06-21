// Source: https://codeforces.com/contest/1254/problem/D
//
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


#define lc i << 1
#define rc (i << 1) + 1

const ll N = 150010;
const ll MOD = 998244353;
ll n;

ll st[4 * N];
vi adj[N];

ll sz[N];
ll p[N];
ll dep[N];
ll id[N];
ll tp[N];
ll t = 0;

ll binpow(ll x, ll n, ll m) {
	assert(n >= 0);
	x %= m;  // note: m * m must be less than 2^63 to avoid ll overflow
	ll res = 1;
	while (n > 0) {
		if (n % 2 == 1) { res = res * x % m; }
		x = x * x % m;
		n /= 2;
	}
	return res;
}

ll rev[N];
ll comb(ll a, ll b) { // MODIFY COMBINER FUNCTION
	return a + b % MOD;
}

void up(ll i) {
	st[i] = comb(st[lc], st[rc]);
}


void update(ll ind, ll val, ll i, ll l, ll r) { // update pos ind with value val
	if (l >= r) return;
	if (r - l == 1) {
		st[i] += val;
		// cout << ' ' << i << l << r << val << endl;
		return;
	}

	ll m = (l + r)/2;

	if (m > ind) update(ind, val, lc, l, m); // contained in left child
	else update(ind, val, rc, m, r); // contained in right child

	up(i); // update current index
}

ll query(ll ql, ll qr, ll i, ll l, ll r) { // query from [ql, qr)
	
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

void update(ll l, ll r, ll val) {
	update(l, val, 1, 0, n);
	if (r != n) update(r, -val, 1, 0, n); // LEARNING!
}

ll query(ll pos) {
	return query(0, pos + 1, 1, 0, n);
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
vi pos[N];

void dfs_hld(ll cur, ll p) {

	pos[cur].pb(t);
	id[cur]=t++;
	rev[t-1]=cur;
	// cout << cur << t-1 << endl;
	for (ll x: adj[cur]) {
		if (x != p) {
			dfs_hld(x, cur);
			pos[cur].pb(t-1);
			// cout << cur << t -1 << endl;
			// cout << cur << t << endl;
		}
	}
}

ll q;
ll deg[N];
ll weight[N];
int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin >> n >> q;
	ll inv_n = binpow(n, MOD-2, MOD);
	// cout << inv_n << endl;	
	// inv_n = 1;
	// FOR(i, 0, *N) st[i]={INF, INF};

	for (ll i = 0; i < n-1; i++) {
		ll a, b;
		cin >> a >> b;

		adj[a].pb(b);
		adj[b].pb(a);
		deg[a]++;
		deg[b]++;
	}	

	vi heavy;

	FOR(i, 1, n + 1) {
		if (deg[i] * deg[i] >= n) heavy.pb(i);
	}

	dfs_sz(1, 1);
	dfs_hld(1, 1);

	FOR(i, 0, q) {
		ll t;
		cin >> t;

		if (t == 1) {
			ll v, d;
			cin >> v >> d;
			weight[v] += d;
			// cout << id[v] << endl;
			update(id[v], id[v] + 1, d);
			// cout << query(1) << endl; 
			if (deg[v] * deg[v] < n) { // not heavy
				for (auto val: adj[v]) if (val != p[v]) {
					update(pos[val][0], pos[val].back() + 1, (n - sz[val]) * d % MOD * inv_n % MOD );// mult inverse
					// cout << query(4) << endl;
				}

				if (v == 1) continue;

				update(0, pos[v][0], sz[v] * d % MOD * inv_n % MOD);
				update(pos[v].back(), n, sz[v] * d % MOD * inv_n % MOD);
			}

		} else {
			ll v;
			cin >> v;

			ll ans = query(id[v]);
			// cout << ans << endl;
			// cout << id[v] << endl;
			for (auto h: heavy) {
				if (h == v) {continue;}
				// cout << h << endl;
				auto it = lower_bound(pos[h].begin(), pos[h].end(), pos[v][0]);

				if (it == pos[h].begin() || it == pos[h].end()) ans += ((sz[h] * weight[h]) % MOD * inv_n) % MOD;
				else {
					it--;
					ans += ((n - sz[rev[(*it)] + 1]) * weight[h] % MOD * inv_n) % MOD;
				}

			}

			cout << ans % MOD << endl;
		}
	}
}












