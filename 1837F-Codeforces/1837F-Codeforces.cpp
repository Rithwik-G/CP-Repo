// Source https://codeforces.com/problemset/problem/1837/F
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


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);


	ll t;
	cin >> t;

	while (t--) {
		ll n, k;
		cin >> n >> k;

		vi a(n);
		ll sum = 0;
		FOR(i, 0, n) {
			cin >> a[i];
			sum += a[i];
		}

		ll lo = 0;
		ll hi = sum;
		vi pref(n);
		vi suff(n);
		while (lo < hi) {
			ll x = (lo + hi)/2;
			priority_queue<ll> p;
			ll cur_sum = 0;
			FOR(i, 0, n) {
				cur_sum += a[i];
				p.push(a[i]);
				while (cur_sum > x) {
					cur_sum -= p.top();
					p.pop();
				}
				pref[i] = p.size();
			}

			priority_queue<ll> s;
			cur_sum = 0;
			for (ll i = n-1; i>= 0; i--) {
				cur_sum += a[i];
				s.push(a[i]);
				while (cur_sum > x) {
					cur_sum -= s.top();
					s.pop();
				}
				suff[i] = s.size();
			}
			bool worked=false;
			FOR(i, 1, n) {
				if (pref[i-1] + suff[i] >= k) worked=true;
			}

			if (worked) hi=x;
			else lo = x+1;



		}

		cout << lo << endl;


	}
}












