// Euler Totient Function in O(sqrt(n))

int totient(int cur) {
	int result = n;

	for (int p=2; p*p<=n; p++) {
		if (n % p == 0) {
			while (n % p == 0) n/=p;

			result = (result * (p - 1)) / p;
		}
	}

	return result;
}
