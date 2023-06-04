vpii pfact(ll num) { // O(sqrt(n))
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