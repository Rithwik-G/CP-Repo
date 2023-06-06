

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

const ll N = 2e5 + 10;

ll a[N];

#define lc n << 1
#define rc (n << 1) + 1

struct node {
	ll max;
	ll lz;
} segTree[N * 4];

ll nn;
void down(ll n, ll nl, ll nr) { // Update lazy of children from parent
	if (segTree[n].lz != 0) {
		ll nm = (nl + nr)/2;

		// update(n*2, nl, nm, segTree[n].lz);
		// update(n*2 + 1, nm, nr, segTree[n].lz);
		segTree[lc].max += segTree[n].lz;
		segTree[rc].max += segTree[n].lz;

		segTree[lc].lz += segTree[n].lz;
		segTree[rc].lz += segTree[n].lz;
		segTree[n].lz = 0;
	}
}

void up(ll n) { // update value of parent from children
	// segTree[n].max = segTree[2 * n].max + segTree[2 *n + 1].max;
	segTree[n].max = max(segTree[2 * n].max, segTree[2 *n + 1].max);
}

void build(ll n = 1, ll nl = 0, ll nr = nn) {

	if (nr - nl > 1) {
		ll nm = (nl + nr)/2;

		build(2*n, nl, nm);
		build(2 * n + 1, nm, nr);
		up(n);
	} else {
		// segTree[n].max = a[nl];
		segTree[n].max = a[nl];
	}
}

void update(ll gl, ll gr, ll val, ll n = 1, ll nl = 0, ll nr = nn) {
	if (gl <= nl && nr <= gr) {
		// cout << nl << nr << endl;
		// update(n, nl, nr, val);
		// cout << nl << nr << endl;
		segTree[n].lz += val;
		segTree[n].max += val;
	} else {
		down(n, nl, nr);
		ll nm = (nl + nr)/2;

		if (gl < nm) update(gl, gr, val, 2*n, nl, nm);
		if (nm < gr) update(gl, gr, val, 2 * n + 1, nm, nr);

		up(n);
	}
}


ll query(ll gl, ll gr, ll n = 1, ll nl = 0, ll nr = nn) {
	if (gl < 0) return 0;
	// cout << gl << gr << endl; 
	if (gl <= nl && nr <= gr) {
		// cout << nl << nr << endl;
		return segTree[n].max;
	} else {
		down(n, nl, nr);
		ll nm = (nl + nr)/2;
		ll acc = 0; // DEFAULT VALUE
		if (gl < nm) acc = max(acc, query(gl, gr, 2*n, nl, nm)); // CHANGE COMBINER FUNCTION
		if (nm < gr) acc = max(acc, query(gl, gr, 2 * n + 1, nm, nr));

		return acc;
	}
}

ll og[N];
int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	ll q;
	cin >> nn >> q;

	FOR(i, 0, nn) {
		cin >> a[i];
		og[i]=a[i];
	}
	FOR(i, 1, nn) a[i] += a[i-1];

	build();

	FOR(i, 0, q) {
		ll a, b, c;
		cin >> a >> b >> c;

		if (a == 1) {
			update(b-1, nn, c-og[b]);
			og[b]=c;
		} else {
			cout << max(0ll, query(b-1, c) - query(b-2, b-1)) << endl;
		}


	}
}












