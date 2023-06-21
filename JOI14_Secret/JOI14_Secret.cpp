// https://oj.uz/problem/view/JOI14_secret
// AC
#include "secret.h"
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

int prefix[1000][1000];

const int MX = 2e5;

int dat[18][MX], mask[MX];

int x[MX];

void divi(int l, int r, int lev) {  // generate dat and mask for [l, r]
	if (l == r) return;
	int m = (l + r) / 2;
	dat[lev][m] = x[m]; // set default lefthand value

	for (int i = m-1; i >= l; i--) dat[lev][i] = Secret(x[i], dat[lev][i + 1]); // gen left hand values

	// same thing for right side
	dat[lev][m + 1] = x[m + 1];
	for (int i = m + 2; i <= r; i++) dat[lev][i] = Secret(dat[lev][i - 1], x[i]);


	for (int i = m + 1; i <= r; i++) mask[i] ^= 1 << lev; // signify with mask that these values we move right
	
	divi(l, m, lev + 1);
	divi(m + 1, r, lev + 1);
}


void Init(int N, int a[]) {
	FOR(i, 0, N) x[i] = a[i];
	divi(0, N-1, 0);
}

int Query(int l, int r) {
	if (l == r) return x[l];
	else {  // find level where info is stored
		// ctz gives number of trailing zeroes
		int bits = __builtin_ctz(mask[l] ^ mask[r]); // how many starting left/right movements are the same
		return Secret(dat[bits][l], dat[bits][r]);
	}
}















