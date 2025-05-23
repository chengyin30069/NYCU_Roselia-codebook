struct BIT
{
    int n;
    long long bit[N];

    void init(int x, vector<long long> &a)
    {
        n = x;
        for(int i=1, j; i<=n; i++)
        {
            bit[i] += a[i-1], j = i + (i & -i);
            if(j <= n)	bit[j] += bit[i];
        }
    }
 
    void update(int x, long long dif)
    {
        while(x <= n)    bit[x] += dif, x += x & -x;
    }
 
    long long query(int l, int r)
    {
        if(l != 1)	return query(1, r) - query(1, l-1);

        long long ret = 0;
        while(l <= r)	ret += bit[r], r -= r & -r;
        return ret;
    }
}bm;