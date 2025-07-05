struct Dinic {
    int n, s, t, level[N], iter[N];
    struct edge {
        int to, cap, rev;
    };
    vector<edge> path[N];
    void init(int _n, int _s, int _t) {
        n = _n, s = _s, t = _t;
        FOR(i, 0, n + 1)
        path[i].clear();
    }
    void add(int a, int b, int c) {
        edge now;
        now.to = b, now.cap = c, now.rev = sz(path[b]);
        path[a].pb(now);
        now.to = a, now.cap = 0, now.rev = sz(path[a]) - 1;
        path[b].pb(now);
    }
    void bfs() {
        memset(level, -1, sizeof(level));
        level[s] = 0;
        queue<int> q;
        q.push(s);
        while (q.size()) {
            int now = q.front();
            q.pop();
            for (edge e : path[now]) {
                if (e.cap > 0 && level[e.to] == -1) {
                    level[e.to] = level[now] + 1;
                    q.push(e.to);
                }
            }
        }
    }
    int dfs(int now, int flow) {
        if (now == t) return flow;
        for (int &i = iter[now]; i < sz(path[now]); i++) {
            edge &e = path[now][i];
            if (e.cap > 0 && level[e.to] == level[now] + 1) {
                int res = dfs(e.to, min(flow, e.cap));
                if (res > 0) {
                    e.cap -= res;
                    path[e.to][e.rev].cap += res;
                    return res;
                }
            }
        }
        return 0;
    }
    int dinic() {
        int res = 0;
        while (true) {
            bfs();
            if (level[t] == -1) break;
            memset(iter, 0, sizeof(iter));
            int now = 0;
            while ((now = dfs(s, INF)) > 0) res += now;
        }
        return res;
    }
};
