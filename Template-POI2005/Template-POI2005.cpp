// source: 

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

vi get_kmp(string s) {
	int n = (int)s.size();
	vector<int> pi_s(n, 0);

	for (int i = 1, j = 0; i < n; i++) {
		while (j > 0 && s[j] != s[i]) { j = pi_s[j - 1]; } // next smallest prefix that is also a suffix
		if (s[i] == s[j]) { j++; }
		pi_s[i] = j;
	}
	return pi_s;
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	string s;

	cin >> s;

	vi kmp = get_kmp(s);

	for (auto i : kmp) cout << i << ' ';

	cout << endl;

}












