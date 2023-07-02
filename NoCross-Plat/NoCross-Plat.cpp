// Source: http://www.usaco.org/index.php?page=viewproblem2&cpid=721
// 

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
	void upd(int ind, int val) {
		arr[ind] += val;
		ind++;
		for (; ind <= size; ind += ind & -ind) { bit[ind] = max(bit[ind], val); }
	}

	/** @return The sum of aint values in [0, ind]. */
	T pref_max(int ind) {
		ind++;
		T total = 0;
		for (; ind > 0; ind -= ind & -ind) { total = max(total, bit[ind]); }
		return total;
	}
};


int main() {
	freopen("nocross.in", "r", stdin);
	freopen("nocross.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n;

	cin >> n;


	vi a(n + 1);
	vi b(n + 1);
	vi reva(n + 1);
	vi revb(n + 1);

	FOR(i,1, n + 1) {
		cin >> a[i];
		reva[a[i]]=i;
	}

	FOR(i,1, n + 1) {
		cin >> b[i];
		revb[b[i]] = i;
	}

	vpii points;

	FOR(i, 1, n + 1){
		for (int j = max(1, a[i] - 4); j <= min(n, a[i] + 4); j++) points.pb({i, -revb[j]});
	}

	sort(points.begin(), points.end());

	BIT<int> vals(n + 1);

	int ans = 0;

	FOR(i, 0, points.size()) {
		
		int cur = vals.pref_max(-points[i].s - 1) + 1;
		// cout << points[i].f << -points[i].s << cur <<  endl;
		vals.upd(-points[i].s, cur);
		ans = max(ans, cur);
	}

	cout << ans << endl;

	


}












