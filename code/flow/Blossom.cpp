const int N=5e2+10;
struct Graph{
	int to[N],bro[N],head[N],e;
	int lnk[N],vis[N],stp,n;
	void init(int _n){
		stp=0;e=1;n=_n;
		FOR(i,0,n+1)head[i]=lnk[i]=vis[i]=0;
	}
	void add(int u,int v){
		to[e]=v,bro[e]=head[u],head[u]=e++;
		to[e]=u,bro[e]=head[v],head[v]=e++;
	}
	bool dfs(int x){
		vis[x]=stp;
		for(int i=head[x];i;i=bro[i])
		{
			int v=to[i];
			if(!lnk[v])
			{
				lnk[x]=v;lnk[v]=x;
				return true;
			}
			else if(vis[lnk[v]]<stp)
			{
				int w=lnk[v];
				lnk[x]=v,lnk[v]=x,lnk[w]=0;
				if(dfs(w))return true;
				lnk[w]=v,lnk[v]=w,lnk[x]=0;
			}
		}
		return false;
	}
	int solve(){
		int ans=0;
		FOR(i,1,n+1){
			if(!lnk[i]){
				stp++;
				ans+=dfs(i);
			}
		}
		return ans;
	}
	void print_matching(){
		FOR(i,1,n+1)
			if(i<graph.lnk[i])
				cout<<i<<" "<<graph.lnk[i]<<endl;
	}
};