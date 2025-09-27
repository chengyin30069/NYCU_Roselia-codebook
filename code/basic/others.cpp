#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#pragma GCC optimize("trapv")
mt19937 gen(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<int> dis(1, 100);
cout << dis(gen) << endl;
shuffle(v.begin(), v.end(), gen);

struct edge {
    int a, b, w;
    friend istream& operator>>(istream& in, edge& x) { in >> x.a >> x.b >> x.w; }
    friend ostream& operator<<(ostream& out, const edge& x) {
        out << "(" << x.a << "," << x.b << "," << x.w << ")";
        return out;
    }
};
struct cmp {
    bool operator()(const edge& x, const edge& y) const { return x.w < y.w; }
};
set<edge, cmp> st;                           // 遞增
map<edge, long long, cmp> mp;                // 遞增
priority_queue<edge, vector<edge>, cmp> pq;  // 遞減

#include <bits/extc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

// map
tree<int, int, less<>, rb_tree_tag, tree_order_statistics_node_update> tr;
tr.order_of_key(element);
tr.find_by_order(rank);

// set
tree<int, null_type, less<>, rb_tree_tag, tree_order_statistics_node_update> tr;
tr.order_of_key(element);
tr.find_by_order(rank);

// hash table
gp_hash_table<int, int> ht;
ht.find(element);
ht.insert({key, value});
ht.erase(element);

// priority queue
__gnu_pbds::priority_queue<int, less<int>> big_q;       // Big First
__gnu_pbds::priority_queue<int, greater<int>> small_q;  // Small First
q1.join(q2);  // join