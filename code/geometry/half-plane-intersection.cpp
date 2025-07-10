bool cover(Line& L, Line& P, Line& Q) {
    long double u = (Q.a - P.a) ^ Q.dir();
    long double v = P.dir() ^ Q.dir();
    long double x = P.dir().x * u + (P.a - L.a).x * v;
    long double y = P.dir().y * u + (P.a - L.a).y * v;
    return sgn(x * L.dir().y - y * L.dir().x) * sgn(v) >= 0;
}
vector<Line> HPI(vector<Line> P) {
    sort(P.begin(), P.end(), [&](Line& l, Line& m) {
        if (argcmp(l.dir(), m.dir())) return true;
        if (argcmp(m.dir(), l.dir())) return false;
        return ori(m.a, m.b, l.a) > 0;
    });

    int l = 0, r = -1;
    for (size_t i = 0; i < P.size(); ++i) {
        if (i && !argcmp(P[i - 1].dir(), P[i].dir())) continue;
        while (l < r && cover(P[i], P[r - 1], P[r])) --r;
        while (l < r && cover(P[i], P[l], P[l + 1])) ++l;
        P[++r] = P[i];
    }
    while (l < r && cover(P[l], P[r - 1], P[r])) --r;
    while (l < r && cover(P[r], P[l], P[l + 1])) ++l;

    if (r - l <= 1 || !argcmp(P[l].dir(), P[r].dir())) return {};
    if (cover(P[l + 1], P[l], P[r])) return {};

    return vector<Line>(P.begin() + l, P.begin() + r + 1);
}