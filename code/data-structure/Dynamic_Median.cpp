struct Dynamic_Median {
    multiset<long long> lo, hi;
    long long slo = 0, shi = 0;
    void rebalance() {
        // keep sz(lo) >= sz(hi) and sz(lo) - sz(hi) <= 1
        while((int)lo.size() > (int)hi.size() + 1) {
            auto it = prev(lo.end());
            long long x = *it;
            lo.erase(it); slo -= x;
            hi.insert(x); shi += x;
        }
        while((int)lo.size() < (int)hi.size()) {
            auto it = hi.begin();
            long long x = *it;
            hi.erase(it); shi -= x;
            lo.insert(x); slo += x;    
        }
    }
    void add(long long x) {
        if(lo.empty() || x <= *prev(lo.end())) {
            lo.insert(x); slo += x;
        }
        else {
            hi.insert(x); shi += x;
        }
        rebalance();
    }
    void remove_one(long long x) {
        if(!lo.empty() && x <= *prev(lo.end())) {
            auto it = lo.find(x);
            if(it != lo.end()) {
                lo.erase(it); slo -= x;
            }
            else {
                auto it2 = hi.find(x);
                hi.erase(it2); shi -= x;
            }
        }
        else {
            auto it = hi.find(x);
            if(it != hi.end()) {
                hi.erase(it); shi -= x;
            }
            else {
                auto it2 = lo.find(x);
                lo.erase(it2); slo -= x;
            }
        }
        rebalance();
    }
};
