// Source: http://www.usaco.org/index.php?page=viewproblem2&cpid=577
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

const int N = 1e5;

#define lc i << 1
#define rc (i << 1) + 1

int n;

struct node {
	int HB, HE, LB, LE, p;
};

node st[4 * N];


void up(int i) {
	node r = st[rc];
	node l = st[lc];
	st[i].p = r.p + l.p + min(r.HB, l.LE) + min(r.HE, l.LB);
	st[i].HE = r.HE + l.HE - min(r.HE, l.LB);
	st[i].HB = r.HB + l.HB - min(r.HB, l.LE);

	st[i].LB = r.LB + l.LB - min(r.HE, l.LB);
	st[i].LE = r.LE + l.LE - min(r.HB, l.LE);
}

int inds[N];

void build(int i = 1, int l = 1, int r = n + 1) { // build segtree from array a
	if (l>=r) return;
	if (r - l == 1) {
		inds[l] = i;
		st[i].p = st[i].HE = st[i].HB = st[i].LE = st[i].LB = 0;
		return;
	}

	int m = (l + r)/2;

	build(lc, l, m);
	build(rc, m, r);

}

void update(int ind, int i = 1, int l = 1, int r = n + 1) { // update pos ind with value val
	if (l >= r) return;
	if (r - l == 1) {
		return;
	}

	int m = (l + r)/2;

	if (m > ind) update(ind, lc, l, m); // contained in left child
	else update(ind, rc, m, r); // contained in right child

	up(i); // update current index
}


int main() {
	freopen("cardgame.in", "r", stdin);
	freopen("cardgame.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> n;

	vi e(n);
	vector<bool> used(2*n + 1, false);

	FOR(i, 0, n) {
		cin >> e[i];
		used[e[i]]=true;
	}

	vi b;

	for (int i = 2*n; i> 0; i--) {
		if (!used[i]) {
			b.pb(i);
		}
	}

	n *= 2;
	build();



	FOR(i, 0, n/2) {
		// cout << e[i] << b[i] << endl;
		st[inds[e[i]]].HE++;
		st[inds[b[i]]].LB++;
	}

	FOR(i, 1, n + 1) update(i);
	// cout << inds[7] << endl;
	int ans = st[1].p;

	// cout << st[1].HB << endl;

	FOR(i, 0, n/2) {
		// cout << ans << endl;
		st[inds[e[i]]].HE--;
		st[inds[e[i]]].LE++;

		st[inds[b[i]]].LB--;
		st[inds[b[i]]].HB++;

		update(b[i]);
		update(e[i]);
		ans = max(ans, st[1].p);
	}
	// cout << inds[7] << endl;

	cout << ans << endl;



}












