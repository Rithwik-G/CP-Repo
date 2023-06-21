// Source: https://codeforces.com/contest/220/problem/B
// Basic Mo's

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

const int block_size = 300;

struct Query {
    int l, r, idx;
    bool operator<(Query other) const
    {
        return make_pair(l / block_size, r) <
               make_pair(other.l / block_size, other.r);
    }
};

const int N = 1e5 + 10;

int freq[N];
Query queries[N];
int a[N];
int ans[N];
int n, Q;
int answer = 0;
int answers[N];
int get_answer() {
	return answer;
}

void remove(int idx) {
	if (a[idx] > n) return;
	if (freq[a[idx]] == a[idx]) answer--;
	freq[a[idx]]--;
	if (freq[a[idx]] == a[idx]) answer++;

}

void add(int idx) {
	if (a[idx] > n) return;
	if (freq[a[idx]] == a[idx]) answer--;
	freq[a[idx]]++;
	if (freq[a[idx]] == a[idx]) answer++;


}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	

	
	cin >> n >> Q;

	FOR(i, 1, n + 1) {
		cin >> a[i];
	}

	FOR(i, 0, Q) {
		cin >> queries[i].l >> queries[i].r;
		queries[i].idx = i;
	}

	sort(queries, queries + Q);

	int cur_l = 0;
    int cur_r = -1;

	for (int i = 0; i < Q; i++) {
		auto q = queries[i];
		while (cur_l > q.l) {
            cur_l--;
            add(cur_l);
        }
        while (cur_r < q.r) {
            cur_r++;
            add(cur_r);
        }
        while (cur_l < q.l) {
            remove(cur_l);
            cur_l++;
        }
        while (cur_r > q.r) {
            remove(cur_r);
            cur_r--;
        }
        answers[q.idx] = get_answer();
	} 
	FOR(i, 0, Q) {
		cout << answers[i] << endl;
	}

}












