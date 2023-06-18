// Source: https://codeforces.com/problemset/problem/1841/E

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


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	ll t;
	cin >> t;

	while (t--) {
		ll n;
		cin >> n;
		vi a(n);
		FOR(i, 0, n) cin >> a[i];

		stack<pii> forward; // value, index
		forward.push({1000000, -1});
		vi g(n);
		vi l(n);
		// cout << 'd' << endl;
		FOR(i, 0, n) {
			// cout << i << endl;
			while (!forward.empty() && forward.top().f <= a[i]) forward.pop();// decreasing
			l[i] = forward.top().s;
			forward.push({a[i], i});
			// cout << i << endl;
		}
		// cout << 'd' << endl;
		stack<pii> backward;
		backward.push({1000000, n});
		for (ll i = n - 1; i>= 0; i--) {
			// cout << i << endl;
			while (!backward.empty() && backward.top().f < a[i]) backward.pop(); // non-increasing
			g[i] = backward.top().s;
			backward.push({a[i], i});
		}
		vi poss(n + 1);
		FOR(i, 0, n) {
			
			if (g[i] != n && a[i] == a[g[i]]) continue;
			
			ll prev_height = n;
			if (l[i] != -1) prev_height = a[l[i]];

			ll after_height = n;
			if (g[i] != n) after_height = a[g[i]];
			// cout << prev_height << after_height << endl;
			poss[g[i] - l[i] - 1] += min(after_height, prev_height) - a[i];
		}
		ll left;
		ll ans = 0;
		cin >> left;
		for (ll i = n; i>=2; i--) {
			ll usable = min(left/i, poss[i]);
			ans += (i-1ll) * usable;
			left-=usable*i;
			poss[i]-=usable;

			if (left == 0) break;

			if (poss[i] > 0) {
				ans += (left - 1);
				left = 0;
				break;
			}


		}
		cout << ans << endl;
	}

}












