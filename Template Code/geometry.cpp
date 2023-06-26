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