// Source: http://www.usaco.org/index.php?page=viewproblem2&cpid=924
// 

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

const int N = 1e6 + 5;

double prob[N];

struct node {
	double val0;
	double pref0;
	double suff0;

	double val1;
	double pref1;
	double suff1;
};

double comb(double a0, double a1, double b0, double b1) {
	return a0 * b1 + a1 * b0;
}

node solve(int l, int r) {
	node cur;
	if (r - l == 1) {
		cur.val0 = cur.suff0 = cur.pref0 = 1 - prob[l];
		cur.val1 = cur.suff1 = cur.pref1 = prob[l];
		return cur;
	}

	int m = (l + r)/2;

	node right = solve(l, m);
	node left = solve(m, r);

	cur.val0 = left.val0 * right.val0;
	cur.pref0 = max(left.pref0, left.val0);
	cur.suff0 = max(right.suff, comb(left.suff, right.val));

	cur.val = max(max(right.val, left.val), comb(right.pref, left.suff));
	cur.pref = max(left.pref, comb(left.val, right.pref));
	cur.suff = max(right.suff, comb(left.suff, right.val));

	cout << l << r << ' ' << cur.val << endl;
	return cur;

}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n;
	cin >> n;

	FOR(i, 0, n) {
		cin >> prob[i];
		prob[i] /= 1e6;
	}

	cout << solve(0, n).val << endl;

}












