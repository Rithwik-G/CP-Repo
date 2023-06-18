// Source https://dmoj.ca/problem/ioi05p3
// 

#include "bits/stdc++.h"

using namespace std;

#define s second
#define f first
#define pb push_back

#define FOR(i, a, b) for (ll i = (a); i<b; i++)

#define lc i << 1
#define rc (i << 1) + 1

typedef long long ll;

typedef pair<ll, ll> pii;
typedef vector<pii> vpii;

typedef vector<ll> vi;


const ll N = 1e5;

#define lc i << 1
#define rc (i << 1) + 1

ll n;

struct node {
	ll val;
	ll lz;
	ll max_pref;
} st[4 * N];
ll a[N];

ll comb(ll a, ll b) { // MODIFY COMBINER FUNCTION
	return a + b;
}

void up(ll i) {
	st[i].val = comb(st[lc].val, st[rc].val);
	st[i].max_pref = max(st[lc].max_pref, st[lc].val + st[rc].max_pref);
}

void down(ll i, ll l, ll r, ll m) { // Propogate Lazy Downwards
	if (st[i].lz == 0) return;
	st[rc].val = (r - m) * st[i].lz;
	st[lc].val = (m - l) * st[i].lz;

	st[rc].lz = st[i].lz;
	st[lc].lz = st[i].lz;

	st[i].lz = 0;

	st[lc].max_pref = max(0ll, st[lc].val);
	st[rc].max_pref = max(0ll, st[rc].val);
}

void update(ll ul, ll ur, ll val, ll i = 1, ll l = 0, ll r = n) { // update [ul, ur) with += val
	if (l >= r) return;
	if (r <= ur && l >= ul) {
		st[i].val = (r - l) * val;
		st[i].lz = val;
		st[i].max_pref = max(0ll, st[i].val);
		// cout << l << r << st[i].max_pref << endl;
		return;
	}

	

	ll m = (l + r)/2;
	down(i,l,r, m); // Propogate Lazy Down

	if (m > ul) update(ul, ur, val, lc, l, m); // contained in left child
	if (m < ur) update(ul, ur, val, rc, m, r); // contained in right child

	up(i); // update current index
	// cout << l << r << st[i].max_pref << endl;
}

ll query(ll req, ll i = 1, ll l = 0, ll r = n) { // query from [ql, qr)

	if (l >= r) return 0; // identity

	if (r - l == 1) return l; // leaf node

	

	ll m = (l + r)/2;

	down(i, l,r,m);
	// cout << l << r << st[i].max_pref << endl;

	if (st[lc].max_pref > req) return query(req, lc, l, m); // Left
	else return query(req - st[lc].val, rc, m, r); // Right
}


int main() {
	FOR(i, 0, 4*N) {
		st[i].val = 0;
		st[i].lz = 0;
	}
	cin >> n;

	char t;
	cin >> t;
	n++;
	while (t != 'E') {

		if (t == 'Q') {
			ll a;
			cin >> a;
			cout << query(a) << endl;
		} else {
			ll a, b, c;
			cin >> a >> b >> c;

			update(--a, b, c);
		}

		cin >> t;
	}

	
}
























