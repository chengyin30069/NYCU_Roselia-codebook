string is, it, s;
// is: 被搜尋 it: 要找的
int n;
vector<int> z;
// 計算每個位置 i 開始的字串，和 s 的共農前綴長度
void init() {
    cin >> is >> it;
    s = it + '0' + is;
    n = (int)s.size();
    z.resize(n, 0);
}
void solve() {
    int ans = 0;
    z[0] = n;
    for (int i = 1, l = 0, r = 0; i < n; i++) {
        if (i <= r) z[i] = min(z[i - l], r - i + 1);
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
        if (i + z[i] - 1 > r) l = i, r = i + z[i] - 1;
        if (z[i] == (int)it.size()) ans++;
    }
    cout << ans << endl;
}