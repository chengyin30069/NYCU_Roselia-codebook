struct segtree
{
    struct node
    {
        long long sum, pre;
        node()
        {
            sum = pre = 0;
        }
    };
 
    node mer(node x, node y)
    {
        node ret;
        ret.sum = x.sum + y.sum;
        ret.pre = max(x.pre, x.sum + y.pre);
        return ret;
    }
 
    int n;
    node seg[1<<19];
 
    void init(int x)
    {
        n = 1<<(__lg(x) + 1);
    }
 
    void print()
    {
        for(int i=1, j=1; i<=__lg(n)+1; i++)
        {
            for(; j<(1<<i); j++)
                cout << seg[j].sum << " ";
            cout << "\n";
        }
        cout << "\n";
    }
 
    void update(int x, long long val)
    {
        x += n;
        seg[x].sum = val, seg[x].pre = max(0LL, val);
        x /= 2;
        while(x)
            seg[x] = mer(seg[2*x], seg[2*x+1]), x /= 2;
    }
 
    long long query(int l, int r)
    {
        l += n, r += n;
        node retl, retr;
        while(l < r)
        {
            if(l & 1)
                retl = mer(retl, seg[l++]);
            if(r & 1)
                retr = mer(seg[--r], retr);
            l /= 2, r /= 2;
        }
        return mer(retl, retr).pre;
    }
}bm;
