// 2 * area
T dbPoly_area(vector<Pt>& e) {
    T res = 0;
    int sz = e.size();
    for (int i = 0; i < sz; i++) {
        res += e[i] ^ e[(i + 1) % sz];
    }
    return abs(res);
}
