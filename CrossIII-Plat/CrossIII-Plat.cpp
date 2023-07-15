// Source: http://www.usaco.org/index.php?page=viewproblem2&cpid=722
// Commented code is Seg Tree version, TLE's unless use of BIT (but still TLEs a bit)

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


#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
template <class T>
using Tree =
    tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

const int N = 1e5;

#define lc i << 1
#define rc (i << 1) + 1

int n, k;

const int sz = 1e5 + 10;
Tree<int> bit[sz];

void update(int ind, int val) {
	ind++;
	for (; ind <= sz; ind += ind & -ind) { bit[ind].insert(val); }
}

	/** @return The sum of aint values in [0, ind]. */
int pref(int ind, int val) {
	ind++;
	int total = 0;
	for (; ind > 0; ind -= ind & -ind) { total += bit[ind].size() - (bit[ind].order_of_key(val+k + 1) - bit[ind].order_of_key(val - k)); }
	return total;
}




int main() {
	freopen("friendcross.in", "r", stdin);
	freopen("friendcross.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(nullptr);


	scanf("%d%d", &n, &k);

	vi a(n+1);
	vi revb(n+1);

	FOR(i, 1, n+1) {
		scanf("%d", &a[i]);

	}

	FOR(i, 1 , n + 1) {
		int d;
		scanf("%d", &d);
		revb[d]=i;
	}

	vi other(n + 1);

	FOR(i, 1, n + 1) {
		other[i] = revb[a[i]];
	}

	int ans = 0;


	for (int i = n; i> 0; i--) {

		ans += pref(other[i], a[i]);

		update(other[i], a[i]);

	}

	cout << ans << endl;
}


// #include "bits/stdc++.h"

// using namespace std;

// #define s second
// #define f first
// #define pb push_back

// typedef long long int;

// typedef pair<int, int> pii;
// typedef vector<pii> vpii;

// typedef vector<int> vi;

// #define FOR(i, a, b) for (int i = (a); i<b; i++)


// #include <ext/pb_ds/assoc_container.hpp>
// using namespace __gnu_pbds;
// template <class T>
// using Tree =
//     tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// const int N = 1e5;

// #define lc i << 1
// #define rc (i << 1) + 1

// int n, k;

// Tree<int> st[4 * N];

// void update(int ind, int val, int i = 1, int l = 1, int r = n+1) { // update pos ind with value val
	
// 	if (l >= r) return;
	
// 	// cout << i << l << r << endl;
// 	st[i].insert(val);
	
// 	if (r - l == 1) {
// 		return;
// 	}

// 	int m = (l + r)/2;

// 	if (m > ind) update(ind, val, lc, l, m); // contained in left child
// 	else update(ind, val, rc, m, r); // contained in right child

	
// }

// int query(int ql, int qr, int val, int i = 1, int l = 1, int r = n+1) { // query from [ql, qr)
// 	// cout << ' ' << i << endl;
// 	// cout << ' ' << ql << qr << val << endl;
// 	if (l >= r) return 0; // identity
// 	if (ql <= l && qr >= r) { // fuinty contained		
// 		return st[i].sz() - (st[i].order_of_key(val+k + 1) - st[i].order_of_key(val - k));
// 	}

// 	if (r - l == 1) return 0; // leaf node

// 	int m = (l + r)/2;

// 	int acc = 0; // SET DEFAULT VALUE

// 	if (m >= ql) acc += query(ql, qr, val, lc, l, m);
// 	if (m <= qr) acc += query(ql, qr, val, rc, m, r);

// 	return acc;
// }



// int main() {
// 	freopen("friendcross.in", "r", stdin);
// 	freopen("friendcross.out", "w", stdout);
// 	ios::sync_with_stdio(false);
// 	cin.tie(nullptr);

	
// 	cin >> n >> k;

// 	vi a(n+1);
// 	vi revb(n+1);

// 	FOR(i, 1, n+1) {
// 		cin >> a[i];
// 	}

// 	FOR(i, 1 , n + 1) {
// 		int d;
// 		cin >> d;
// 		revb[d]=i;
// 	}

// 	vi other(n + 1);

// 	FOR(i, 1, n + 1) {
// 		other[i] = revb[a[i]];
// 	}

// 	int ans = 0;

// 	FOR(i, 1, n + 1) {
// 		// cout << other[i] << endl;
// 		ans += query(other[i], n+1, a[i]);
// 		// cout << ' ' << ans << endl;
// 		update(other[i], a[i]);

// 	}

// 	cout << ans << endl;
// }












