

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

set<int> in[N];
set<int> out[N];
set<int> child[N];

int ans = 0;
queue<pii> to_merge;

struct DSU {
	vector<int> e;
	DSU(int N) { e = vector<int>(N, -1); }

	// get representive component (uses path compression)
	int get(int x) { return e[x] < 0 ? x : e[x] = get(e[x]); }

	bool same_set(int a, int b) { return get(a) == get(b); }

	int size(int x) { return -e[get(x)]; }

	void add_conn(int a, int b) {
		in[a].insert(b);
		out[b].insert(a);

		if (out[a].find(b) != out[a].end()) to_merge.push({a, b});
	}

	void merge(int x, int y) {  // union by size
		child[get(y)].insert(x);
		x = get(x), y = get(y);
		if (x == y) return;
		if (!child[y].count(x)) return;
		ans += -e[y];

		if (out[y].find(x) == out[y].end()) {
			out[x].insert(y);
			in[y].insert(x);
			return;
		}
		if (-e[x] > -e[y]) swap(x, y);
		// cout << ' ' << e[y] << endl;		

		ans += -e[x]*child[y].size() + -e[y]*child[x].size();
		
		for (auto val: child[x]) {
			if (child[y].count(val)) ans -= -e[y];
			else child[y].insert(val);
		}
		
		for (auto val: in[x]) {
			out[val].erase(x);
			add_conn(y, val);
		}
		for (auto val: out[x]) {
			in[val].erase(x);
			add_conn(val, y);
		}
		// cout << e[x] << e[y] << endl;
		e[y] += e[x]; 

	}
};

DSU dsu(N);

int n, m;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);



	cin >> n >> m;

	FOR(i, 0, m) {
		int a, b;
		cin >> a >> b;
		dsu.merge(a, b);

		while (!to_merge.empty()) {
			dsu.merge(to_merge.front().f, to_merge.front().s);
			to_merge.pop();
		}
		cout << ans << endl;
	}
}












