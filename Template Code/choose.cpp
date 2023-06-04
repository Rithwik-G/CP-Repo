// Calculates nCk % MOD in O(1) time with O(MAX_N) preprocessing
// Assumes MOD is prime

// Needs Global Arrays fact[] and invfact[] as well as MOD

ll fact[N];
ll invfact[N];

ll binpow(ll x, ll n) { // binary exponentiation
	x %= MOD;
	ll cur = 1;
	while (n > 0) {
		if (n % 2==1) {cur = cur * x % MOD;}
 
		x = x * x % MOD;
		n /= 2;
	}
	return cur;
}

void calcChoose(ll n) { // preprocessing
	fact[0]=1;
	invfact[0]=1;
	for (ll i = 1; i < n; i++) fact[i] = (fact[i-1]*i) % MOD;
	for (ll i = 1; i < n; i++) invfact[i] = binpow(fact[i], MOD - 2) % MOD;
}

ll choose(ll n, ll k) { // calculate choose in O(1)
	return (fact[n] * ((invfact[k] * invfact[n - k]) % MOD)) % MOD;
}