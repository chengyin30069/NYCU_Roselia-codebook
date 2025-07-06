short inPoly(vector<Pt>& pts, Pt p) {
    // 0=Bound 1=In -1=Out
    int n = pts.size();
    for (int i = 0; i < pts.size(); i++) if (onseg(p, pts[i], pts[(i + 1) % n])) return 0;
    int cnt = 0;
    for (int i = 0; i < pts.size(); i++) if (line_intersect_check(p, Pt(p.x + 1, p.y + 2e9), pts[i], pts[(i + 1) % n])) cnt ^= 1;
    return (cnt ? 1 : -1);
}
