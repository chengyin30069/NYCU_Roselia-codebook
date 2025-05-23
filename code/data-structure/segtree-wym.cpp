struct segtree
{
    int n, seg[1<<19];
 
    void init(int x)
    {
        n = 1<<(__lg(x) + 1);
        for(int i=1; i<2*n; i++)
            seg[i] = inf;
    }
 
    void update(int x, int val)
    {
        x += n;
        seg[x] = val, x /= 2;
        while(x)
            seg[x] = min(seg[2*x], seg[2*x+1]), x /= 2;
    }
 
    int query(int l, int r)
    {
        l += n, r += n;
        int ret = inf;
        while(l < r)
        {
            if(l & 1)
                ret = min(ret, seg[l++]);
            if(r & 1)
                ret = min(ret, seg[--r]);
            l /= 2, r /= 2;
        }
        return ret;
    }
}bm;
