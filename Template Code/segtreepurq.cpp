// Basic Segment Tree

// Update O(log n)
// Query O(log n)

// Changes
// comb - associative function
// query - defualt value & identity value



const int N = 1e5;

#define lc i << 1
#define rc (i << 1) + 1

int n;

int st[4 * N];
int a[N];

int comb(int a, int b) { // MODIFY COMBINER FUNCTION
	return max(a, b);
}

void up(int i) {
	st[i] = comb(st[lc], st[rc]);
}

void build(int i = 1, int l = 0, int r = n) { // build segtree from array a
	if (l>=r) return;
	if (r - l == 1) {
		st[i]=a[l];
		return;
	}

	int m = (l + r)/2;

	build(lc, l, m);
	build(rc, m, r);
	up(i);
}

void update(int ind, int val, int i = 1, int l = 0, int r = n) { // update pos ind with value val
	if (l >= r) return;
	if (r - l == 1) {
		st[i] = val;
		return;
	}

	int m = (l + r)/2;

	if (m > ind) update(ind, val, lc, l, m); // contained in left child
	else update(ind, val, rc, m, r); // contained in right child

	up(i); // update current index
}

int query(int ql, int qr, int i = 1, int l = 0, int r = n) { // query from [ql, qr)
	
	if (l >= r) return 0; // identity
	if (ql <= l && qr >= r) { // fully contained
		return st[i];
	}

	if (r - l == 1) return 0; // leaf node

	int m = (l + r)/2;

	int acc = ; // SET DEFAULT VALUE

	if (m >= ql) acc = comb(query(ql, qr, lc, l, m), acc);
	if (m <= qr) acc = comb(acc, query(ql, qr, rc, m, r));

	return acc;
}









