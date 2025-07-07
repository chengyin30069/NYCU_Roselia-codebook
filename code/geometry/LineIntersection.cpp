bool line_intersect_check(Pt p1, Pt p2, Pt q1, Pt q2) {
    if (onseg(p1, q1, q2) || onseg(p2, q1, q2) || onseg(q1, p1, p2) || onseg(q2, p1, p2)) return true;
    Pt p = mv(p1, p2), q = mv(q1, q2);
    return (ori(p, mv(p1, q1)) * ori(p, mv(p1, q2)) < 0) && (ori(q, mv(q1, p1)) * ori(q, mv(q1, p2)) < 0);
}
// long double
Pt line_intersect(Pt a1, Pt a2, Pt b1, Pt b2) {
    Pt da = mv(a1, a2), db = mv(b1, b2);
    T det = da ^ db;
    if (sgn(det) == 0) { // parallel
        // return Pt(NAN, NAN);
    }
    T t = ((b1 - a1) ^ db) / det;
    return a1 + da * t;
}