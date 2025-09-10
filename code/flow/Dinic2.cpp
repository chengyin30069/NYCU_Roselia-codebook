using namespace std;
using namespace __gnu_pbds;
template<class T>using deset=tree<T,null_type,greater<T>,rb_tree_tag,tree_order_statistics_node_update>;
template<class T>using inset=tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
template<class T,class TT>using um=unordered_map<T,TT>;
template<class T,class TT>using fm=gp_hash_table<T,TT>;
typedef trie<string,null_type,trie_string_access_traits<string>,pat_trie_tag,trie_prefix_search_node_update> tr;
template<class T>using pbds_pq=__gnu_pbds::priority_queue<T,greater<T>,pairing_heap_tag>;
template<class T>using std_pq=std::priority_queue<T,vector<T>,greater<T>>;
const int Mod1=1000000007,Mod2=998244353,N=2000+5;
int n,m,s,t,level[N],iter[N];
struct edge
{
     int to,cap,rev;
};
vector<edge>path[N];
void add(int a,int b,int c)
{
     path[a].pb({b,c,sz(path[b])});
     path[b].pb({a,0,sz(path[a])-1});
}
void bfs()
{
     memset(level,-1,sizeof(level));
     level[s]=0;
     queue<int>q;q.push(s);
     while(q.size())
     {
          int now=q.front();q.pop();
          for(edge e:path[now])
          {
               if(e.cap>0&&level[e.to]==-1)
               {
                    level[e.to]=level[now]+1;
                    q.push(e.to);
               }
          }
     }
}
int dfs(int now,int flow)
{
     if(now==t)return flow;
     for(int &i=iter[now];i<sz(path[now]);i++)
     {
          edge &e=path[now][i];
          if(e.cap>0&&level[e.to]==level[now]+1)
          {
               int res=dfs(e.to,min(flow,e.cap));
               if(res>0)
               {
                    e.cap-=res;
                    path[e.to][e.rev].cap+=res;
                    return res;
               }
          }
     }
     return 0;
}
int dinic()
{
     int res=0;
     while(true)
     {
          bfs();
          if(level[t]==-1)break;
          memset(iter,0,sizeof(iter));
          int now=0;
          while((now=dfs(s,INF))>0)res+=now;
     }
     return res;
}
