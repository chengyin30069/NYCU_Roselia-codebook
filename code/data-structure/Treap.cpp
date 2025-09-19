mt19937 rng(random_device{}());
struct Treap {
    Treap *l, *r;
    int val, sum, real, tag, num, pri, rev;
    Treap(int k) {
        l = r = NULL;
        val = sum = k;
        num = 1;
        real = -1;
        tag = 0;
        rev = 0;
        pri = rng();
    }
};
int siz(Treap *now) { return now ? now->num : 0ll; }
int sum(Treap *now) {
    if (!now) return 0;
    if (now->real != -1) return (now->real + now->tag) * now->num;
    return now->sum + now->tag * now->num;
}
void pull(Treap *&now) {
    now->num = siz(now->l) + siz(now->r) + 1ll;
    now->sum = sum(now->l) + sum(now->r) + now->val + now->tag;
}
void push(Treap *&now) {
    if (now->rev) {
        swap(now->l, now->r);
        now->l->rev ^= 1;
        now->r->rev ^= 1;
        now->rev = 0;
    }
    if (now->real != -1) {
        now->real += now->tag;
        if (now->l) {
            now->l->tag = 0;
            now->l->real = now->real;
            now->l->val = now->real;
        }
        if (now->r) {
            now->r->tag = 0;
            now->r->real = now->real;
            now->r->val = now->real;
        }
        now->val = now->real;
        now->sum = now->real * now->num;
        now->real = -1;
        now->tag = 0;
    } else {
        if (now->l) now->l->tag += now->tag;
        if (now->r) now->r->tag += now->tag;
        now->sum += sum(now);
        now->val += now->tag;
        now->tag = 0;
    }
}
Treap *merge(Treap *a, Treap *b) {
    if (!a || !b) return a ? a : b;
    else if (a->pri > b->pri) {
        push(a);
        a->r = merge(a->r, b);
        pull(a);
        return a;
    } else {
        push(b);
        b->l = merge(a, b->l);
        pull(b);
        return b;
    }
}
void split_size(Treap *rt, Treap *&a, Treap *&b, int val) {
    if (!rt) {
        a = b = NULL;
        return;
    }
    push(rt);
    if (siz(rt->l) + 1 > val) {
        b = rt;
        split_size(rt->l, a, b->l, val);
        pull(b);
    } else {
        a = rt;
        split_size(rt->r, a->r, b, val - siz(a->l) - 1);
        pull(a);
    }
}
void split_val(Treap *rt, Treap *&a, Treap *&b, int val) {
    if (!rt) {
        a = b = NULL;
        return;
    }
    push(rt);
    if (rt->val <= val) {
        a = rt;
        split_val(rt->r, a->r, b, val);
        pull(a);
    } else {
        b = rt;
        split_val(rt->l, a, b->l, val);
        pull(b);
    }
}