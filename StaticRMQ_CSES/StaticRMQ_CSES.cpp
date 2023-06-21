// Source: https://cses.fi/problemset/task/1647
// AC (uses online D&C not sparse table)

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


int n, q;

const int MX = 2e5+10;
int x[MX];

int dat[18][MX], mask[MX];  // 18 = ceil(log2(n))

void divi(int l, int r, int lev) {  // generate dat and mask
	if (l == r) return;
	int m = (l + r) / 2;
	dat[lev][m] = x[m]; // set default lefthand value

	for (int i = m-1; i >= l; i--) dat[lev][i] = min(x[i], dat[lev][i + 1]); // gen left hand values

	// same thing for right side
	dat[lev][m + 1] = x[m + 1];
	for (int i = m + 2; i <= r; i++) dat[lev][i] = min(dat[lev][i - 1], x[i]);


	for (int i = m + 1; i <= r; i++) mask[i] ^= 1 << lev; // signify with mask that these values we move right
	
	divi(l, m, lev + 1);
	divi(m + 1, r, lev + 1);
}

int main() {
	cin >> n >> q;

	FOR(i, 1, n+1) cin >> x[i];

	divi(1, n, 0);
	FOR(i, 0, q) {
		int a, b;
		cin >> a >>	 b;
		if (a == b) cout << x[a] << endl;
		else {  // find level where info is stored
			// ctz gives number of trailing zeroes
			int bits = __builtin_ctz(mask[a] ^ mask[b]); // how many starting left/right movements are the same
			cout << min(dat[bits][a], dat[bits][b]) << endl;
		}
	}
}












