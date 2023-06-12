const ll N = 2e5 + 10;
const ll INF = 3e18;
const ll DEF = -INF;

ll n, q;

struct node {
	ll max;
	ll lz;
} st[4 * N];
ll a[N];

ll comb(ll a, ll b) { // MODIFY COMBINER FUNCTION
	return max(a, b);
}

void up(ll i) {
	st[i].max = comb(st[lc].max, st[rc].max);
}

void down(ll i) { // Propogate Lazy Downwards
	st[rc].max += st[i].lz;
	st[lc].max += st[i].lz;

	st[rc].lz += st[i].lz;
	st[lc].lz += st[i].lz;

	st[i].lz = 0;
}

void build(ll i = 1, ll l = 0, ll r = n) { // build segtree from array a
	if (l>=r) return;
	if (r - l == 1) {
		st[i].max=a[l];
		return;
	}

	ll m = (l + r)/2;

	build(lc, l, m);
	build(rc, m, r);
	up(i);
}

void update(ll ul, ll ur, ll val, ll i = 1, ll l = 0, ll r = n) { // update [ul, ur) with += val
	if (l >= r) return;
	if (r <= ur && l >= ul) {
		st[i].max += val;
		st[i].lz += val;
		return;
	}

	down(i); // Propogate Lazy Down

	ll m = (l + r)/2;

	if (m > ul) update(ul, ur, val, lc, l, m); // contained in left child
	if (m < ur) update(ul, ur, val, rc, m, r); // contained in right child

	up(i); // update current index
}

ll query(ll ql, ll qr, ll i = 1, ll l = 0, ll r = n) { // query from [ql, qr)
	if (l >= r) return DEF; // identity
	if (ql <= l && qr >= r) { // fully contained
		return st[i].max;
	}

	if (r - l == 1) return DEF; // leaf node

	down(i);

	ll m = (l + r)/2;

	ll acc = DEF; // SET DEFAULT VALUE

	if (m >= ql) acc = comb(query(ql, qr, lc, l, m), acc); // Left
	if (m <= qr) acc = comb(acc, query(ql, qr, rc, m, r)); // Right
	return acc;
}