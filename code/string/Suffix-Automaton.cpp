struct SAM {
    struct State {
        int next[26];
        int link, len;
        State() : link(-1), len(0) { memset(next, -1, sizeof next); }
    };
    vector<State> st;
    int last;
    vector<long long> occ;
    vector<int> first_bkpos;
    SAM(int maxlen = 0) {
        st.reserve(2 * maxlen + 5); st.push_back(State()); last = 0;
        occ.reserve(2 * maxlen + 5); occ.push_back(0);
        first_bkpos.push_back(-1);
    }
    void extend(int c) {
        int cur = (int)st.size();
        st.push_back(State());
        occ.push_back(0);
        first_bkpos.push_back(0);
        st[cur].len = st[last].len + 1;
        first_bkpos[cur] = st[cur].len - 1;
        int p = last;
        while (p != -1 && st[p].next[c] == -1) {
            st[p].next[c] = cur;
            p = st[p].link;
        }
        if (p == -1) {
            st[cur].link = 0;
        } else {
            int q = st[p].next[c];
            if (st[p].len + 1 == st[q].len) {
                st[cur].link = q;
            } else {
                int clone = (int)st.size();
                st.push_back(st[q]);
                first_bkpos.push_back(first_bkpos[q]);
                occ.push_back(0);
                st[clone].len = st[p].len + 1;
                while (p != -1 && st[p].next[c] == q) {
                    st[p].next[c] = clone;
                    p = st[p].link;
                }
                st[q].link = st[cur].link = clone;
            }
        }
        last = cur;
        occ[cur] += 1;
    }
    void finalize_occ() {
        int m = (int)st.size();
        vector<int> order(m);
        iota(order.begin(), order.end(), 0);
        sort(order.begin(), order.end(), [&](int a, int b){ return st[a].len > st[b].len; });
        for (int v : order) {
            int p = st[v].link;
            if (p != -1) occ[p] += occ[v];
        }
    }
};