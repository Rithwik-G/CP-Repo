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
	vi vals;

	for (auto val: adj[cur]) {
		if (val != p) {
			ll poss = dfs(val, cur);
			if (poss == -1) return -1;

			vals.pb(poss + 1);
		}
	}

	sort(vals.begin(), vals.end());
	bool evenPoss = false;
	if (vals.size() % 2 == 0) {
		evenPoss = true;
		ll l = 0;
		ll r = vals.size() - 1;
		while (l < r) {
			if (vals[l] + vals[r] < k) {
				evenPoss = false;
				break;
			}
			l++;
			r--;
		}

	}

	if (vals.size() == 1) return vals[0];

	ll lo = 0;
	ll hi = vals.size()-1;
	bool works = false;
	ll best;
	while (lo < hi) {
		bool bad = false;
		ll m = (hi + lo + 1)/2;


		int l= 0;
		int r = vals.size() - 1;

		while (r > l) {
			if (vals[l] >= k) break;

			if (vals[l] + vals[r] < k) {
				bad= true;
				break;
			}

			l++;
			r--;

			if (l == m) l++;
			if (r == m) r--;
		}
		if (l == r && vals[l] < k) bad= true;
		// multiset<int> st;
		// for (auto val: vals) st.insert(val);

		// while (st.size() > 0) {
		// 	ll val = *st.begin();

		// 	st.erase(st.begin());
		// 	if (val >= k) continue;

		// 	auto it = st.lower_bound(k - val);
		// 	if (it == st.end()) {
		// 		bad = true;
		// 		break;
		// 	}

		// 	st.erase(it);
		// }


		if (bad) hi = m - 1;
		else {
			works = true;
			best = vals[m];
			lo = m;
		}
	}

	// cout << evenPoss << endl;
	if (!works) {
		if (evenPoss) return 0;
		return -1;
	}
	else {
		// cout << k << best << endl;
		return best;
	}

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

	while (lo < hi) {

		k = (lo + hi + 1)/2;

		ll val = dfs(1);
		if (val >= k || val == 0) lo = k;
		else hi = k-1;
	}
	cout << lo << endl;

	

}












