// SOURCE: https://cses.fi/problemset/result/6213655/

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

// Basic RURQ Segment Tree

// Update O(log n)
// Query O(log n)

// NOTE RANGES ARE EXCLUSIVE OF RIGHT ENDPOINT
const ll N = 2e5 + 10;
#define lc n << 1
#define rc (n << 1) + 1

ll a[N];

struct node {
	ll sum;

	ll lzAdd;
	ll lzSet;
} segTree[N * 4];



void down(ll n, ll nl, ll nr) { // Function to update lazy of children from parent
	ll mid = (nl + nr)/2;
	if (segTree[n].lzSet != 0) {
		

		segTree[2*n].lzSet = segTree[n].lzSet;
		segTree[2*n + 1].lzSet = segTree[n].lzSet;

		segTree[2*n].sum = (mid - nl) * segTree[2*n].lzSet;
		segTree[2*n + 1].sum = (nr - mid) * segTree[2*n].lzSet;

		segTree[rc].lzAdd = segTree[lc].lzAdd = 0;

		segTree[n].lzSet = 0;
	} else if (segTree[n].lzAdd != 0) {
		if (segTree[rc].lzSet == 0) segTree[rc].lzAdd += segTree[n].lzAdd;
		else {
			segTree[rc].lzSet += segTree[n].lzAdd;
			segTree[rc].lzAdd = 0;
		}

		if (segTree[lc].lzSet == 0) segTree[lc].lzAdd += segTree[n].lzAdd;
		else {
			segTree[lc].lzSet += segTree[n].lzAdd;
			segTree[lc].lzAdd = 0;
		}

		segTree[lc].sum += (mid - nl) * segTree[n].lzAdd;
		segTree[rc].sum += (nr - mid) * segTree[n].lzAdd;
		segTree[n].lzAdd = 0;
	}

}

void up(ll n) {
	segTree[n].sum = segTree[2 * n].sum + segTree[2 *n + 1].sum;
	// segTree[n].min = min(segTree[2 * n].min, segTree[2 *n + 1].min);
}

void build(ll n, ll nl, ll nr) {

	if (nr - nl > 1) {
		ll nm = (nl + nr)/2;

		build(2*n, nl, nm);
		build(2 * n + 1, nm, nr);
		up(n);
	} else {
		segTree[n].sum = a[nl];
		// segTree[n].min = a[nl];
	}
}

void add(ll n, ll nl, ll nr, ll gl, ll gr, ll val) {
	if (gl <= nl && nr <= gr) {
		// cout << nl << nr << endl;
		segTree[n].sum += (nr - nl) * val;
		if (segTree[n].lzSet == 0) segTree[n].lzAdd += val;
		else segTree[n].lzSet += val;
	} else {
		down(n, nl, nr);
		ll nm = (nl + nr)/2;

		if (gl < nm) add(2*n, nl, nm, gl, gr, val);
		if (nm < gr) add(2 * n + 1, nm, nr, gl, gr, val);

		up(n);
	}
}

void setV(ll n, ll nl, ll nr, ll gl, ll gr, ll val) {
	if (gl <= nl && nr <= gr) {
		segTree[n].sum = (nr - nl) * val;
		segTree[n].lzSet = val;
		segTree[n].lzAdd = 0;
	} else {
		down(n, nl, nr);
		ll nm = (nl + nr)/2;

		if (gl < nm) setV(2*n, nl, nm, gl, gr, val);
		if (nm < gr) setV(2 * n + 1, nm, nr, gl, gr, val);

		up(n);
	}
}


ll query(ll n, ll nl, ll nr, ll gl, ll gr) { 
	if (gl <= nl && nr <= gr) {
		// cout << nl << nr << segTree[n].sum << endl;
		return segTree[n].sum;
	} else {
		down(n, nl, nr);
		ll nm = (nl + nr)/2;
		ll acc = 0; // DEFAULT VALUE
		if (gl < nm) acc = acc + query(2*n, nl, nm, gl, gr); // CHANGE COMBINER FUNCTION
		if (nm < gr) acc = query(2 * n + 1, nm, nr, gl, gr) + acc;

		return acc;
	}
}






int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	ll n, q;
	cin >> n >> q;

	FOR(i, 0, n) {
		cin >> a[i];
	}

	build(1, 0, n);

	FOR(i, 0, q) {
		ll t;
		cin >> t;
		ll x, y, z;
		if (t == 2) {
			cin >> x >> y >> z;
			setV(1, 0, n, x-1, y, z);
		} else if (t == 1) {
			cin >> x >> y >> z;
			add(1, 0, n, x-1, y, z);
		} else {
			cin >> x >> y;
			cout << query(1, 0, n, x-1, y) << endl;
		}
	}
}












