const ll SZ = 101; // Size of Matrix
const ll MOD = 1e9 + 7;

struct Matrix {
	long long a[SZ][SZ];

	void reset() {
		FOR(i, 0, SZ) FOR(j, 0, SZ) a[i][j]=0; // Reset Matrix
	}

	Matrix operator *(Matrix other) { // multiply two matrices
		Matrix res;
		res.reset();
		FOR(i, 0, SZ) 
			FOR(j, 0, SZ)
				FOR(k, 0, SZ) {
					res.a[i][k] = (res.a[i][k] + a[i][j] * other.a[j][k]) % MOD; // Operation to Multiply

		return product;
	}
};

Matrix exp(Matrix m, int k) {
	Matrix ans;
	ans.reset();
	FOR(i, 0, SZ) ans.a[i][i]=1;

	while (k > 0) {
		if (k % 2 == 1) ans = ans*m;
		m = m*m;
		k/=2;
	}

	return ans;
}