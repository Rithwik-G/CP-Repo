// Basic Lazy Segment Tree

// Update O(log n)
// Query O(log n)

// Changes
// comb - associative function
// down - how to update lazy
// update - how to update without traversing children
// query - defualt value & identity value

const int N = 1e5;

#define lc i << 1
#define rc (i << 1) + 1

int n;

struct node {
	int val = 0;
	int lz = 0;
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

void build(int i = 1, int l = 0, int r = n) { // build segtree from array a
	if (l>=r) return;
	if (r - l == 1) {
		st[i].val=a[l];
		return;
	}

	int m = (l + r)/2;

	build(lc, l, m);
	build(rc, m, r);
	up(i);
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


int main() {

	cin >> n;

	FOR(i, 0, n) cin >> a[i];

	build();

	FOR(i, 0, 100) {
		int a, b, c;
		cin >> a >> b >> c;

		if (a == 1) {
			int d;
			cin >> d;
			update(--b, c, d);
		} else {
			cout << query(--b, c) << endl;
		}
	}
}












