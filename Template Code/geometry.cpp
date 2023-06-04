/**
 * Description: Use in place of \texttt{complex<T>}.
 * Source: http://codeforces.com/blog/entry/22175, KACTL
 * Verification: various
 */

using T = db; // or ll
const T EPS = 1e-9; // adjust as needed
using P = pair<T,T>; using vP = V<P>; using Line = pair<P,P>;
int sgn(T a) { return (a>EPS)-(a<-EPS); }
T sq(T a) { return a*a; }

bool close(const P& a, const P& b) { 
	return sgn(a.f-b.f) == 0 && sgn(a.s-b.s) == 0; } 
T abs2(const P& p) { return sq(p.f)+sq(p.s); }
T abs(const P& p) { return sqrt(abs2(p)); }
T arg(const P& p) { return atan2(p.s,p.f); }
P conj(const P& p) { return P(p.f,-p.s); }
P perp(const P& p) { return P(-p.s,p.f); }
P dir(T ang) { return P(cos(ang),sin(ang)); }

P operator-(const P& l) { return P(-l.f,-l.s); }
P operator+(const P& l, const P& r) { 
	return P(l.f+r.f,l.s+r.s); }
P operator-(const P& l, const P& r) { 
	return P(l.f-r.f,l.s-r.s); }
P operator*(const P& l, const T& r) { 
	return P(l.f*r,l.s*r); }
P operator*(const T& l, const P& r) { return r*l; }
P operator/(const P& l, const T& r) { 
	return P(l.f/r,l.s/r); }
P operator*(const P& l, const P& r) { 
	return P(l.f*r.f-l.s*r.s,l.s*r.f+l.f*r.s); }
P operator/(const P& l, const P& r) { 
	return l*conj(r)/abs2(r); }
P& operator+=(P& l, const P& r) { return l = l+r; }
P& operator-=(P& l, const P& r) { return l = l-r; }
P& operator*=(P& l, const T& r) { return l = l*r; }
P& operator/=(P& l, const T& r) { return l = l/r; }
P& operator*=(P& l, const P& r) { return l = l*r; }
P& operator/=(P& l, const P& r) { return l = l/r; }

P unit(const P& p) { return p/abs(p); }
T dot(const P& a, const P& b) { return a.f*b.f+a.s*b.s; }
T dot(const P& p, const P& a, const P& b) { return dot(a-p,b-p); }
T cross(const P& a, const P& b) { return a.f*b.s-a.s*b.f; }
T cross(const P& p, const P& a, const P& b) {
	return cross(a-p,b-p); }
P reflect(const P& p, const Line& l) {
	P a = l.f, d = l.s-l.f;
	return a+conj((p-a)/d)*d; }
P foot(const P& p, const Line& l) {
	return (p+reflect(p,l))/(T)2; }
bool onSeg(const P& p, const Line& l) {
	return sgn(cross(l.f,l.s,p)) == 0 && sgn(dot(p,l.f,l.s)) <= 0; }


// {unique intersection point} if it exists
// {b.f,b.s} if input lines are the same
// empty if lines do not intersect
vP lineIsect(const Line& a, const Line& b) {
	T a0 = cross(a.f,a.s,b.f), a1 = cross(a.f,a.s,b.s); 
	if (a0 == a1) return a0 == 0 ? vP{b.f,b.s} : vP{};
	return {(b.s*a0-b.f*a1)/(a0-a1)};
}

// point in interior of both segments a and b, if it exists
vP strictIsect(const Line& a, const Line& b) {
	T a0 = cross(a.f,a.s,b.f), a1 = cross(a.f,a.s,b.s); 
	T b0 = cross(b.f,b.s,a.f), b1 = cross(b.f,b.s,a.s); 
	if (sgn(a0)*sgn(a1) < 0 && sgn(b0)*sgn(b1) < 0)
		return {(b.s*a0-b.f*a1)/(a0-a1)};
	return {};
}

// intersection of segments, a and b may be degenerate
vP segIsect(const Line& a, const Line& b) { 
	vP v = strictIsect(a,b); if (sz(v)) return v;
	set<P> s;
	#define i(x,y) if (onSeg(x,y)) s.ins(x)
	i(a.f,b); i(a.s,b); i(b.f,a); i(b.s,a);
	return {all(s)};
}