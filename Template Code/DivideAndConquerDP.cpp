const int INF = 1e9;

int C(int j, int i) { // returns cost of range from (j, i]

}

void solve(ll k, ll ia, ll ib, ll ja, ll jb) { // solves range [ia, ib) assuming the previous DP can be from [ja, jb]
	if (ia == ib) return;

	ll i = (ia + ib) / 2;
	ll arg_j = -1;

	dp[k][i] = INF;

	for (ll j = ja; j <= jb; j++) {
		ll v = C(j, i) + dp[k - 1][j];

		if (v < dp[k][i]) {

			arg_j = j;
			dp[k][i] = v;
		}
	}

	solve(k, ia, i, ja, arg_j);
	solve(k, i + 1, ib, arg_j, jb);

}