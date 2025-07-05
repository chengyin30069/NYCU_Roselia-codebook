ll add(ll x, ll y, ll p) {
    return (x + y) % p;
}
ll qMul(ll x, ll y, ll mod) {
    ll ret = x * y - (ll)((long double)x / mod * y) * mod;
    return ret < 0 ? ret + mod : ret;
}
ll f(ll x, ll mod) { return add(qMul(x, x, mod), 1, mod); }
ll pollard_rho(ll n) {
    if (!(n & 1)) return 2;
    while (true) {
        ll y = 2, x = rand() % (n - 1) + 1, res = 1;
        for (int sz = 2; res == 1; sz *= 2) {
            for (int i = 0; i < sz && res <= 1; i++) {
                x = f(x, n);
                res = __gcd(llabs(x - y), n);
            }
            y = x;
        }
        if (res != 0 && res != n) return res;
    }
}
vector<ll> ret;
void fact(ll x) {
    if (miller_rabin(x)) {
        ret.push_back(x);
        return;
    }
    ll f = pollard_rho(x);
    fact(f);
    fact(x / f);
}
