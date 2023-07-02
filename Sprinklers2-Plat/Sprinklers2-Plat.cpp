

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

template <class T> class sum_bit {
  private:
	int size;
	vector<T> bit;
	vector<T> arr;

  public:
	sum_bit(int size) : size(size), bit(size + 1), arr(size) {}

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
};

template <class T> class prod_bit {
  private:
	int size;
	vector<T> bit;
	vector<T> arr;

  public:
	prod_bit(int size) : size(size), bit(size + 1, 1), arr(size) {}

	/** Sets the value at index ind to val. */
	void set(int ind, int val) { add(ind, val - arr[ind]); }

	/** Adds val to the element at index ind. */
	void mult(int ind, int val) {
		arr[ind] *= val;
		ind++;
		for (; ind <= size; ind += ind & -ind) { bit[ind] = bit[ind] * val; }
	}

	/** @return The sum of all values in [0, ind]. */
	T pref_prod(int ind) {
		ind++;
		T total = 1;
		for (; ind > 0; ind -= ind & -ind) { total = total *= bit[ind]; }
		return total;
	}
};

const int N = 2001;

int prodCnt[N][N][2];
int cnt[N][N][2];
int rem[N][N][2];


prod_bit<int> product0(N);
prod_bit<int> product1(N);
sum_bit<int> sum_cnt0(N);
sum_bit<int> sum_cnt1(N);

sum_bit<int> sum_rem0(N);
sum_bit<int> sum_rem1(N);





int main() {
	// ios::sync_with_stdio(false);
	// cin.tie(nullptr);

	// int n;
	// cin >> n;

	// prodCnt[0][0][0] = 2;

	// cnt[0][0][0] = 1;

	// rem[0][0][0] = 1;


	// vector<bool> inp(n, true);

	// FOR(i, 0, n) {
	// 	FOR(j, 0, n) {

	// 		char a;
	// 		cin >> a;
	// 		if (i == 0 && j == 0 && a == 'W') {
	// 			cout << 0 << endl;
	// 			return 0;
	// 		}

	// 		if (a == 'W') inp[i]=false;

	// 		if (!inp[i]) continue;

	// 		cnt[i][j][0] = sum_cnt1.pref_sum(j);
	// 		prodCnt[i][j][0] = product1.pref_prod(j);
	// 		rem[i][j][0] = sum_rem1.pref_sum(j) + cnt[i][j][0];

	// 		sum_cnt0.add(j, cnt[i][j][0]);
	// 		product0.mult(j, prodCnt[i][j][0]);
	// 		sum_rem0.add(j, rem[i][j][0]);
	// 	}

	// 	FOR(j, 0, n) {
	// 		if (!inp[i]) continue;

	// 		cnt[i][j][1] = sum_cnt0.pref_sum(j-1);
	// 		prodCnt[i][j][1] = product0.pref_prod(j-1);
	// 		rem[i][j][1] = sum_rem0.pref_sum(j-1) + cnt[i][j][1];

	// 		sum_cnt1.add(j, cnt[i][j][1]);
	// 		product1.mult(j, prodCnt[i][j][1]);
	// 		sum_rem1.add(j, rem[i][j][1]);
	// 	}
	// }

	// // cout << prodCnt[n-1][n-1][0] + prodCnt[n-1][n-1][1] / pow(2, rem[n-1][n-1][0]) / pow(2, rem[n-1][n-1][1])  << endl;
	// cout << cnt[n-1][n-1][0] << endl;
}












