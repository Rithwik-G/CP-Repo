// modified global array 'sieve' which stores smallest prime divisor

void linsieve(int n) { // O(n)

	bool iscomposite[n];
	vi prime;
	FOR(i, 2, n) {
		if (!sieve[i]) {
			prime.push_back (i);
			sieve[i]=i;
		}
		for (int j = 0; j < prime.size () && i * prime[j] < n; ++j) {
			sieve[i * prime[j]] = prime[j];
			if (i % prime[j] == 0) break;
		}
	}
}

vpii pfact(ll num) { // O(log(num))
	vpii ans;
	if (num == 1) return {};
	int prev_div = -1;
	while (num != 1) {
		if (sieve[num] != prev_div) ans.pb({sieve[num], 0});
		ans[ans.size() - 1].s ++;
		prev_div = sieve[num];
		num/=sieve[num];
	}
	return ans;

	// returns vector of factors
}


// Find all factors of a number using a Sieve - FAST

void factorize(ll cur_ind, vpii &factors, int cur_num) {
	if (cur_ind == factors.size()) {
		// DO STUFF
		return;
	}

	factorize(cur_ind + 1, factors, cur_num);

	FOR(i, 0, factors[cur_ind].s) {
		cur_num *= factors[cur_ind].f;
		factorize(cur_ind + 1, factors, cur_num);
	}
}

void factors(ll num) { // uses sieve to find all factors of a number in O(log n)
	vpii prime_factors = pfact2(num);
	factorize(0, prime_factors, 1);
}




// WITHOUT SIEVE!

vpii findFactors(ll num) { // Find all factors of a number in O(sqrt(n)) in 
	vpii ans;
	if (num == 1) return {};
	for (ll i = 2; i * i <= num; i++) { // all small primes
		
		if (num % i == 0) {
			ll cnt = 0;
			while (num % i == 0) {
				num/=i;
				cnt++;
			}

			ans.pb({i, cnt});
		}
	}

	if (num != 1) ans.pb({num, 1}); // prime greater than sqrt(n)

	return ans;
}