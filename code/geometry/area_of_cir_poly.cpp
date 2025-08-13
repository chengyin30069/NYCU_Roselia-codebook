double AreaOfCirclePoly(Cir C, vector<Pt> &P) {
    auto arg = [&](Pt p, Pt q) { return atan2l(p ^ q, p * q); };
    double r2 = (double)(C.r * C.r / 2);
    auto tri = [&](Pt p, Pt q) {
        Pt d = q - p;
        T a = (d * p) / (d * d);
        T b = ((p * p) - C.r * C.r) / (d * d);
        T det = a * a - b;
        if (det <= 0) return (double)(arg(p, q) * r2);
        T s = max((T)0.0L, -a - sqrtl(det));
        T t = min((T)1.0L, -a + sqrtl(det));
        if (t < 0 || 1 <= s) return (double)(arg(p, q) * r2);
        Pt u = p + d * s, v = p + d * t;
        return (double)(arg(p, u) * r2 + (u ^ v) / 2 + arg(v, q) * r2);
    };
    long double sum = 0.0L;
    for (int i = 0; i < (int)P.size(); i++)
        sum += tri(P[i] - C.o, P[(i + 1) % P.size()] - C.o);
    return (double)fabsl(sum);
}