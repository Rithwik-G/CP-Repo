// Source: https://oj.uz/problem/view/IZhO12_apple
// Later

#include "bits/stdc++.h"


using namespace std;

#define s second
#define f first
#define pb push_back

typedef long long ll;

typedef pair<int, int> pii;
typedef vector<pii> vpii;

typedef vector<int> vi;

#define FOR(i, a, b) for (int i = (a); i<b; i++)


const int N = 1e5;

#define lc st[i].left
#define rc st[i].right

int cnt = 2;
struct node {
	int val;
	int lz;
	int left;
	int right;
	int l;
	int r;
	node() : val(0), lz(0), left(0), right(0) {}
} st[64 * N];
int a[N];

int comb(int a, int b) { // MODIFY COMBINER FUNCTION
	return a + b;
}

void up(int i) {
	st[i].val = comb(st[lc].val, st[rc].val);
}

int new_node(int l, int r) {
	int ind = cnt++;
	st[ind].l = l;
	st[ind].r = r;

	return ind;
}

void down(int i) { // Propogate Lazy Downwards
	if (st[i].lz == 0) return;
	int mid = (st[i].l + st[i].r) / 2;
	if (rc == 0) rc = new_node(mid, st[i].r);
	if (lc == 0) lc = new_node(st[i].l, mid);

	st[rc].val = (st[rc].r - st[rc].l) * st[i].lz;
	st[rc].lz = st[i].lz;

	st[lc].val = (st[lc].r - st[lc].l) * st[i].lz;
	st[lc].lz = st[i].lz;

	st[i].lz = 0;
}

void update(int ul, int ur, int val, int i = 1, int l = 0, int r = 1e9 + 1) { // update [ul, ur) with += val
	if (l >= r) return;
	if (r <= ur && l >= ul) {
		
		
		st[i].val = (r - l) * val;
		st[i].lz = val;
		// cout << l << r << i << ' '  << st[i].val << endl;
		return;
	}
	down(i); // Propogate Lazy Down

	int m = (l + r)/2;

	if (rc == 0) rc = new_node(m, st[i].r);
	if (lc == 0) lc = new_node(st[i].l, m);

	

	if (m > ul) update(ul, ur, val, lc, l, m); // contained in left child
	if (m < ur) update(ul, ur, val, rc, m, r); // contained in right child

	up(i); // update current index
}

int query(int ql, int qr, int i = 1, int l = 0, int r = 1e9 + 1) { // query from [ql, qr)

	if (l >= r) return 0; // identity
	if (ql <= l && qr >= r) { // fully contained
		// cout << l << r << i << ' '  << st[i].val << endl;
		return st[i].val;
	}

	if (r - l == 1) return 0; // leaf node

	down(i);



	int m = (l + r)/2;

	if (rc == 0) rc = new_node(m, st[i].r);
	if (lc == 0) lc = new_node(st[i].l, m);

	int acc = 0; // SET DEFAULT VALUE

	if (m >= ql) acc = comb(query(ql, qr, lc, l, m), acc); // Left
	if (m <= qr) acc = comb(acc, query(ql, qr, rc, m, r)); // Right

	return acc;
}


int main() {

	int m;
	cin >> m;

	st[1].val = 0;
	st[1].lz = 0;
	st[1].l = 1;
	st[1].r = 1e9;

	int c = 0;
	FOR(_, 0, m) {
		int d, x, y;
		cin >> d >> x >> y;
		if (d == 1) {
			c = query(x + c, y + c + 1);
			cout << c << endl;
		} else update(x + c, y + c + 1, 1);
	}


	
}












