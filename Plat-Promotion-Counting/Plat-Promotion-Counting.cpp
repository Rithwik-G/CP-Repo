

#include "bits/stdc++.h"


using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <class T>
using Tree =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

#define s second
#define f first
#define pb push_back

typedef long long ll;

typedef pair<ll, ll> pii;
typedef vector<pii> vpii;

typedef vector<ll> vi;

#define FOR(i, a, b) for (ll i = (a); i<b; i++)


const ll N = 1e5 + 10;
ll v[N];
vi adj[N];
Tree<ll> vals[N];
ll ans[N];

void solve(ll cur = 1) {
	for (auto val: adj[cur]) {
		solve(val);

		if (vals[val].size() > vals[cur].size()) vals[val].swap(vals[cur]);

		for (auto other: vals[val]) vals[cur].insert(other);
	}
	// cout << vals[cur].size() << ' ' << cur << endl;
	ans[cur] = vals[cur].order_of_key(-v[cur]);

	vals[cur].insert(-v[cur]);
}

int main() {
	freopen("promote.in", "r", stdin);
	freopen("promote.out", "w", stdout);

	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	ll n;
	cin >> n;
	FOR(i, 1, n + 1) {
		cin >> v[i];
	}

	FOR(i, 2, n + 1) {
		ll a;
		cin >> a;
		adj[a].pb(i);
	}
	solve();
	FOR(i, 1, n + 1) cout << ans[i] << endl;


}












