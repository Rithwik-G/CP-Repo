// Source: https://studylib.net/doc/5889373/--ceoi-2009
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

struct Line {
	ll m, b;

	Line(ll m = 0, ll b = 0) : m(m), b(b) {}


	ll operator()(ll x) { return m * x + b; }


	friend ld intersect(Line l1, Line l2) {
		return (ld)(l2.b - l1.b) / (ld)(l1.m - l2.m);
	}
};

const int N = 1e5 + 10;

Line stk[N];
int s[N];
int v[N];
int ans[N];

int stk_max = 0;

int add(Line cur) {
	if (hull.size() < 2 || intersect(stk[stk_max - 1], cur) > inersect(stk[stk_max - 1], stk[stk_max - 2])) return stk_max;

	int l = 1;
	int r = stk_max - 1;

	while (l < r) {
		int mid = (l + r) / 2;

		if (intersect(stk[mid], stk[mid - 1]) < intersect(cur, stk[mid])) {
			l = m + 1;
		} else r = m;
	}

	return l;
}

int query(int x) {
	int l = 0;
	int r = stk_max - 1;

	while (l < r) {
		int mid = (l + r) / 2;

		if (intersect(stk[mid], stk[mid + 1]) < x) {
			l = m + 1;
		} else r = m;
	}

	return stk[l](x);
}

void dfs(int cur, int p = -1, int d = 0) {
	
	


}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

}












