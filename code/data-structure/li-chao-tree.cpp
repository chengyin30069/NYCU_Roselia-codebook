const int eps=1e-9;
struct line
{
     double m,k;
}p[N];
int seg[N<<2],cnt;
double cal(int id,int x){return 1.0*p[id].m*x+p[id].k;}
void add(int x0,int y0,int x1,int y1)
{
     cnt++;
     if(x0==x1)p[cnt].m=0,p[cnt].k=max(y0,y1);
     else p[cnt].m=1.0*(y1-y0)/(x1-x0),p[cnt].k=y0-p[cnt].m*x0;
}
void update(int x,int l,int r,int ql,int qr,int u)
{
     int v=seg[x],mid=(l+r)>>1;
     double resu=cal(u,mid),resv=cal(v,mid);
     if(qr<l||r<ql)return;
     if(ql<=l&&r<=qr)
     {
          if(l==r)
          {
               if(resu>resv)seg[x]=u;
               return;
          }
          if(p[u].m-p[v].m>eps)
          {
               if(resu-resv>eps)
               {
                    seg[x]=u;
                    update(x<<1,l,mid,ql,qr,v);
               }
               else update(x<<1|1,mid+1,r,ql,qr,u);
          }
          else if(p[v].m-p[u].m>eps)
          {
               if(resu-resv>eps)
               {
                    seg[x]=u;
                    update(x<<1|1,mid+1,r,ql,qr,v);
               }
               else update(x<<1,l,mid,ql,qr,u);
          }
          else if(p[u].k-p[v].k>eps)seg[x]=u;
          return;
     }
     update(x<<1,l,mid,ql,qr,u);
     update(x<<1|1,mid+1,r,ql,qr,u);
}
double ask(int x,int l,int r,int qx)
{
     if(r<qx||qx<l)return{0,0};
     int mid=(l+r)>>1;
     double res=cal(seg[x],qx);
     if(l==r)return res;
     return max({res,seg[x],ask(x<<1,l,mid,qx),ask(x<<1|1,mid+1,r,qx)});
}
