struct Dinic {
    struct Edge { int to, cap, rev; };
    int n, s, t;
    vector<vector<Edge>> g;
    vector<int> level, it;

    void init(int _n, int _s, int _t){
        n=_n; s=_s; t=_t;
        g.assign(n, {});
        level.assign(n, 0);
        it.assign(n, 0);
    }
    void add(int a,int b,int c){
        Edge f{b,c,(int)g[b].size()};
        Edge r{a,0,(int)g[a].size()};
        g[a].push_back(f);
        g[b].push_back(r);
    }
    bool bfs(){
        fill(level.begin(), level.end(), -1);
        queue<int> q; level[s]=0; q.push(s);
        while(!q.empty()){
            int u=q.front(); q.pop();
            for(const auto &e: g[u]){
                if(e.cap>0 && level[e.to]==-1){
                    level[e.to]=level[u]+1;
                    q.push(e.to);
                }
            }
        }
        return level[t]!=-1;
    }
    int dfs(int u,int f){
        if(!f || u==t) return f;
        for(int &i=it[u]; i<(int)g[u].size(); ++i){
            auto &e=g[u][i];
            if(e.cap>0 && level[e.to]==level[u]+1){
                int got=dfs(e.to, min(f, e.cap));
                if(got){
                    e.cap-=got;
                    g[e.to][e.rev].cap+=got;
                    return got;
                }
            }
        }
        return 0;
    }
    int maxflow(){
        int flow=0, add;
        while(bfs()){
            fill(it.begin(), it.end(), 0);
            while((add=dfs(s, INF))) flow+=add;
        }
        return flow;
    }
};