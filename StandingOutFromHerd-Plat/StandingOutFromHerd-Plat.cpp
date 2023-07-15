// Source: http://www.usaco.org/index.php?page=viewproblem2&cpid=768
//  

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

bool ckmin(ll& a, ll b){ return b < a ? a = b, true : false; }

bool ckmax(ll& a, ll b){ return b > a ? a = b, true : false; }

void countsort(vector<ll> &p, vi &c) {
	ll n = p.size();

	vi cnt(n);

	FOR(i, 0, n) cnt[c[i]]++;

	vector<ll> p_new(n);
	vector<ll> pos(n);

	pos[0] = 0;

	for(ll i = 1; i < n; i++) pos[i] = pos[i-1] + cnt[i-1];

	for (auto x: p) {
		ll i = c[x];
		p_new[pos[i]] = x;
		pos[i]++;
	}

	p = p_new;

}

pair<vi, vi> get_sufflcp_array(string s) {
	s += "$";

	ll n = s.size();


	vi p(n), c(n);

	{
		// k = 0
		vector<pair<char, ll> > a(n);

		FOR(i, 0, n) a[i] = {s[i], i};
		sort(a.begin(), a.end());

		FOR(i, 0, n) p[i] = a[i].s;

		c[p[0]]=0;

		FOR(i, 1, n) {
			if (a[i].f == a[i-1].f) c[p[i]] = c[p[i-1]];
			else c[p[i]] = c[p[i-1]] + 1;
		}
	}

	ll k = 0;
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
		ll pi = c[i];
		if (pi == 0) continue;
		ll j = p[pi - 1];

		// LCP of these two suffixes
		while (s[i + k] == s[j + k]) k++;
		lcp[pi]=k;

		k = max(k-1ll, 0ll);
	}



	return {p, lcp};
}

ll get_unique_sub(string s) {
	vi suff;
	vi lcp;

	tie(suff, lcp)=get_sufflcp_array(s);

	ll ans = 0;

	FOR(i, 0, suff.size()) {
		ans += (s.size() - suff[i]) - lcp[i];
	}

	return ans;
}


int main() {
	// freopen("standingout.in", "r", stdin);
	// freopen("standingout.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	ll n;
	cin >> n;

	string s;
	string cur;

	vi inds(n+1);

	vector<vi> max_dist(n+1);
	vector<string> inp(n+1);
	vi ans(n + 1);
	inds[0]=0;
	FOR(i, 1, n + 1) {
		cin >> cur;
		s+=cur+'$';
		inds[i] = s.size();

		inp[i] = cur;

		max_dist[i] = vi(cur.size(), 0);

		ans[i] = get_unique_sub(cur);
	}

	vi suff, lcp;

	tie(suff, lcp) = get_sufflcp_array(s);

	int l = 0;
	int r = 0;

	int lc = upper_bound(inds.begin(), inds.end(), suff[l]) - inds.begin();
	int rc = upper_bound(inds.begin(), inds.end(), suff[l]) - inds.begin();
	lcp.pb(0);

	while (r != suff.size()) {
		assert(l == r);
		if (s[suff[l]] == '$' && suff[l] != s.size()) {
			l++;
			r++;
			continue;
		}

		lc = upper_bound(inds.begin(), inds.end(), suff[l]) - inds.begin();
		rc = upper_bound(inds.begin(), inds.end(), suff[r]) - inds.begin();
		while (lc == rc) {
			r++;
			
			if (r == suff.size()) break;
			cout << "    " << s.substr(suff[r], s.size()) << endl;
			rc = upper_bound(inds.begin(), inds.end(), suff[r]) - inds.begin();
		}

		cout << lc << ' ' << s.substr(suff[l], s.size()) << ' ' << max(lcp[l-1], lcp[r]) << endl;
		ans[lc] -= max(lcp[l-1], lcp[r]);

		l = r;
	}

	FOR(i, 1, n + 1)cout << ans[i] << endl;

	// FOR(i, 0, suff.size()) {
	// 	if (s[suff[i]] == '$' || s[suff[i-1]] == '$') continue;
	// 	ll a = upper_bound(inds.begin(), inds.end(), suff[i]) - inds.begin();
	// 	ll b = upper_bound(inds.begin(), inds.end(), suff[i-1]) - inds.begin();
	// 	cout << s.substr(suff[i], s.size()) << endl;
	// 	if (a != b) {
	// 		cout << a << endl;
	// 		ckmax(max_dist[a][suff[i] - inds[a-1]], lcp[i]);
	// 		// ckmax(max_dist[b][suff[i-1] - inds[b-1]], lcp[i]);
	// 	}
	// }

	// ll i = suff.size() - 1;
	// ll st = upper_bound(inds.begin(), inds.end(), suff[i]) - inds.begin();
	// ll a = st;
	// while (a == st) {
	// 	i--;
	// 	a = upper_bound(inds.begin(), inds.end(), suff[i]) - inds.begin();
	// }
	// i++;
	// a = upper_bound(inds.begin(), inds.end(), suff[i]) - inds.begin();

	// ckmax(max_dist[a][suff[i] - inds[a-1]], lcp[i]);

	// FOR(i, 1, n + 1) {
	// 	ll cur = get_unique_sub(inp[i]);

	// 	FOR(j, 0, inp[i].size()) {
	// 		cout << i << j << min(max_dist[i][j], (ll) inp[i].size() - j) << endl;
	// 		cur -= min(max_dist[i][j], (ll) inp[i].size() - j);
	// 	}
	// 	cout << cur << endl;
	// }

	





}












