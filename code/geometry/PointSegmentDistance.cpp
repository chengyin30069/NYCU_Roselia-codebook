double point_segment_dist(Pt q0, Pt q1, Pt p) {
    if (q0 == q1) {
        double dx = double(p.x - q0.x);
        double dy = double(p.y - q0.y);
        return sqrt(dx * dx + dy * dy);
    }
    T d1 = (q1 - q0) * (p - q0);
    T d2 = (q0 - q1) * (p - q1);
    if (d1 >= 0 && d2 >= 0) {
        double area = fabs(double((q1 - q0) ^ (p - q0)));
        double base = sqrt(double(dis2(q0, q1)));
        return area / base;
    }
    double dx0 = double(p.x - q0.x), dy0 = double(p.y - q0.y);
    double dx1 = double(p.x - q1.x), dy1 = double(p.y - q1.y);
    return min(sqrt(dx0 * dx0 + dy0 * dy0), sqrt(dx1 * dx1 + dy1 * dy1));
}
