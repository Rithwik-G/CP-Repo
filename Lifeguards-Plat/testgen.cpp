

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

int main(int argc, char* argv[]) {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);


	srand(atoi(argv[1]));
	
	int n = rand(1, 10);
	int k = rand(1, n);
	cout << n << ' ' << k << endl;
	for (int i = 0; i < n; i++) {
		int st = rand(1, 100);
		cout << st << ' ' << rand(st + 1, 1000) << endl;
	}

	
	
}