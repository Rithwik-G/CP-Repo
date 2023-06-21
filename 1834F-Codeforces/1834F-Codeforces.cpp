// Source: https://codeforces.com/problemset/problem/1834/F
// 

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
const int N = 4e5 + 10;
int a[N];
int pref[2][N];
int suff[2][N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n;
	cin >> n;

	int ans = 0;
	FOR(i, 1, n + 1) {
		cin >> a[i];
		if (a[i] < i) ans++;
	}


	// suff[1] = ans;
	Tree<pii> s;
	for (int i = n; i >= 1; i--) {
		s.insert({a[i]-i, i});
		// shift i-1
		// cout << a[i]-i << endl;
		suff[0][i] = s.order_of_key({-(i - 1), -N});
	}
	s.clear();

	for (int i = 1; i <= n; i++) {
		s.insert({a[i]-i, i});
		// shift i-1
		pref[0][i] = s.order_of_key({(n - i), -N});
	}

	s.clear();

	reverse(a+1, a + n + 1);

	for (int i = n; i >= 1; i--) {
		s.insert({a[i]-i, i});
		// shift i-1
		// cout << a[i]-i << endl;
		suff[1][i] = s.order_of_key({-(i - 1), -N});
	}
	s.clear();

	for (int i = 1; i <= n; i++) {
		s.insert({a[i]-i, i});
		// shift i-1
		pref[1][i] = s.order_of_key({(n - i), -N});
	}

	s.clear();

	int shift = 0;
	int order = 0;

	cout << suff[order][shift + 1] + pref[order][shift] << endl;

	int q;
	cin >> q;

	FOR(i, 0, q) {
		int t;
		cin >> t;

		if (t == 1) {
			int k;
			cin >> k;
			shift = (shift + k) % n;
		} else if (t == 2) {
			int k;
			cin >> k;
			shift = (shift - k + n) % n;
		} else {
			shift = (n - shift + n) % n;
			order = (order + 1) % 2;
		}
		cout << suff[order][shift + 1] + pref[order][shift] << endl;
	}



}












