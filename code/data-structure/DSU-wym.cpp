struct DSU {
    int h[N], s[N];

    void init(int n) { iota(h, h + n + 1, 0), fill(s, s + n + 1, 1); }

    int fh(int x) { return (h[x] == x ? x : h[x] = fh(h[x])); }

    bool mer(int x, int y) {
        x = fh(x), y = fh(y);
        if (x == y) return 0;
        if (s[x] < s[y]) swap(x, y);
        s[x] += s[y], s[y] = 0;
        h[y] = x;
        return 1;
    }
} bm;
