struct edge 
{ 
    int a, b, w;
    friend istream& operator>>(istream &in, edge &x)
    {    in >> x.a >> x.b >> x.w;    }
    friend ostream& operator<<(ostream &out, const edge &x)
    {    out << "(" << x.a << "," << x.b << "," << x.w << ")"; return out;    }
};

struct cmp 
{    bool operator()(const edge &x, const edge &y) const { return x.w < y.w; }    };

set<edge, cmp> st; //遞增
map<edge, long long, cmp> mp; //遞增
priority_queue<edge, vector<edge>, cmp> pq; // 遞減