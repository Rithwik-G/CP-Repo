/*
Centroid Decomp Template (so hard to write bruh)
*/

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

const int N = 2e5 + 5;
const int MS = 20;
int n, q;


// specific to decomp
bool r[N];  // removed
int s[N];   // subtree size



// one for each graph
int pog[N];
int pnew[N];
int digits[N];
int inv = 0;
vi adj[N];
vi adj2[N];

int dog[N];
int dnew[N];

int upnew[N][MS];
int upog[N][MS];


int INF = 1e9;


int jmpog(int x, int d) {
	FOR(i, 0, MS) if (d & (1<<i)) x = upog[x][i]; 
	return x;
}

int lcaog(int x, int y) {
	if (dog[x] < dog[y]) swap(x, y);

	x = jmpog(x, dog[x]-dog[y]);
	if (x == y) return x;
	
	assert(x != 0);
	for (int i = MS-1;i>=0;i--) {
		
		if (upog[x][i] != upog[y][i]) {
			// assert(up[x][i] >= 0 && up[y][i] > 0);
			x = upog[x][i];
			y = upog[y][i];
		}
	}

	return upog[x][0];
}

int jmpnew(int x, int d) {
	FOR(i, 0, MS) if (d & (1<<i)) x = upog[x][i]; 
	return x;
}

int lcanew(int x, int y) {
	if (dnew[x] < dnew[y]) swap(x, y);

	x = jmpnew(x, dnew[x]-dnew[y]);
	if (x == y) return x;
	
	assert(x != 0);
	for (int i = MS-1;i>=0;i--) {
		
		if (upnew[x][i] != upnew[y][i]) {
			x = upnew[x][i];
			y = upnew[y][i];
		}
	}

	return upnew[x][0];
}


void find_dog(int cur, int p = -1) {
	for (int x : adj[cur]) {
		if (x != p) {
			dog[x] = dog[cur] + 1;
			find_dog(x, cur);
		}
	}
}

void find_dnew(int cur, int p = -1) {
	for (int x : adj2[cur]) {
		if (x != p) {
			dnew[x] = dnew[cur] + 1;
			find_dnew(x, cur);
		}
	}
}


int distog(int x, int y) {
	return dog[x] + dog[y] - 2 * dog[lcaog(x, y)];
}

int distnew(int x, int y) {
	return dnew[x] + dnew[y] - 2 * dnew[lcanew(x, y)];
}



int dfs(int n, int p = -1) { // original graph
	upog[n][0]=p;
	pog[n]=p;
	s[n] = 1;
	for (int x: adj[n]) {
		if (x != p && !r[x]) s[n] += dfs(x, n);
	}

	return s[n];
}

int get_centroid(int n, int sz, int p = -1) {
	for (int x : adj[n]) {
		if (x == p || r[x]) continue;
		if (s[x] * 2 > sz) return get_centroid(x, sz, n);
	}
	return n;
}

vector<map<int, int> > poss[N];
vector<vector<pii> > subt;

int ans = 0;
int M;
void solve(int cur, int p = -1) {
	poss[cur].erase(poss[cur].begin(), poss[cur].end());
	subt[cur].erase(subt[cur].begin(), subt[cur].end());
	subt[cur].pb({cur, 0});
	for (auto nx : adj[cur]) {
		if (nx != p) {
			solve(nx, cur);

			for (auto val: subt[nx]) {
				subt[cur].pb({val.f, val.s + 1});
				int pow = (-val + binpow(inv, h) + M) % M;
				if (cur == 1 && poss[cur].find(pow) != poss[cur].end()) ans+=poss[cur][pow];
			}

			for (auto val: poss[nx]) {
				poss[cur][((10 * val + digits[cur]) % M)]++;
			}
		}
	}
}

int cent;
void centroid(int n = 1, int prev = 0) {
	int C = get_centroid(n, dfs(n));

	solve(C);
	pnew[C] = prev;
	if (prev == 0) cent=C;
	r[C] = 1;
	upnew[C][0]=prev;
	adj2[prev].pb(C);
	for (int x : adj[C]) {
		if (!r[x]) {
			centroid(x, C);
		}
	}
}

void init_lifting() {
	FOR(i, 1, MS) FOR(j, 1, n+1) upog[j][i] = upog[upog[j][i-1]][i-1];
	FOR(i, 1, MS) FOR(j, 1, n+1) upnew[j][i] = upnew[upnew[j][i-1]][i-1];
}


int totient(int cur) {
	int result = n;

	for (int p=2; p*p<=n; p++) {
		if (n % p == 0) {
			while (n % p == 0) n/=p;

			result = (result * (p - 1)) / p;
		}
	}

	return result;
}

ll binpow(ll x, ll n, ll m = M) {
	assert(n >= 0);
	x %= m;  // note: m * m must be less than 2^63 to avoid ll overflow
	ll res = 1;
	while (n > 0) {
		if (n % 2 == 1) { res = res * x % m; }
		x = x * x % m;
		n /= 2;
	}
	return res;
}

int main() {
	
	cin >> n >> M;
	inv = binpow(10, totient(M)-1);

	FOR(i, 0, n) cin >> digits[i];
	for (int i = 0; i < n-1; i++) {
		int a, b;
		cin >> a >> b;

		adj[a].pb(b);
		adj[b].pb(a);
	}

	centroid();
	init_lifting();




	cout << ans << endl;
	
	






}