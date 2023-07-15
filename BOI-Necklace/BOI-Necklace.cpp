// Source: https://oj.uz/problem/view/BOI19_necklace4
// AC

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

int p1[6005];
int p2[6005];

void get_kmp(string s, int *pi_s) {
	int n = (int)s.size();

	for (int i = 1, j = 0; i < n; i++) {
		while (j > 0 && s[j] != s[i]) { j = pi_s[j - 1]; } // next smallest prefix that is also a suffix
		if (s[i] == s[j]) { j++; }
		pi_s[i] = j;
	}
}

pair<int, pii> solve(string s, string t, bool rev) {
	int n = s.size();
	int m = t.size();

	string t_rev = t;

	reverse(t_rev.begin(), t_rev.end());

	pair<int, pii> ans;

	for (int i = 0; i < n; i++) {

		string s1 = s.substr(0, i);
		string s2 = s.substr(i, n - i);

		reverse(s1.begin(), s1.end());

		get_kmp(s1 + "$" + t, p1);
		get_kmp(s2 + "$" + t_rev, p2);

		for (int j = 1; j <= m; j++) {
			ans = max(ans, {p1[i + j] + p2[n - i + m - j], {i - p1[i + j], rev ? m - j - p2[n - i + m - j] : j - p1[i + j]}});
		}

	}

	return ans;
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	string a, b;
	cin >> a >> b;

	auto ans = solve(a, b, false);
	reverse(b.begin(), b.end());

	ans = max(ans, solve(a, b, true));
	cout << ans.f << '\n' << ans.s.f << ' ' << ans.s.s << endl;
}












