struct KM
{
	int n,mx[1005],my[1005],pa[1005];
	int g[1005][1005],lx[1005],ly[1005],sy[1005];
	bool vx[1005],vy[1005];
	void init(int _n)
	{
		n=_n;
		FOR(i,1,n+1)fill(g[i],g[i]+1+n,0);
	}
	void add(int a,int b,int c){g[a][b]=c;}
	void augment(int y)
	{
		for(int x,z;y;y=z)
			x=pa[y],z=mx[x],my[y]=x,mx[x]=y;
	}
	void bfs(int st)
	{
		FOR(i,1,n+1)sy[i]=INF,vx[i]=vy[i]=0;
		queue<int>q;q.push(st);
		for(;;)
		{
			while(!q.empty())
			{
				int x=q.front();q.pop();
				vx[x]=1;
				FOR(y,1,n+1)if(!vy[y])
				{
					int t=lx[x]+ly[y]-g[x][y];
					if(t==0)
					{
						pa[y]=x;
						if(!my[y]){augment(y);return;}
						vy[y]=1, q.push(my[y]);
					}
					else if(sy[y]>t)pa[y]=x,sy[y]=t;
				}
			}
			int cut=INF;
			FOR(y,1,n+1)if(!vy[y]&&cut>sy[y])cut=sy[y];
			FOR(j,1,n+1)
			{
				if(vx[j])lx[j]-=cut;
				if(vy[j])ly[j]+=cut;
				else sy[j]-=cut;
			}
			FOR(y,1,n+1)
			{
				if(!vy[y]&&sy[y]==0)
				{
					if(!my[y]){augment(y);return;}
					vy[y]=1;q.push(my[y]);
				}
			}
		}
	}
	int solve()
	{
		fill(mx,mx+n+1,0);fill(my,my+n+1,0);
		fill(ly,ly+n+1,0);fill(lx,lx+n+1,0);
		FOR(x,1,n+1)FOR(y,1,n+1)
			lx[x]=max(lx[x],g[x][y]);
		FOR(x,1,n+1)bfs(x);
		int ans=0;
		FOR(y,1,n+1)ans+=g[my[y]][y];
		return ans;
	}
};
