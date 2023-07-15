// Source: http://usaco.org/index.php?page=viewproblem2&cpid=1140
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
	int val;
	int lz;
} st[4 * N];
int a[N];

int comb(int a, int b) { // MODIFY COMBINER FUNCTION
	return a + b;
}

void up(int i) {
	st[i].val = comb(st[lc].val, st[rc].val);
}

void down(int i) { // Propogate Lazy Downwards
	st[rc].val += st[i].lz;
	st[lc].val += st[i].lz;

	st[rc].lz += st[i].lz;
	st[lc].lz += st[i].lz;

	st[i].lz = 0;
}

void update(int ul, int ur, int val, int i = 1, int l = 0, int r = n) { // update [ul, ur) with += val
	if (l >= r) return;
	if (r <= ur && l >= ul) {
		st[i].val += (r - l) * val;
		st[i].lz += val;
		return;
	}

	down(i); // Propogate Lazy Down

	int m = (l + r)/2;

	if (m > ul) update(ul, ur, val, lc, l, m); // contained in left child
	if (m < ur) update(ul, ur, val, rc, m, r); // contained in right child

	up(i); // update current index
}

int query(int ql, int qr, int i = 1, int l = 0, int r = n) { // query from [ql, qr)

	if (l >= r) return 0; // identity
	if (ql <= l && qr >= r) { // fully contained
		return st[i].val;
	}

	if (r - l == 1) return 0; // leaf node

	down(i);

	int m = (l + r)/2;

	int acc = 0; // SET DEFAULT VALUE

	if (m >= ql) acc = comb(query(ql, qr, lc, l, m), acc); // Left
	if (m <= qr) acc = comb(acc, query(ql, qr, rc, m, r)); // Right

	return acc;
}

int querySet(int ql, int qr, int i = 1, int l = 0, int r = n) { // query from [ql, qr)

	if (l >= r) return 0; // identity
	if (ql <= l && qr >= r) { // fully contained
		return (st[i].val > 0);
	}

	if (r - l == 1) return 0; // leaf node

	down(i);

	int m = (l + r)/2;

	int acc = 0; // SET DEFAULT VALUE

	if (m >= ql) acc = comb(query(ql, qr, lc, l, m), acc); // Left
	if (m <= qr) acc = comb(acc, query(ql, qr, rc, m, r)); // Right

	return acc;
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	// int n;
	cin >> n;

	int a;

	vi prev(n + 1, -1);

	vi nxt(n, n);
	vector<bool> first(n + 1, false);
	int first_cnt = 0;

	FOR(i, 0, n) {
		cin >> a;
		if (prev[a] != -1) nxt[prev[a]]=i;
		if (!first[a]) {
			first_cnt++;
			update(i, i + 1, first_cnt);
			
			// cout << query(i, i + 1) << endl;
			first[a]=true;
		}
		prev[a]=i;

	}

	int ans = 0;



	FOR(i, 0, n) {
		update(i, nxt[i], -1);

		ans += query(i, nxt[i]);
		cout << i << nxt[i] << query(i, nxt[i]) << endl;
		assert(query(i, i + 1) == 0);

		

		update(nxt[i], nxt[i] + 1, querySet(i, nxt[i]));
	}

	cout << ans << endl;

}












