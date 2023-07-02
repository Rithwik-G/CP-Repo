// Source: http://www.usaco.org/index.php?page=feb20results
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

const ll N = 2e5  + 10;

vi adj[N];
ll k;

ll dfs(ll cur, ll p = -1) {
	if (adj[cur].size() == 1 && cur != 1) return 0; 
	vi vals;

	for (auto val: adj[cur]) {
		if (val != p) {
			ll poss = dfs(val, cur);
			if (poss == -1) return -1;

			vals.pb(poss + 1);
		}
	}
	sort(vals.begin(), vals.end());
	if (vals.size() % 2 == 0) {
		ll l = 0;
		ll r = vals.size() - 1;
		while (l < r) {
			if (vals[l] + vals[r] < k) {
				return -1;
				break;
			}
			l++;
			r--;
		}

		return 0;
	}

	if (vals.size() == 1) return vals[0];

	ll lo = 0;
	ll hi = vals.size();
	bool works = false;
	ll best;
	while (lo < hi) {
		bool bad = false;
		ll m = (hi + lo + 1)/2;

		ll l = 0;
		ll r = vals.size() - 1;
		while (l < r) {
			if (vals[l] + vals[r] < k) {
				bad = true;
				break;
			}
			l++;
			r--;
			if (r == m) r--;
			if (l == m) l++;
		}

		if (bad) hi = m - 1;
		else {
			works = true;
			best = vals[m];
			lo = m;
		}
	}

	if (!works) return -1;
	else return best;





	// while (vals.size() > 1) {
	// 	ll val = *vals.begin();

	// 	vals.erase(vals.begin());
	// 	if (val >= k) continue;

	// 	auto it = vals.lower_bound(k - val);
	// 	if (it == vals.end()) return -1;

		
	// 	vals.erase(it);
	// }

	// if (vals.size() == 0) return 0;
	// return (*vals.begin());

}

int main() {
	// freopen("deleg.in", "r", stdin);
	// freopen("deleg.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	ll n;
	cin >> n;
	ll a, b;
	FOR(i, 0, n-1) {
		cin >> a >> b;
		adj[a].pb(b);
		adj[b].pb(a);
	}

	ll lo = 1;
	ll hi = n;
	k = 3125;
	cout << dfs(1) << endl;
	while (lo < hi) {

		k = (lo + hi + 1)/2;
		cout << lo << hi << endl;
		ll val = dfs(1);
		if (val >= k || val == 0) lo = k;
		else hi = k-1;
	}
	cout << lo << endl;

	

}












