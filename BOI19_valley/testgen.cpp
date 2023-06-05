

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

const ll INF = 100000000000000ll;

int rand(int a, int b) {
	return a + rand()% (b - a + 1);
}
bool used[10000+1];
int main(int argc, char* argv[]) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);


	srand(atoi(argv[1]));
	
	ll n, s, q, se;
	n = rand(1, 6);
	s = rand(1, n);
	q = 400;
	se = rand(1, n);
	cout << n  << ' ' << s << ' ' << q << ' ' << se << endl;
	for (int i = 0; i < n - 1; i++) {
		cout << rand(1, i + 1) << ' ' << i + 2 << ' ' << rand(1, 10) << endl;
	}

	



	FOR(i, 0, s) {
		int cur_shop = rand(1, n);
		while (used[cur_shop]) cur_shop = rand(1, n);
		used[cur_shop]=true;
		cout << cur_shop << endl;
	}

	FOR(i, 0, q) {
		cout << rand(1, n) << ' ' << rand(1, n) << endl;
	}



	
	
}