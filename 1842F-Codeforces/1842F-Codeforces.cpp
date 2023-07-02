// Source: https://codeforces.com/problemset/problem/1842/F
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

const int N = 5008;

int INF = 1e5;

vi adj[N];

int ans[N];
int n;
void solve(int u) {

	queue<int> q;
	vector<int> dis(N, INF);

	q.push(u);
	dis[0] = -1;
	dis[u] = 0;

	while (!q.empty()) {
		int cur = q.front();
		q.pop();

		for (auto val: adj[cur]) {
			if (dis[val] == INF) {
				dis[val] = dis[cur]+1;
				q.push(val);
			}
		}
	}

	sort(dis.begin(), dis.end());

	int run_tot = 0;

	FOR(i, 1, n + 1) {
		// cout << i << dis[i] << endl;
		run_tot += n - 1 - 2 * dis[i];
		ans[i] = max(ans[i], run_tot);
	}


}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	

	cin >> n;

	FOR(i, 0, n-1) {
		int a, b;
		cin >> a >> b;

		adj[a].pb(b);
		adj[b].pb(a);
	}

	FOR(i, 1, n + 1) solve(i);

	// cout << 0 << ' ';
	FOR(i, 0, n + 1) cout << ans[i] << ' ';
	cout << endl;

}












