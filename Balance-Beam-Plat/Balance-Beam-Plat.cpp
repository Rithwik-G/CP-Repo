// Source: http://www.usaco.org/index.php?page=viewproblem2&cpid=864


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

// use built in complex number support

typedef long long T;
typedef complex<T> pt;
#define x real()
#define y imag()

T dot(pt a, pt b) {return (conj(a)*b).x;} // very cryptic but works
T cross(pt a, pt b) {return (conj(a)*b).y;}

T orient(pt a, pt b, pt c) {return cross(b-a,c-a);} // whether you go "left" or "right"
T dist(pt a) {
	return (a.x) * (a.x) + (a.y) * (a.y);
}

long long slope(pt a, pt b) {return ( 1e5 * (a.y - b.y)) / ( (a.x - b.x)); } // slope from a -> b

vector<pt> Hull(vector<pt> v) {
	int ind = int(min_element(v.begin(), v.end(), [&](pt p1, pt p2) {
		if (p1.x == p2.x) return p1.y < p2.y;
		else return p1.x < p2.x;
	}
	) - v.begin());

	pt pivot = v[ind];

	vector<pt> hull{pivot};
	vi cand;

	FOR(i, 0, v.size()) if (v[i] != pivot) cand.pb(i);	


	sort(cand.begin(), cand.end(), [&](int p1, int p2) {
		pt pt1 = v[p1] - pivot;
		pt pt2 = v[p2] - pivot;
		T cr = cross(pt1, pt2);
		return cr != 0 ? cr > 0 : dist(pt1) < dist(pt2);
	});

	for (auto ind : cand) {
		while (hull.size() > 1 && cross(hull[hull.size() - 2] - v[ind], hull[hull.size() - 1] - v[ind]) <= 0) {
			hull.pop_back();
		}
		hull.pb(v[ind]);
	}

	return hull;
}


int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	freopen("balance.in", "r", stdin);
	freopen("balance.out", "w", stdout);

	int n;
	cin >> n;

	vector<pt> p(n + 2);
	int a;

	p[0] = {0, 0};
	FOR(i, 1, n + 1) {
		cin >> a;
		p[i] = {i, a};
	}

	p[n + 1] = {n + 1, 0};
	

	vector<pt> hull = Hull(p);
	int st;
	FOR(i, 0, hull.size()) {
		// cout << hull[i].x << ' ' << hull[i].y << endl;
		if (hull[i].x == 0) st = i;
	}

	int cur = 1;

	bool first = true;
	double sl;
	double val = 0;
	for (int i = st; ; i = (i - 1 + hull.size()) % hull.size()) {
		// sl = slope(hull[i], hull[(i - 1 + hull.size()) % hull.size()]);
		int cur_x = hull[(i - 1 + hull.size()) % hull.size()].x;
		int along = 0;
		while (cur_x >= cur) {
			// val += sl;
			// cout << cur_x << endl;
			cout << (long long) (val * 1e5) << endl;
			cur++;
			if (cur == n+1)break;
		}
		// cout << cur << endl;
		if (cur == n+1) break;
		// if (i == )
	}

}












