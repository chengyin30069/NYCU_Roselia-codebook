struct PushRelabel {// 0-based, s and t in [0,n-1]
    struct Edge {
        int dest, back;
        int f, c;
    };
    vector<vector<Edge>> g;
    vector<int> ec;
    vector<Edge*> cur;
    vector<vector<int>> hs;
    vector<int> H;
    PushRelabel(int n) : g(n), ec(n), cur(n), hs(2 * n), H(n) {}
    void add(int s, int t, int cap, int rcap = 0) {
        if (s == t) return;
        g[s].pb({t, sz(g[t]), 0, cap});
        g[t].pb({s, sz(g[s]) - 1, 0, rcap});
    }
    void AddFlow(Edge& e, int f) {
        Edge& back = g[e.dest][e.back];
        if (!ec[e.dest] && f) hs[H[e.dest]].pb(e.dest);
        e.f += f;
        e.c -= f;
        ec[e.dest] += f;
        back.f -= f;
        back.c += f;
        ec[back.dest] -= f;
    }
    int flow(int s, int t) {
        int v = sz(g);
        H[s] = v;
        ec[t] = 1;
        vector<int> co(2 * v);
        co[0] = v - 1;
        FOR(i, 0, v) cur[i] = g[i].data();
        for (Edge& e : g[s]) AddFlow(e, e.c);
        for (int hi = 0;;) {
            while (hs[hi].empty())
                if (!hi--) return -ec[s];
            int u = hs[hi].back();
            hs[hi].pop_back();
            while (ec[u] > 0) {
                if (cur[u] == g[u].data() + sz(g[u])) {
                    H[u] = INF;
                    for (Edge& e : g[u])
                        if (e.c && H[u] > H[e.dest] + 1) {
                            H[u] = H[e.dest] + 1;
                            cur[u] = &e;
                        }
                    if (++co[H[u]], !--co[hi] && hi < v) {
                        FOR(i, 0, v) if (hi < H[i] && H[i] < v) {
                            --co[H[i]];
                            H[i] = v + 1;
                        }
                    }
                    hi = H[u];
                } else if (cur[u]->c && H[u] == H[cur[u]->dest] + 1)
                    AddFlow(*cur[u], min(ec[u], cur[u]->c));
                else
                    ++cur[u];
            }
        }
    }
    bool leftOfMinCut(int a) { return H[a] >= sz(g); }
};
