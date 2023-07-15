// Source: http://www.usaco.org/index.php?page=viewproblem2&cpid=770
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

const int N = 1e5 + 10;
int a[N];

int main() {
	freopen("greedy.in", "r", stdin);
	freopen("greedy.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n;
	cin >> n;

	int ans = 0;
	int cur_max =0;

	FOR(i, 1, n + 1) {
		cin >> a[i];
	}

	int lo = 1;
	int hi = n;

	while (lo < hi) { // first cow who does not receive a gift
		int m = (lo + hi)/2;

		vi freq(n, 0);

		FOR(i, 0, m) freq[a[i]]++;

		int index = m;
		bool good = true;
		FOR(i, 0, n) {
			if (freq[i] > 0 && index >= n-i) good = false;
			index -= freq[i];
		}

		assert(index == 0);

		if (good) lo = m + 1;
		else hi = m;
	}

	cout << n - hi + 1 << endl;



}












