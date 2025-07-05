#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 5;
vector<int> a[N];
int sz[N], lv[N];
bool used[N];
int f_sz(int x, int p) {
    sz[x] = 1;
    for (int i : a[x])
        if (i != p && !used[i])
            sz[x] += f_sz(i, x);
    return sz[x];
}
int f_cen(int x, int p, int total) {
    for (int i : a[x]) {
        if (i != p && !used[i] && 2 * sz[i] > total)
            return f_cen(i, x, total);
    }
    return x;
}
void cd(int x, int p) {
    int total = f_sz(x, p);
    int cen = f_cen(x, p, total);
    lv[cen] = lv[p] + 1;
    used[cen] = 1;
    // cout << "cd: " << x << " " << p << " " << cen << "\n";
    for (int i : a[cen]) {
        if (!used[i])
            cd(i, cen);
    }
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    for (int i = 0, x, y; i < n - 1; i++) {
        cin >> x >> y;
        a[x].push_back(y);
        a[y].push_back(x);
    }
    cd(1, 0);
    for (int i = 1; i <= n; i++)
        cout << (char)('A' + lv[i] - 1) << " ";
    cout << "\n";
}