// Source: https://codeforces.com/problemset/problem/13/E
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

const ll N = 1e5 + 10;
ll a[N];
ll nxt[N];
ll num_steps[N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	ll n, m;

	cin >> n >> m;
	ll batch_size;
	FOR(i, 1, n + 1) {
		if (i * i < n) batch_size=i;
		cin >> a[i];
		a[i] += i;
	}
	batch_size++;


	FOR(i, 1, n + 1) {
		ll batch_num = (i/batch_size);

		ll cur = i;
		ll cnt = 0;
		while (cur/batch_size == batch_num && cur <= n) {
			cur = a[cur];
			cnt++;

		}

		nxt[i]=cur;
		num_steps[i]=cnt;
	}

	// cout << 'd' << endl;

	FOR(i, 0, m) {
		ll t;
		cin >> t;

		if (t == 1) {
			ll ind;
			cin >> ind;
			ll ans = 0;
			while (true) {
				ans += num_steps[ind];
				if (nxt[ind] > n) break;
				ind = nxt[ind];
			}
			while (a[ind] <= n) ind = a[ind];

			cout << ind << ' ' << ans << endl;
		} else {
			ll ind, b;
			cin >> ind >> b;
			a[ind] = b + ind;

			ll batch_num = (ind/batch_size);

			for (ll i = ind; i >= batch_num * batch_size; i--) {
				
				if (i == 0) break;
				if (a[i]/batch_size > batch_num || a[i] > n) {
					nxt[i]=a[i];
					num_steps[i]=1;
					continue;
				}
				nxt[i]=nxt[a[i]];
				num_steps[i]=num_steps[a[i]] + 1;


			}

		

		}
	}


}












