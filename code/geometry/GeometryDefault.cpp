// typedef long long T;
typedef long double T;
const long double eps = 1e-8;

short sgn(T x) {
    if (abs(x) < eps) return 0;
    return x < 0 ? -1 : 1;
}

struct Pt {
    T x, y;
    Pt(T _x = 0, T _y = 0) : x(_x), y(_y) {}
    Pt operator+(Pt a) { return Pt(x + a.x, y + a.y); }
    Pt operator-(Pt a) { return Pt(x - a.x, y - a.y); }
    Pt operator*(T a) { return Pt(x * a, y * a); }
    Pt operator/(T a) { return Pt(x / a, y / a); }
    T operator*(Pt a) { return x * a.x + y * a.y; }
    T operator^(Pt a) { return x * a.y - y * a.x; }
    bool operator<(Pt a) { return x < a.x || (x == a.x && y < a.y); }
    // return sgn(x-a.x) < 0 || (sgn(x-a.x) == 0 && sgn(y-a.y) < 0); }
    bool operator==(Pt a) { return sgn(x - a.x) == 0 && sgn(y - a.y) == 0; }
};

Pt mv(Pt a, Pt b) { return b - a; }
T len2(Pt a) { return a * a; }
T dis2(Pt a, Pt b) { return len2(b - a); }

short ori(Pt a, Pt b) { return ((a ^ b) > 0) - ((a ^ b) < 0); }
bool onseg(Pt p, Pt l1, Pt l2) {
    Pt a = mv(p, l1), b = mv(p, l2);
    return ((a ^ b) == 0) && ((a * b) <= 0);
}

inline int cross(const Pt &a, const Pt &b, const Pt &c) {
    return (b.x - a.x) * (c.y - a.y)
         - (b.y - a.y) * (c.x - a.x);
}

double polar_angle(Pt ori, Pt pt){
    return atan2(pt.y - ori.y, pt.x - ori.x);
}

bool argcmp(Pt u, Pt v) {
    auto half = [](const Pt& p) {
        return p.y > 0 || (p.y == 0 && p.x >= 0);
    };
    if (half(u) != half(v)) return half(u) < half(v);
    return sgn(u ^ v) > 0;
}
struct Line {
    Pt a, b;
    Line() {}
    Line(Pt _a, Pt _b) : a(_a), b(_b) {}
    Pt dir() { return b - a; }
};
int ori(Pt& o, Pt& a, Pt& b) {
    return sgn((a - o) ^ (b - o));
}
