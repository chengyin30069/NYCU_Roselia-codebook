double cross(const Pt &a, const Pt &b) {
    return a.x*b.y - a.y*b.x;
}
int rotatingCalipers(const vector<Pt>& hull) {
    int m = hull.size();
    if (m < 2) return 0;
    int j = 1;
    T maxd = 0;
    for (int i = 0; i < m; ++i) {
        int ni = (i + 1) % m;
        while (abs(cross({hull[ni].x - hull[i].x, hull[ni].y - hull[i].y}, {hull[(j+1)%m].x - hull[i].x, hull[(j+1)%m].y - hull[i].y})) > abs(cross({hull[ni].x - hull[i].x, hull[ni].y - hull[i].y}, {hull[j].x - hull[i].x,   hull[j].y - hull[i].y}))) {
            j = (j + 1) % m;
        }
        maxd = max(maxd, dis2(hull[i], hull[j]));
        maxd = max(maxd, dis2(hull[ni], hull[j]));
    }
    return maxd; // TODO
}