

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

const int N = 2e5 + 10;
const int MX = 20;

int q[N];
int p[N];

int previ[N];

int lifting[N][MX];

int prev_ind[N];

int start_from[N];

	int sp_table[N][MX];

int n, m, qu;




	int query(int l, int r) {
		int dist = log2(r-l + 1);
		return comb(sp_table[l][dist], sp_table[r-(int) pow(2, dist) + 1][dist]);
	}

int jump_back(int pos, int n) {
	FOR(i, 0, MX) {
		if ((1 << i) & n) {
			pos = lifting[pos][i];
		}
	}

	return pos;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	cin >> n >> m >> qu;

	FOR(i, 1, n+1) cin >> p[i];

	previ[p[1]] = p[n];
	FOR(i, 2, n + 1) previ[p[i]] = p[(i - 1 + n) % n];


	FOR(i, 1, m+1) {
		cin >> q[i];

		lifting[i][0] = prev_ind[previ[q[i]]];
		// cout << i << ' ' << lifting[i][0] << endl;
		prev_ind[q[i]]=i;
	}

	FOR(j, 1, MX) {
		FOR(i, 1, N) {
			lifting[i][j] = lifting[lifting[i][j-1]][j-1];

		}
	}

	// cout << lifting[5][1] << endl;


	FOR(i, 1, m + 1) {
		start_from[i]=jump_back(i, n-1);
	}


	FOR(i, 1, m + 1) {
		sp_table[i][0] = start_from[i];	
	}

	FOR(j, 1, MX) {
		FOR(i, 1, m + 1) {
			sp_table[i][j] = max(sp_table[i][j - 1], sp_table[min((int) i + (int) pow(2, j-1), m)][j-1]);
		}
	}
	// cout << sp_table[2][2] << endl;
	// cout << query(1, 5) << endl;
	FOR(i, 0, qu) {
		int a, b;
		cin >> a >> b;
		// cout << 'd' << endl;
		if (query(a, b) >= a) cout << 1;
		else cout << 0;
	}
	cout << endl;

}












