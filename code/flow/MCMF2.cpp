struct MCMF {
    int n, s, t, par[N + 5], p_i[N + 5], dis[N + 5], vis[N + 5];
    struct edge {
        int to, cap, rev, cost;
    };
    vector<edge> path[N];
    void init(int _n, int _s, int _t) {
        n = _n, s = _s, t = _t;
        FOR(i, 0, 2 * n + 5)
        par[i] = p_i[i] = vis[i] = 0;
    }
    void add(int a, int b, int c, int d) {
        path[a].pb({b, c, sz(path[b]), d});
        path[b].pb({a, 0, sz(path[a]) - 1, -d});
    }
    void spfa() {
        FOR(i, 0, n * 2 + 5)
        dis[i] = INF,
        vis[i] = 0;
        dis[s] = 0;
        queue<int> q;
        q.push(s);
        while (!q.empty()) {
            int now = q.front();
            q.pop();
            vis[now] = 0;
            for (int i = 0; i < sz(path[now]); i++) {
                edge e = path[now][i];
                if (e.cap > 0 && dis[e.to] > dis[now] + e.cost) {
                    dis[e.to] = dis[now] + e.cost;
                    par[e.to] = now;
                    p_i[e.to] = i;
                    if (vis[e.to] == 0) {
                        vis[e.to] = 1;
                        q.push(e.to);
                    }
                }
            }
        }
    }
    pii flow() {
        int flow = 0, cost = 0;
        while (true) {
            spfa();
            if (dis[t] == INF)
                break;
            int mn = INF;
            for (int i = t; i != s; i = par[i])
                mn = min(mn, path[par[i]][p_i[i]].cap);
            flow += mn;
            cost += dis[t] * mn;
            for (int i = t; i != s; i = par[i]) {
                edge &now = path[par[i]][p_i[i]];
                now.cap -= mn;
                path[i][now.rev].cap += mn;
            }
        }
        return mp(flow, cost);
    }
};
