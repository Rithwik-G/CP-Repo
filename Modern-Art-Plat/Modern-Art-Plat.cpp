// Source: http://www.usaco.org/index.php?page=viewproblem2&cpid=744


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

bool ckmin(int& a, int b){ return b < a ? a = b, true : false; }
bool ckmax(int& a, int b){ return b > a ? a = b, true : false; }

const int N = 1001;

int coords[N*N][4]; // min_x, min_y, max_x, max_y

int pref[N][N];

int arr[N][N];
bool poss[N * N];

int main() {
	freopen("art.in", "r", stdin);
	freopen("art.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n;
	cin >> n;

	FOR(i, 0, n*n + 1) {
		coords[i][0] = N;
		coords[i][1]= N;
	}
	int cnt = 0;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			
			int a;
			cin >> a;
			if (coords[a][2] == 0) cnt++;
			arr[i][j] = a;
			ckmin(coords[a][0], i);
			ckmax(coords[a][2], i + 1);
			ckmin(coords[a][1], j);
			ckmax(coords[a][3], j + 1);
		}
	}

	if (cnt == 0) {
		cout << 0 << endl;
		return 0;
	} else if (cnt == 1) {
		cout << n*n - 1 << endl;
		return 0;
	}

	FOR(i, 1, n*n + 1) {
		poss[i] = true;
		if (coords[i][2] == 0 || coords[i][3] == 0) continue;
		// cout << i << endl;
		// FOR(k, 0, 4) cout << coords[i][k] << ' ';
		// cout << endl;
		pref[coords[i][0]][coords[i][1]]++;
		pref[coords[i][0]][coords[i][3]]--;
		pref[coords[i][2]][coords[i][1]]--;
		pref[coords[i][2]][coords[i][3]]++;
	}

	FOR(i, 0, n) {
		FOR(j, 0, n) {
			int res = pref[i][j];
			if (i) res += pref[i-1][j];
			if (j) res += pref[i][j - 1];

			if (i && j) res -= pref[i-1][j - 1];
			// cout << pref[i][j] << res << ' ';
			if (res > 1) {
				// cout << i << j << endl;
				poss[arr[i][j]] = false;
			}

			pref[i][j]=res;

		}
		// cout << endl;
	}
	int ans = 0;
	FOR(i, 1, n*n + 1) {

		ans += poss[i];
	}

	cout << ans << endl;

}












