// Source: http://usaco.org/index.php?page=viewproblem2&cpid=1116
// Commented Code at the End is a Mo's that interestingly TLE's even though its n*sqrt(n)
// AC


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


template <class T> class BIT {
  private:
	int size;
	vector<T> bit;
	vector<T> arr;

  public:
	BIT(int size) : size(size), bit(size + 1), arr(size) {}

	/** Sets the value at index ind to val. */
	void set(int ind, int val) { add(ind, val - arr[ind]); }

	/** Adds val to the element at index ind. */
	void add(int ind, int val) {
		arr[ind] += val;
		ind++;
		for (; ind <= size; ind += ind & -ind) { bit[ind] += val; }
	}

	/** @return The sum of all values in [0, ind]. */
	T pref_sum(int ind) {
		ind++;
		T total = 0;
		for (; ind > 0; ind -= ind & -ind) { total += bit[ind]; }
		return total;
	}

	T range_sum(int l, int r) {
		return pref_sum(r) - pref_sum(l-1);
	}
};

struct Query {
    int l, r, idx;
    bool operator<(Query other) const
    {
        return r < other.r;
    }
};

const int N = 2e5 + 10;

Query queries[N];
int arr[N];

const int MX = 23;

int sp_table[N][MX];

int comb(int a, int b) {
	return min(a, b);
}

int n;

void build(int arr[]) {

	FOR(i, 1, n + 1) sp_table[i][0] = arr[i];	
	

	FOR(j, 1, MX) 
		FOR(i, 0, n)
			sp_table[i][j] = comb(sp_table[i][j - 1], sp_table[min((int) i + (int) pow(2, j-1), n)][j-1]);
		
	
}

int log(int x) {
    return 32 - __builtin_clz(x) - 1;
}

int query(int l, int r) {
	int dist = log(r-l + 1);
	return comb(sp_table[l][dist], sp_table[r-(int) pow(2, dist) + 1][dist]);
}

int answers[N];

int bef[N];

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int Q;
	cin >> n >> Q;

	FOR(i, 1, n + 1) cin >> arr[i];

	build(arr);

	FOR(i, 0, Q) {
		cin >> queries[i].l >> queries[i].r;
		queries[i].idx = i;
	}

	sort(queries, queries + Q);

	int qid = 0;

	BIT<int> bit(n + 1);

	for (int i = 1; i <= n; i++) {

		if (bef[arr[i]] != 0 && query(bef[arr[i]], i) >= arr[i]) {
			bit.set(bef[arr[i]], 0);
		}
		bit.set(i, 1);
		bef[arr[i]]=i;
		while (qid != Q && queries[qid].r == i) {
			answers[queries[qid].idx] = bit.range_sum(queries[qid].l, queries[qid].r);
			qid++;

		}

	} 

	FOR(i, 0, Q) cout << answers[i] << endl;

}














// #include "bits/stdc++.h"

// using namespace std;

// #define s second
// #define f first
// #define pb push_back

// typedef long long ll;

// typedef pair<ll, ll> pii;
// typedef vector<pii> vpii;

// typedef vector<ll> vi;

// #define FOR(i, a, b) for (ll i = (a); i<b; i++)

// const int block_size = 500;

// struct Query {
//     int l, r, idx;
//     bool operator<(Query other) const
//     {
//         if (l / block_size != other.l / block_size)
//         	return make_pair(l, r) < make_pair(other.l, other.r);
//     	return (l / block_size & 1) ? (l < other.l) : (r > other.r);
//     }
// };

// const int N = 2e5 + 10;

// Query queries[N];
// int arr[N];

// deque<int> inds[N];

// const int MX = 23;

// int sp_table[N][MX];

// int comb(int a, int b) {
// 	return min(a, b);
// }

// int n;

// void build(int arr[]) {

// 	FOR(i, 0, n) sp_table[i][0] = arr[i];	
	

// 	FOR(j, 1, MX) 
// 		FOR(i, 0, n)
// 			sp_table[i][j] = comb(sp_table[i][j - 1], sp_table[min((int) i + (int) pow(2, j-1), n)][j-1]);
		
	
// }

// int log(int x) {
//     return 32 - __builtin_clz(x) - 1;
// }

// int query(int l, int r) {
// 	int dist = log(r-l + 1);
// 	return comb(sp_table[l][dist], sp_table[r-(int) pow(2, dist) + 1][dist]);
// }

// int answers[N];

// int ans = 0;

// void addFront(int ind) {
// 	ans ++;
// 	if (!inds[arr[ind]].empty() && query(ind, inds[arr[ind]].front()) >= arr[ind]) ans--;

// 	inds[arr[ind]].push_front(ind);
// }

// void addBack(int ind) {
// 	ans ++;
// 	// if (!inds[arr[ind]].empty()) cout << ind << inds[arr[ind]].back() << query(inds[arr[ind]].back(), ind) << endl;
// 	if (!inds[arr[ind]].empty() && query(inds[arr[ind]].back(), ind) >= arr[ind]) ans--;

// 	inds[arr[ind]].push_back(ind);
// }

// void removeFront(int ind) {
// 	assert(inds[arr[ind]].front() == ind);
// 	inds[arr[ind]].pop_front();

// 	ans--;
// 	// cout << ind << inds[arr[ind]].front() << endl;
// 	if (!inds[arr[ind]].empty() && query(ind, inds[arr[ind]].front()) >= arr[ind]) ans++;

// }

// void removeBack(int ind) {
// 	assert(inds[arr[ind]].back() == ind);
	
// 	inds[arr[ind]].pop_back();
	
// 	ans--;
// 	if (!inds[arr[ind]].empty() && query(inds[arr[ind]].back(), ind) >= arr[ind]) ans++;

// }


// int main() {
// 	ios::sync_with_stdio(false);
// 	cin.tie(nullptr);

// 	int Q;
// 	cin >> n >> Q;

// 	FOR(i, 0, n) cin >> arr[i];

// 	build(arr);

// 	FOR(i, 0, Q) {
// 		cin >> queries[i].l >> queries[i].r;
// 		queries[i].l--;
// 		queries[i].r--;
// 		queries[i].idx = i;
// 	}

// 	sort(queries, queries + Q);

// 	int cur_l = 0;
//     int cur_r = -1;

// 	for (int i = 0; i < Q; i++) {

// 		auto q = queries[i];
// 		while (cur_l > q.l) {
//             cur_l--;
//             addFront(cur_l);
//         }
//         while (cur_r < q.r) {
//             cur_r++;
//             addBack(cur_r);
//             // cout << cur_r << ans << endl;
//         }

//         // cout << ans << endl;
//         while (cur_l < q.l) {
//             removeFront(cur_l);
//             cur_l++;
//         }
//         while (cur_r > q.r) {
//             removeBack(cur_r);
//             cur_r--;
//         }
//         answers[q.idx] = ans;

//         // cout << q.l << q.r << ans << endl;
// 	} 

// 	FOR(i, 0, Q) cout << answers[i] << endl;

// }












