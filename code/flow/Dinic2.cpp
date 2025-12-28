using namespace std;
struct Dinic {
    int n, s, t;  // 0-base, s and t included in [0,n-1]
    vector<int> level, iter;
    struct edge {
        int to, cap, rev;
    };
    vector<vector<edge>> path;
    Dinic(int _n) : n(_n), level(_n), iter(_n), path(_n, vector<edge>(0)) {}
    void add(int a, int b, int c) {
        path[a].pb({b, c, sz(path[b])});
        path[b].pb({a, 0, sz(path[a]) - 1});
    }
    void bfs() {
        FOR(i, 0, n) level[i] = -1;
        level[s] = 0;
        queue<int> q;
        q.push(s);
        while (q.size()) {
            int now = q.front();
            q.pop();
            for (edge e : path[now])
                if (e.cap > 0 && level[e.to] == -1) {
                    level[e.to] = level[now] + 1;
                    q.push(e.to);
                }
        }
    }
    int dfs(int now, int flow) {
        if (now == t) return flow;
        for (int& i = iter[now]; i < sz(path[now]); i++) {
            edge& e = path[now][i];
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
    int dinic(int _s, int _t) {
        s = _s, t = _t;
        int res = 0;
        while (true) {
            bfs();
            if (level[t] == -1) break;
            FOR(i, 0, n) iter[i] = 0;
            int now = 0;
            while ((now = dfs(s, INF)) > 0) res += now;
        }
        return res;
    }
};
