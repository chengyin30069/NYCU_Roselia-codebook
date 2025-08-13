long long mod_pow(long long a, long long e, long long p){
    long long r = 1 % p;
    while(e){
        if(e & 1) r = (__int128)r * a % p;
        a = (__int128)a * a % p;
        e >>= 1;
    }
    return r;
}
long long mod_inv(long long a, long long p){
    return mod_pow((a%p+p)%p, p-2, p);
}
// BSGS: solve a^x = y (mod p), gcd(a,p)=1, p prime, return minimal x>=0, or -1 if no solution
long long bsgs(long long a, long long y, long long p){
    a%=p; y%=p;
    if(y==1%p) return 0;          // x=0
    long long m = (long long)ceil(sqrt((long double)p));
    // baby steps: a^j
    unordered_map<long long,long long> table;
    table.reserve(m*2);
    long long cur = 1%p;
    for(long long j=0;j<m;++j){
        if(!table.count(cur)) table[cur]=j;
        cur = (__int128)cur * a % p;
    }
    long long am = mod_pow(a, m, p);
    long long am_inv = mod_inv(am, p);
    long long gamma = y % p;
    for(long long i=0;i<=m;++i){
        auto it = table.find(gamma);
        if(it != table.end()){
            long long x = i*m + it->second;
            return x;
        }
        gamma = (__int128)gamma * am_inv % p;
    }
    return -1;
}