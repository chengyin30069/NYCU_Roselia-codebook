bool point_in_convex(const vector<Pt> &C, Pt p, bool strict = true) {
    // only works when no three point are collinear
    int n = C.size();
    int a = 1, b = n - 1, r = !strict;
    if (n == 0) return false;
    if (n < 3) return r && onseg(p, C[0], C.back());
    if (ori(mv(C[0], C[a]), mv(C[0], C[b])) > 0) swap(a, b);
    if (ori(mv(C[0], C[a]), mv(C[0], p)) >= r || ori(mv(C[0], C[b]), mv(C[0], p)) <= -r) return false;
    while (abs(a - b) > 1) {
        int c = (a + b) / 2;
        if (ori(mv(C[0], C[c]), mv(C[0], p)) > 0) b = c;
        else a = c;
    }
    return ori(mv(C[a], C[b]), mv(C[a], p)) < r;
}
