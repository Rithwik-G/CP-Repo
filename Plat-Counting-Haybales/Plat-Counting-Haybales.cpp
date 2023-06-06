
// SOURCE: http://www.usaco.org/index.php?page=viewproblem2&cpid=578
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

const ll N = 2e5 + 10;
ll a[N];

struct node {
	ll sum;
	ll min;
	ll lz;
} segTree[N * 4];


void update(ll n, ll nl, ll nr, ll val) {
	segTree[n].sum += (nr-nl) * val;
	segTree[n].min += val;
	segTree[n].lz += val;
	
}

void down(ll n, ll nl, ll nr) {
	if (segTree[n].lz != 0) {
		int nm = (nl + nr)/2;
		update(n*2, nl, nm, segTree[n].lz);
		update(n*2 + 1, nm, nr, segTree[n].lz);
		segTree[n].lz = 0;
	}
}

void up(ll n) {
	segTree[n].sum = segTree[2 * n].sum + segTree[2 *n + 1].sum;
	segTree[n].min = min(segTree[2 * n].min, segTree[2 *n + 1].min);
}

void build(ll n, ll nl, ll nr) {

	if (nr - nl > 1) {
		ll nm = (nl + nr)/2;

		build(2*n, nl, nm);
		build(2 * n + 1, nm, nr);
		up(n);
	} else {
		segTree[n].sum = a[nl];
		segTree[n].min = a[nl];
	}
	// cout << nl << nr << segTree[n].min << endl;
}

void update(ll n, ll nl, ll nr, ll gl, ll gr, ll val) {
	if (gl <= nl && nr <= gr) {
		update(n, nl, nr, val);
	} else {
		down(n, nl, nr);
		ll nm = (nl + nr)/2;

		if (gl < nm) update(2*n, nl, nm, gl, gr, val);
		if (nm < gr) update(2 * n + 1, nm, nr, gl, gr, val);

		up(n);
	}
}


ll querySum(ll n, ll nl, ll nr, ll gl, ll gr) {
	if (gl <= nl && nr <= gr) {
		return segTree[n].sum;
	} else {
		down(n, nl, nr);
		ll nm = (nl + nr)/2;
		ll acc = 0;
		if (gl < nm) acc += querySum(2*n, nl, nm, gl, gr);
		if (nm < gr) acc += querySum(2 * n + 1, nm, nr, gl, gr);

		return acc;
	}
}

ll queryMin(ll n, ll nl, ll nr, ll gl, ll gr) {
	// cout << nl << nr << gl << gr << endl;
	if (gl <= nl && nr <= gr) {
		return segTree[n].min;
	} else {
		down(n, nl, nr);
		ll nm = (nl + nr)/2;
		ll acc = 1e13;
		if (gl < nm) acc = min(acc, queryMin(2*n, nl, nm, gl, gr));
		if (nm < gr) acc = min(queryMin(2 * n + 1, nm, nr, gl, gr), acc);

		return acc;
	}
}






int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	freopen("haybales.in", "r", stdin);
	freopen("haybales.out", "w", stdout);


	ll n, m;
	cin >> n >> m;

	FOR(i, 0, n) cin >> a[i];

	build(1, 0, n);


	FOR(i, 0, m) {
		char c;
		cin >> c;
		ll a, b, d;
		if (c == 'M') {
			
			cin >> a >> b;
			cout << queryMin(1, 0, n, a-1, b) << endl;
		} else if (c == 'P') {
			cin >> a >> b >> d;
			update(1, 0, n, --a, b, d);
		} else {
			cin >> a >> b;
			cout << querySum(1, 0, n, a-1, b) << endl;
		}
	}
}












