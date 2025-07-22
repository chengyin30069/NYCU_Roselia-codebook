const int N = 2e3;
int match[N];
bool vis[N];
int n;
vector<int> ed[N];
int match_cnt;
bool dfs(int u) {
    vis[u] = 1;
    for(int i : ed[u]) {
        if(match[i] == 0 || !vis[match[i]] && dfs(match[i])) {
            match[i] = u;
            return true;
        }
    }
    return false;
}
void hungary() {
    memset(match, 0, sizeof(match));
    match_cnt = 0;
    for(int i = 1; i <= n; i++) {
        memset(vis, 0, sizeof(vis));
        if(dfs(i)) match_cnt++;
    }
}
