int a[N];
int st[N][30];
void pre(int n)
{
     FOR(i,1,n+1)st[i][0]=a[i];
     for(int j=1;(1<<j)<=n+1;j++)
          for(int i=0;i+(1<<j)<=n+1;i++)
               st[i][j]=min(st[i][j-1],st[i+(1<<(j-1))][j-1]);
}
int ask(int l,int r)
{
     int k=__lg(r-l+1);
     return min(st[l][k],st[r-(1<<k)+1][k]);
}
