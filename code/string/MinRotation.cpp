// rotate(begin(s), begin(s)+minRotation(s), end(s))
// 找出字串的最小字典序旋轉
int minRotation(string s) {
    int a = 0, n = s.size();
    s += s;
    for (int b = 0; b < n; b++)
        for (int k = 0; k < n; k++) {
            if (a + k == b || s[a + k] < s[b + k]) {
                b += max(0, k - 1);
                break;
            }
            if (s[a + k] > s[b + k]) {
                a = b;
                break;
            }
        }
    return a;
}
