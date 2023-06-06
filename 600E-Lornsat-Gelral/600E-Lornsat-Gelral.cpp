

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

vi adj[N];
ll c[N];
ll ans[N];
ll best[N];
ll realans[N];
map<ll, ll> freq[N];

void solve(ll cur = 1, ll p = -1) {
	freq[cur][c[cur]] = 1;
	best[cur]=1;
	ans[cur]=c[cur];
	for (auto val: adj[cur]) {
		if (val == p) continue;
		solve(val, cur);

		if (freq[val].size() > freq[cur].size()) {
			swap(freq[val], freq[cur]);
			swap(best[cur], best[val]);
			swap(ans[cur], ans[val]);
		}

		for (auto [color, cnt]: freq[val]) {
			freq[cur][color] += cnt;
			if (freq[cur][color] > best[cur]) {
				ans[cur] = color;
				best[cur] = freq[cur][color];
			} else if (freq[cur][color] == best[cur]) ans[cur] += color;
		}
	}

	realans[cur]=ans[cur];
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	ll n;
	cin >> n;

	FOR(i, 1, n+1) {
		cin >> c[i];
	}

	FOR(i, 0, n-1) {
		ll a, b;
		cin >> a >> b;
		adj[a].pb(b);
		adj[b].pb(a);
	}

	solve();

	FOR(i, 1, n + 1) cout << realans[i] << ' ';
	cout << endl;

}












