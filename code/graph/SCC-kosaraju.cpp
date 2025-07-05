const int N = 1e5 + 10;
vector<int> ed[N], ed_b[N];  // 反邊
vector<int> SCC(N);          // 最後SCC的分組
bitset<N> vis;
int SCC_cnt;
int n, m;
vector<int> pre;  // 後序遍歷

void dfs(int x) {
    vis[x] = 1;
    for (int i : ed[x]) {
        if (vis[i]) continue;
        dfs(i);
    }
    pre.push_back(x);
}

void dfs2(int x) {
    vis[x] = 1;
    SCC[x] = SCC_cnt;
    for (int i : ed_b[x]) {
        if (vis[i]) continue;
        dfs2(i);
    }
}

void kosaraju() {
    for (int i = 1; i <= n; i++) {
        if (!vis[i]) {
            dfs(i);
        }
    }
    SCC_cnt = 0;
    vis = 0;
    for (int i = n - 1; i >= 0; i--) {
        if (!vis[pre[i]]) {
            SCC_cnt++;
            dfs2(pre[i]);
        }
    }
}