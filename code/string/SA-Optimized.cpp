#define F first
#define S second
struct SuffixArray {  // don't forget s += "$";
    int n;
    string s;
    vector<int> suf, lcp, rk;
    // 後綴陣列：suf[i] = 第 i 小的後綴起點
    // LCP 陣列：lcp[i] = suf[i] 與 suf[i-1] 的最長共同前綴長度
    // rank 陣列：rk[i] = 起點在 i 的後綴的名次
    vector<int> cnt, pos;
    vector<pair<pair<int, int>, int> > buc[2];
    void init(string _s) {
        s = _s;
        n = (int)s.size();
        // resize(n): suf, rk, cnt, pos, lcp, buc[0~1]
        suf.assign(n, 0);
        rk.assign(n, 0);
        lcp.assign(n, 0);
        cnt.assign(n, 0);
        pos.assign(n, 0);
        buc[0].assign(n, {{0,0},0});
        buc[1].assign(n, {{0,0},0});
    }
    void radix_sort() {
        for (int t : {0, 1}) {
            fill(cnt.begin(), cnt.end(), 0);
            for (auto& i : buc[t]) cnt[(t ? i.F.F : i.F.S)]++;
            for (int i = 0; i < n; i++)
                pos[i] = (!i ? 0 : pos[i - 1] + cnt[i - 1]);
            for (auto& i : buc[t])
                buc[t ^ 1][pos[(t ? i.F.F : i.F.S)]++] = i;
        }
    }
    bool fill_suf() {
        bool end = true;
        for (int i = 0; i < n; i++) suf[i] = buc[0][i].S;
        rk[suf[0]] = 0;
        for (int i = 1; i < n; i++) {
            int dif = (buc[0][i].F != buc[0][i - 1].F);
            end &= dif;
            rk[suf[i]] = rk[suf[i - 1]] + dif;
        }
        return end;
    }
    void sa() {
        for (int i = 0; i < n; i++)
            buc[0][i] = make_pair(make_pair(s[i], s[i]), i);
        sort(buc[0].begin(), buc[0].end());
        if (fill_suf()) return;
        for (int k = 0; (1 << k) < n; k++) {
            for (int i = 0; i < n; i++)
                buc[0][i] = make_pair(make_pair(rk[i], rk[(i + (1 << k)) % n]), i);
            radix_sort();
            if (fill_suf()) return;
        }
    }
    void LCP() {
        int k = 0;
        for (int i = 0; i < n - 1; i++) {
            if (rk[i] == 0) continue;
            int pi = rk[i];
            int j = suf[pi - 1];
            while (i + k < n && j + k < n && s[i + k] == s[j + k]) k++;
            lcp[pi] = k;
            k = max(k - 1, 0);
        }
    }
};
SuffixArray suffixarray;
