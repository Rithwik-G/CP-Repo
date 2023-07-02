// Source: http://www.usaco.org/index.php?page=viewproblem2&cpid=770
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
		int a;
		cin >> a;

		if (cur_max > n -i) ans++;

		cur_max = max(a, cur_max);
	}

	cout << ans << endl;


}












