// Source: https://cses.fi/problemset/task/1144
// AC

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

typedef pair<int, int> pii;
typedef vector<pii> vpii;

typedef vector<int> vi;

#define FOR(i, a, b) for (ll i = (a); i<b; i++)
const int INF = 1e9;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, q;
	cin >> n >> q;
	vi a(n+1);
	Tree<pii> t;

	FOR(i, 1, n + 1) {
		cin  >> a[i];

		t.insert({a[i], i});
	}

	FOR(i, 0, q) {
		char ty;
		cin >> ty;
		int b, c;
		cin >> b >> c;

		if (ty == '!') {
			t.erase({a[b], b});
			a[b]=c;
			t.insert({a[b], b});
		} else {
			cout << t.order_of_key({c, INF}) - t.order_of_key({b-1, INF}) << endl;
		}
	}

}












