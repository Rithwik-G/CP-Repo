// Basic RURQ Segment Tree

// Update O(log n) => update(l, r, val)
// Query O(log n) => query(l, r, val)

// NOTE RANGES ARE EXCLUSIVE OF RIGHT ENDPOINT

#define lc n << 1
#define rc (n << 1) + 1

ll a[N];

struct node {
	// ll sum;
	// ll min;
	// ll lz;
} segTree[N * 4];


void down(ll n, ll nl, ll nr) { // Update lazy of children from parent
	if (segTree[n].lz != 0) {
		int nm = (nl + nr)/2;
		// update(n*2, nl, nm, segTree[n].lz);
		// update(n*2 + 1, nm, nr, segTree[n].lz);
		// segTree[n].lz = 0;
	}
}

void up(ll n) { // update value of parent from children
	// segTree[n].sum = segTree[2 * n].sum + segTree[2 *n + 1].sum;
	// segTree[n].min = min(segTree[2 * n].min, segTree[2 *n + 1].min);
}

void build(ll n = 1, ll nl = 0, ll nr = n) {

	if (nr - nl > 1) {
		ll nm = (nl + nr)/2;

		build(2*n, nl, nm);
		build(2 * n + 1, nm, nr);
		up(n);
	} else {
		// segTree[n].sum = a[nl];
		// segTree[n].min = a[nl];
	}
}

void update(ll gl, ll gr, ll val, ll n = 1, ll nl = 0, ll nr = n) {
	if (gl <= nl && nr <= gr) {
		update(n, nl, nr, val);
	} else {
		down(n, nl, nr);
		ll nm = (nl + nr)/2;

		if (gl < nm) update(gl, gr, val, 2*n, nl, nm);
		if (nm < gr) update(gl, gr, val, 2 * n + 1, nm, nr);

		up(n);
	}
}


ll query(ll gl, ll gr, ll n = 1, ll nl = 0, ll nr = n) { 
	if (gl <= nl && nr <= gr) {
		return segTree[n].min;
	} else {
		down(n, nl, nr);
		ll nm = (nl + nr)/2;
		ll acc = ; // DEFAULT VALUE
		if (gl < nm) acc = comb(acc, query(nm, gl, gr, 2*n, nl)); // CHANGE COMBINER FUNCTION
		if (nm < gr) acc = comb(query(nr, gl, gr, 2 * n + 1, nm), acc);

		return acc;
	}
}



