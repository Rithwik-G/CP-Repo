// Source: https://codeforces.com/gym/102644/problem/A
// AC


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


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	int n;
	long double p;
	cout << setprecision(12);

	cin >> n >> p;

	long double ans = 0;

	while (n > 0) {
		if (n % 2 == 1) ans = (1.0 - ans) * p + (1.0 - p) * ans;
		p = p * (1.0 - p) * 2;
		n/=2;
	}

	cout << 1-ans << endl;



}












