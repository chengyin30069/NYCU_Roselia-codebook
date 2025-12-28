struct MCMF {
    int n, s, t; // 0-based, s and t in [0,n-1]
    vector<int> par, p_i, dis, vis;
    struct edge {
        int to, cap, rev, cost;
    };
    vector<vector<edge>> path;
    MCMF(int _n) : n(_n), par(_n), p_i(_n), dis(_n), vis(_n), path(_n, vector<edge>(0)) {}
    void add(int a, int b, int c, int d) {
        path[a].pb({b, c, sz(path[b]), d});
        path[b].pb({a, 0, sz(path[a]) - 1, -d});
    }
    void spfa() {
        FOR(i, 0, n) dis[i] = INF, vis[i] = 0;
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
    pii flow(int _s, int _t) {
        s = _s;
        t = _t;
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
                edge& now = path[par[i]][p_i[i]];
                now.cap -= mn;
                path[i][now.rev].cap += mn;
            }
        }
        return mp(flow, cost);
    }
};
