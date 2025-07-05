vector<int> f;
void buildFailFunction(string &s) {
    f.resize(s.size(), -1);
    for (int i = 1; i < s.size(); i++) {
        int now = f[i - 1];
        while (now != -1 and s[now + 1] != s[i]) now = f[now];
        if (s[now + 1] == s[i]) f[i] = now + 1;
    }
}

void KMPmatching(string &a, string &b) {
    for (int i = 0, now = -1; i < a.size(); i++) {
        while (a[i] != b[now + 1] and now != -1) now = f[now];
        if (a[i] == b[now + 1]) now++;
        if (now + 1 == b.size()) {
            cout << "found a match start at position " << i - now << endl;
            now = f[now];
        }
    }
}
