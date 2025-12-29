struct HopcroftKarp {
    int n, nx, ny;  // X: [1, nx], Y: [nx+1, nx+ny]
    vector<vector<int> > g;
    vector<int> mx, my, dis, vis, min_cov;
    void init(int nnx, int nny) {
        nx = nnx, ny = nny;
        n = nx + ny + 1;
        g.resize(n, vector<int>(0));
        mx.resize(n, -1);
        my.resize(n, -1);
        dis.resize(n, -1);
        vis.resize(n, 0);
    }
    void add(int x, int y) {
        g[x].emplace_back(y);
        g[y].emplace_back(x);
    }
    bool dfs(int x) {
        vis[x] = true;
        for (auto y : g[x]) {
            int px = my[y];
            if (px == -1 ||
                (dis[px] == dis[x] + 1 &&
                 !vis[px] && dfs(px))) {
                mx[x] = y;
                my[y] = x;
                return true;
            }
        }
        return false;
    }
    int get() {
        int res = 0;
        while (true) {
            queue<int> q;
            fill(dis.begin(), dis.end(), -1);
            for (int x = 1; x <= nx; x++) {
                if (mx[x] == -1) {
                    dis[x] = 0;
                    q.push(x);
                }
            }
            while (!q.empty()) {
                int x = q.front();
                q.pop();
                for (auto y : g[x]) {
                    if (my[y] != -1 &&
                        dis[my[y]] == -1) {
                        dis[my[y]] = dis[x] + 1;
                        q.push(my[y]);
                    }
                }
            }
            bool brk = true;
            fill(vis.begin(), vis.end(), 0);
            for (int x = 1; x <= nx; x++)
                if (mx[x] == -1 && dfs(x))
                    brk = false;
            if (brk) break;
        }
        for (int x = 1; x <= nx; x++)
            if (mx[x] != -1) res++;
        return res;
    }
    void get_min_cov() {
        vector<int> visX(n, 0), visY(n, 0);
        queue<int> q;
        min_cov.resize(n, 0);
        for (int x = 1; x < nx + 1; x++)
            if (mx[x] == -1) {
                visX[x] = 1;
                q.push(x);
            }
        while (!q.empty()) {
            int x = q.front();
            q.pop();
            for (auto y : g[x])
                if (!visY[y]) {
                    visY[y] = 1;
                    if (my[y] != -1 && !visX[my[y]]) {
                        visX[my[y]] = 1;
                        q.push(my[y]);
                    }
                }
        }
        for (int x = 1; x < nx + 1; x++)
            if (!visX[x]) min_cov[x] = 1;
        for (int y = nx + 1; y < n; y++)
            if (visY[y]) min_cov[y] = 1;
    }
} hk;