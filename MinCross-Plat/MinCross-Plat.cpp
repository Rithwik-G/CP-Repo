// Source: http://www.usaco.org/index.php?page=viewproblem2&cpid=720
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

typedef pair<ll, ll> pii;
typedef vector<pii> vpii;

typedef vector<ll> vi;

#define FOR(i, a, b) for (ll i = (a); i<b; i++)


int main() {
	freopen("mincross.in", "r", stdin);
	freopen("mincross.out", "w", stdout);

	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	ll n;
	cin >> n;

	vi a(n + 1);
	vi revb(n + 1);
	vi reva(n + 1);
	vi b(n + 1);
	vi other(n + 1);

	FOR(i,1, n + 1) {
		cin >> a[i];
		reva[a[i]]=i;
	}

	FOR(i,1, n + 1) {
		cin >> b[i];
		revb[b[i]] = i;
	}

	FOR(i, 1, n + 1){
		other[i]=revb[a[i]];
	}

	Tree<ll> vals;

	ll inv = 0;

	FOR(i, 1, n + 1) {
		inv += i - 1ll - vals.order_of_key(other[i]);
		vals.insert(other[i]);
	}

	ll ans = inv;

	for (ll i = n; i > 0; i--) {
		inv += 2ll * other[i] - n - 1ll;
		ans = min(ans, inv);
	}



	FOR(i, 1, n + 1){
		other[i]=reva[b[i]];
	}

	vals.clear();

	inv = 0;

	FOR(i, 1, n + 1) {
		inv += i - 1ll - vals.order_of_key(other[i]);
		vals.insert(other[i]);
	}

	ans = min(ans, inv);

	for (ll i = n; i > 0; i--) {
		inv += 2ll * other[i] - n - 1ll;
		ans = min(ans, inv);
	}
	cout << ans << endl;




}












