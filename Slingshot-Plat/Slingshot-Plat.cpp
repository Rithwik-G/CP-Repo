// Source: http://www.usaco.org/index.php?page=viewproblem2&cpid=816
// Integer Overflow for some reason

#include "bits/stdc++.h"

using namespace std;

#define s second
#define f first
#define pb push_back

typedef long long ll;

typedef pair<ll, ll> pii;
typedef vector<pii> vpii;

typedef vector<ll> vi;

const ll INF = 1e18;

#define FOR(i, a, b) for (ll i = (a); i<b; i++)

template <class T> class MinSegmentTree {
  private:
	const T DEFAULT = 1e15;  // Will overflow if T is an ll

	vector<T> segtree;
	ll len;

  public:
	MinSegmentTree(ll len) : len(len), segtree(len * 2, DEFAULT) {}

	/** Sets the value at ind to val. */
	void upd(ll ind, T val) {
		ind += len;
		segtree[ind] = min(val, segtree[ind]);
		for (; ind > 1; ind /= 2) {
			segtree[ind / 2] = std::min(segtree[ind], segtree[ind ^ 1]);
		}
	}

	/** @return the minimum element in the range [start, end) */
	T range_min(ll start, ll end) {
		T sum = DEFAULT;
		for (start += len, end += len; start < end; start /= 2, end /= 2) {
			if (start % 2 == 1) { sum = std::min(sum, segtree[start++]); }
			if (end % 2 == 1) { sum = std::min(sum, segtree[--end]); }
		}
		return sum;
	}
};

vi vy;

ll conv(ll val) {
	return lower_bound(vy.begin(),vy.end(),val) - vy.begin();
}


int main() {

	freopen("slingshot.in", "r", stdin);
	freopen("slingshot.out", "w", stdout);
	ios::sync_with_stdio(false);
	cin.tie(nullptr);

	long long n, q;
	cin >> n >> q;


	vector<array<long long, 3> > sl(n);
	vector<array<long long, 2> > queries(q);

	vector<ll> cid(n);
	vector<ll> qid(q);

	FOR(i, 0, n) {
		cid[i]=i;
		cin >> sl[i][0] >> sl[i][1] >> sl[i][2];
		vy.pb(sl[i][1]);
	}
	vi ansBef(q, INF);
	FOR(i, 0, q) {
		qid[i]=i;
		cin >> queries[i][0] >> queries[i][1];
		ansBef[i] = abs(queries[i][1]-queries[i][0]);

		vy.pb(queries[i][1]);
	}

	sort(cid.begin(), cid.end(), [&](ll a, ll b){
		return (sl[a][0] < sl[b][0]);
	});

	sort(qid.begin(), qid.end(), [&](ll a, ll b){
		return (queries[a][0] < queries[b][0]);
	});

	sort(vy.begin(),vy.end());
	vy.resize(distance(vy.begin(),unique(vy.begin(),vy.end())));

	MinSegmentTree<ll> up(n + q + 10), down(n + q + 10);

	ll cur_s = 0;

	

	for (ll i = 0; i < q; i++) {
		while (cur_s != n && sl[cid[cur_s]][0] <= queries[qid[i]][0]) {
			// if (sl[cid[cur_s]][0] > sl[cid[cur_s]][1]) {
			// 	cur_s++;
			// 	continue;
			// }

			up.upd(conv(sl[cid[cur_s]][1]), - sl[cid[cur_s]][0] + sl[cid[cur_s]][1] + sl[cid[cur_s]][2]);
			down.upd(conv(sl[cid[cur_s]][1]), - sl[cid[cur_s]][0] - sl[cid[cur_s]][1] + sl[cid[cur_s]][2]);
			cur_s ++;
		}

		array<long long, 2> cur = queries[qid[i]];

		ansBef[qid[i]] = min(ansBef[qid[i]], min( cur[0] - cur[1] + up.range_min(conv(cur[1]), n + q + 10), cur[0] + cur[1] + down.range_min(0, conv(cur[1]))));
		// cout << qid[i] << endl;
	}



	MinSegmentTree<ll> up2(n + q + 10), down2(n + q + 10);

	cur_s = n-1;

	vi ansAft(q, INF);

	for (ll i = q-1; i >= 0; i--) {
		while (cur_s != -1 && sl[cid[cur_s]][0] >= queries[qid[i]][0]) {
			// if (sl[cid[cur_s]][0] < sl[cid[cur_s]][1]) {
			// 	cur_s++;
			// 	continue;
			// }
			up2.upd(conv(sl[cid[cur_s]][1]), sl[cid[cur_s]][0] + sl[cid[cur_s]][1] + sl[cid[cur_s]][2]);
			down2.upd(conv(sl[cid[cur_s]][1]), sl[cid[cur_s]][0] - sl[cid[cur_s]][1] + sl[cid[cur_s]][2]);
			cur_s --;
		}

		array<long long, 2> cur = queries[qid[i]];

		ansAft[qid[i]] = min( -cur[0] - cur[1] + up2.range_min(conv(cur[1]), n + q + 10), -cur[0] + cur[1] + down2.range_min(0, conv(cur[1])));
	
	}

	FOR(i, 0, q) cout << (long long) min(ansAft[i], ansBef[i]) << endl;

	




}












