// Source: http://www.usaco.org/index.php?page=viewproblem2&cpid=948
// 

// #include "bits/stdc++.h"
#include "grader.h"

using namespace std;

#define s second
#define f first
#define pb push_back

typedef long long ll;

typedef pair<ll, ll> pii;
typedef vector<pii> vpii;

typedef vector<ll> vi;

#define FOR(i, a, b) for (ll i = (a); i<b; i++)

// void addBox(int a, int b, int c, int d) {
// 	cout << a << b << c << d << endl;
// }

// int getN() {
// 	return 3;
// }

// void setFarmLocation(int ind, int a, int b) {
// 	cout << ind <<  ' ' << a << b << endl;
// }


const int N = 1e5 + 10;
const int MX = 20;

vi adj[N];
pii positions[N];
int up[N][20];
int dep[N];

int sz[N];


void get_sz(int cur, int prev = -1, int d = 0) {
	up[cur][0]=prev;
	dep[cur] = d;
	for (auto child: adj[cur]) {
		if (child == prev) continue;

		get_sz(child, cur, d + 1);
		sz[cur]+=sz[child];

	}

	sz[cur]++;
}

void solve(int x1, int y1, int x2, int y2, int ind, int prev = -1) {
	positions[ind] = {x1, y1};
	setFarmLocation(ind, x1, y1);
	int cur_x = x1;
	int cur_y = y2;
	for (auto child: adj[ind]) {
		if (child == prev) continue;

		solve(cur_x, cur_y - sz[child] + 1, cur_x + sz[child]-1, cur_y, child, ind);

		cur_y -= sz[child];
		cur_x += sz[child];

	}
}


void addRoad(int a, int b){
	adj[a].pb(b);
	adj[b].pb(a);
}

void buildFarms(){
	int n = getN();
	get_sz(0);
	solve(1, 1, n, n, 0);

	FOR(j, 1, MX) FOR(i, 0, n) if (up[i][j-1] != -1) up[i][j] = up[up[i][j-1]][j-1];
}

int jmp(int x, int d) {
	FOR(i, 0, MX) if (d & (1<<i)) x = up[x][i]; 
	return x;
}

int lca(int x, int y) {
	if (dep[x] < dep[y]) swap(x, y);

	x = jmp(x, dep[x]-dep[y]);
	if (x == y) return x;
	
	assert(x != 0);
	for (int i = MX-1;i>=0;i--) {
		
		if (up[x][i] != up[y][i]) {
			x = up[x][i];
			y = up[y][i];
		}
	}

	return up[x][0];
}

void send(int x1, int y1, int x2, int y2) {
	addBox(min(x1, x2), min(y1, y2), max(x1, x2), max(y1, y2));
}

void notifyFJ(int a, int b){
	int h = lca(a, b);
	// cout << up[2][0] << endl;
	if (h == b) swap(a, b);

	if (h == a) {
		send(positions[b].f, positions[b].s, positions[h].f, positions[h].s);
	} else {
		send(positions[b].f, positions[b].s, positions[h].f, positions[h].s);
		h = jmp(a, dep[a]-dep[h] - 1);
		send(positions[a].f, positions[a].s, positions[h].f, positions[h].s);
	}

}



// int main() {
// 	addRoad(0, 1);
// 	addRoad(0, 2);
// 	buildFarms();

// 	notifyFJ(1, 2);

// }









