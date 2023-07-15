// Source: https://codeforces.com/edu/course/2/lesson/2/5/practice/contest/269656/problem/B
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

void countsort(vector<int> &p, vi &c) {
	int n = p.size();

	vi cnt(n);

	FOR(i, 0, n) cnt[c[i]]++;

	vector<int> p_new(n);
	vector<int> pos(n);

	pos[0] = 0;

	for(int i = 1; i < n; i++) pos[i] = pos[i-1] + cnt[i-1];

	for (auto x: p) {
		int i = c[x];
		p_new[pos[i]] = x;
		pos[i]++;
	}

	p = p_new;

}

pair<vi, vi> get_sufflcp_array(string s) {
	s += "$";

	int n = s.size();


	vi p(n), c(n);

	{
		// k = 0
		vector<pair<char, int> > a(n);

		FOR(i, 0, n) a[i] = {s[i], i};
		sort(a.begin(), a.end());

		FOR(i, 0, n) p[i] = a[i].s;

		c[p[0]]=0;

		FOR(i, 1, n) {
			if (a[i].f == a[i-1].f) c[p[i]] = c[p[i-1]];
			else c[p[i]] = c[p[i-1]] + 1;
		}
	}

	int k = 0;
	while ((1 << k) < n) {
		// k -> k + 1

		FOR(i, 0, n) p[i] = (p[i] - (1 << k) + n) % n;

		countsort(p, c);

		vi c_new(n);

		c_new[p[0]] = 0;

		FOR(i, 1, n) {
			pii prev = {c[p[i-1]], c[(p[i-1] + (1 << k)) % n]};
			pii now = {c[p[i]], c[(p[i] + (1 << k)) % n]};
			
			if (now == prev) c_new[p[i]] = c_new[p[i-1]];
			else c_new[p[i]] = c_new[p[i-1]] + 1;
		}

		c = c_new;

		

		k++;
	}

	vi lcp(n);

	k = 0;

	FOR(i, 0, n) {
		int pi = c[i];
		if (pi == 0) continue;
		int j = p[pi - 1];

		// LCP of these two suffixes
		while (s[i + k] == s[j + k]) k++;
		lcp[pi]=k;

		k = max(k-1, 0);
	}



	return {p, lcp};
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	string s;
	cin >> s;

	vi suff;
	vi lcp;

	tie(suff, lcp)=get_sufflcp_array(s);

	ll ans = 0;

	FOR(i, 0, suff.size()) {
		ans += (s.size() - suff[i]) - lcp[i];
	}

	cout << ans << endl;

}












