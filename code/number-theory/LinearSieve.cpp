const int C = 1e7 + 2;
int mo[C], lp[C], phi[C], isp[C];
vector<int> prime;
void sieve() {
    mo[1] = phi[1] = 1;
    for(int i = 1; i < C; i++) lp[i] = 1;
    for(int i = 2; i < C; i++) {
        if(lp[i] == 1) {
            lp[i] = i;
            prime.push_back(i);
            isp[i] = 1;
            mo[i] = -1;
            phi[i] = i - 1;
        }
        for(int p : prime) {
            if(i * p >= C) break;
            lp[i * p] = p;
            if(i % p == 0) {
                phi[p * i] = phi[i] * p;
                break;
            }
            phi[i * p] = phi[i] * (p - 1);
            mo[i * p] = mo[i] * mo[p];
        }
    }
}
