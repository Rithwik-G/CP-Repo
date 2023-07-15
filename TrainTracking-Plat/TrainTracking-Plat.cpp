// Source: http://www.usaco.org/index.php?page=viewproblem2&cpid=902
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

const int N = 1e5 + 10;

int dp[N];
int k;
int solve(int n, int num) {

	if (n <= 0) return 1;

	dp[0] = 0;

	dp[1] = 1;

	int cur = dp[1] + num*dp[0];

	for (int i = 2; i <= n + 1; i++) {

		dp[i] = cur;
		
		cur *= num;
		cur += dp[i];

		if (i >= k) cur -= pow(num, k) * dp[i - k];
	}

	int res = 0;

	for (int i = n-k+1; i<=n; i++) res += dp[i];

	cout << n << res << endl;
	return res;



}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n;

	cin >> n >> k;

	int prev;
	int st = 0;

	cin >> prev;
	int ans = 1;
	for (int i = 1; i < n-k+1; i++) {
		int a;
		cin >> a;
		if (a != prev) {
			// cout << en << st << endl;
			int en = i + k - 1;
			if (a > prev) {

				ans *= solve(i - st, 1e9 - prev);
				cout << i << st << endl;
				st = i;
			} else {
				cout << en << st << endl;
				ans *= solve(en - st, 1e9 - prev);
				st = en;
			}

			prev=a;
			

		}

	}

	ans *= solve(n - st - 1, 1e9 - prev);

	cout << ans << endl;

}












