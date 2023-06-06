// Basic Segment Tree
// Replace comb with associative combiner function
// Update O(log n)
// Query O(log n)
// Source: AI.Cash



const int N = 1e5;  // limit for array size
int n;  // array size
int st[2 * N];
int comb(int a, int b) {
	return // WRITE HERE
}

void build() {  // build the tree; assumes original array is st[n..2*n]
  for (int i = n - 1; i > 0; --i) st[i] = comb(st[i<<1], st[i<<1|1]);
}

void modify(int p, int value) {  // set value at position p
  for (st[p += n] = value; p > 1; p >>= 1) st[p>>1] = comb(st[p], st[p^1]);
}

int query(int l, int r) {  // sum on interval [l, r)
  int res = 0;
  for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if (l&1) res = comb(res, st[l++]);
    if (r&1) res = comb(res, st[--r]);
  }
  return res;
}

