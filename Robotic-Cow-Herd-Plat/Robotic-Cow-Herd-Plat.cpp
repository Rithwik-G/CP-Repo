



// Source: http://www.usaco.org/index.php?page=viewproblem2&cpid=674
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

vector<vi> models;
int suff_sum[N];

int cur_count;

int n, k;

int m;

int tot_cost = 0;

int state[N];


bool solve(int model, int ind, int cur_cost) {

	if (cur_cost > m) return cur_count <= k;
	
	cur_count++;
	
	tot_cost += cur_cost;

	if (ind + 1 < models[model].size()) solve(model, ind + 1, cur_cost + models[model][ind + 1] - models[model][ind]);

	for (int i = model + 1; i < models.size(); i++) {
		int nxt = cur_cost + models[i][0];

		if (nxt > m) break;

		solve(i, 0, nxt);
	}
	

	return cur_count <= k;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	// freopen("roboherd.in", "r", stdin);
	// freopen("roboherd.out", "w", stdout);
	
	cin >> n >> k;

	

	FOR(i, 0, n) {
		cin >> m;
		int s;
		cin >> s;
		vi cur(m - 1);
		FOR(j, 1, m) {
			int a;
			cin >> a;
			cur[j-1] = a-s;
		}
		sort(cur.begin(), cur.end());
		if (cur.size() != 0) models.pb(cur);
	}

	sort(models.begin(), models.end());

	for (int i = n - 1; i>= 0; i--) suff_sum[i] = suff_sum[i + 1] + models[i][0];

	int hi = 100;
	int lo = 0;
	int res = 0;

	FOR(i, 0, n) {
		res += models[i][0];
	}

	while (lo < hi) {
		m = (lo + hi + 1)/2;

		
		cur_count = 0;
		FOR(i, 0, n) {
			state[i]=1;
		}
		FOR(i, 0, models.size()) solve(i, 0, res);

		if (cur_count < k) lo = m;
		else hi = m-1;

	}
	cout << lo << endl;
	m = lo;
	tot_cost = 0;
	cur_count = 0;
	// assert(solve(res));
	cout << cur_count << endl;
	cout << (k - cur_count) * (lo + 1) + tot_cost << endl;



}





















