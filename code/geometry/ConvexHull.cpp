vector<Pt> convexHull(vector<Pt> pts) {
    vector<Pt> hull;
    sort(pts.begin(), pts.end());
    for (int i = 0; i < 2; i++) {
        int b = hull.size();
        for (auto ei : pts) {
            while (hull.size() - b >= 2 && ori(mv(hull[hull.size() - 2], hull.back()), mv(hull[hull.size() - 2], ei)) == -1) {
                hull.pop_back();
            }
            hull.emplace_back(ei);
        }
        hull.pop_back();
        reverse(pts.begin(), pts.end());
    }
    return hull;
}
