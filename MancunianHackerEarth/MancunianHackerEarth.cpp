// Source: https://www.hackerearth.com/practice/data-structures/advanced-data-structures/fenwick-binary-indexed-trees/practice-problems/algorithm/mancunian-and-twin-permutations-d988930c/
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

int fwt[100001];
const int MX = 100001;

void inc(int ind, int i) {
	while (ind < MX) {
		fwt[ind] += i;
		ind += (ind & -ind);
	}
}
int sum(int ind) {
	int ret = 0;
	while (ind > 0) {
		ret += fwt[ind];
		ind -= (ind & -ind);
	}
	return ret;
}



int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n;
	cin >> n;

	vi a(n + 1);
	vi b(n + 1);
	vi y(n + 1);
	FOR(i, 1, n + 1) {
		cin >> a[i];
		y[a[i]]=i;
	}
	FOR(i, 1, n + 1) cin >> b[i];

	int q;
	cin >> q;

	vector<vi> e(n + 1);
	vector<vi> s(n + 1);

	vector<pair<pii, pii> > qu(q);
	vi ans(q);

	FOR(i, 0, q) {
		cin >> qu[i].f.f >> qu[i].f.s >> qu[i].s.f >> qu[i].s.s;

		e[qu[i].s.s].push_back(i);
		s[qu[i].s.f].push_back(i);


	}

	FOR(i, 1, n + 1) {
		for (int query: s[i]) {
			ans[query] -= sum(qu[query].f.s) - sum(qu[query].f.f - 1);
		}
		inc(y[b[i]], 1);
		for (int query: e[i]) {
			ans[query] += sum(qu[query].f.s) - sum(qu[query].f.f - 1);
		}
	}

	FOR(i, 0, q) cout << qu[i].f.s - qu[i].f.f + 1 - ans[i] << endl;

}












