long long Min_Euclidean_Dist(vector<Pt> &pts) {
    sort(pts.begin(), pts.end());
    set<pair<long long, long long>> s;
    s.insert({pts[0].y, pts[0].x});
    long long l = 0, best = LLONG_MAX;
    for (int i = 1; i < (int)pts.size(); i++) {
        Pt now = pts[i];
        long long lim = (long long)ceil(sqrtl((long double)best));
        while (now.x - pts[l].x > lim) {
            s.erase({pts[l].y, pts[l].x}); l++;
}
        auto low = s.lower_bound({now.y - lim, LLONG_MIN});
        auto high = s.upper_bound({now.y + lim, LLONG_MAX});
        for (auto it = low; it != high; it++) {
            long long dy = it->first - now.y;
            long long dx = it->second - now.x;
            best = min(best, dx * dx + dy * dy);
        }
        s.insert({now.y, now.x});
    }
    return best;
}