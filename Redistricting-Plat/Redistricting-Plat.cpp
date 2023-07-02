

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


int main() {
	freopen("redistricting.in", "r", stdin);
	freopen("redistricting.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n, k;

	cin >> n >> k;

	int cur_pre = 0;
	set<array<int, 3> > ms;
	ms.insert({0, 0, -1}); // dp, prefix, ind
	char c;
	int dp;
	FOR(i, 0, n) {
		cin >> c;


		if (c == 'H') cur_pre --;
		else cur_pre ++;

		while ((*ms.begin())[2] < (i - k)) ms.erase(ms.begin());

		dp = (*ms.begin())[0] + (cur_pre + (*ms.begin())[1] >= 0);
		// cout << i << dp << endl;
		ms.insert({dp, -cur_pre, i});
	}

	cout << dp << endl;

}












