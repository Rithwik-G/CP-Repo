// Sparse Table
// O(nlogn) Pre with O(1) over all "overlappable" functions (comb)

const int N = 2e5;
const int MX = 23;

int sp_table[N][MX];

void build(int arr[]) {

	FOR(i, 1, n + 1) sp_table[i][0] = arr[i];	
	

	FOR(j, 1, MX) 
		FOR(i, 1, n + 1)
			sp_table[i][j] = comb(sp_table[i][j - 1], sp_table[min((int) i + (int) pow(2, j-1), n)][j-1]);
		
	
}

int query(int l, int r) {
	int dist = log2(r-l + 1);
	return comb(sp_table[l][dist], sp_table[r-(int) pow(2, dist) + 1][dist]);
}