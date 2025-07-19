void reorder(vector <Pt> &P) {
  rotate(P.begin(), min_element(P.begin(), P.end(), [&](Pt a, Pt b) { return make_pair(a.y, a.x) < make_pair(b.y, b.x); }), P.end());
}
vector <Pt> Minkowski(vector <Pt> P, vector <Pt> Q) {
  // P, Q: convex polygon
  reorder(P), reorder(Q);
  int n = P.size(), m = Q.size();
  P.push_back(P[0]), P.push_back(P[1]), Q.push_back(Q[0]), Q.push_back(Q[1]);
  vector <Pt> ans;
  for (int i = 0, j = 0; i < n || j < m; ) {
    ans.push_back(P[i] + Q[j]);
    auto val = (P[i + 1] - P[i]) ^ (Q[j + 1] - Q[j]);
    if (val >= 0) i++;
    if (val <= 0) j++;
  }
  return ans;
}
