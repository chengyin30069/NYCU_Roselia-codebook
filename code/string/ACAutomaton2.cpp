struct ACautomata {
    struct Node {
        int cnt; // 停在此節點的數量
        Node *go[26], *fail, *dic;
        // 子節點 fail指標 最近的模式結尾
        Node() {
            cnt = 0;
            fail = 0;
            dic = 0;
            memset(go, 0, sizeof(go));
        }
    } pool[1048576], *root;
    int nMem;
    Node *new_Node() {
        pool[nMem] = Node();
        return &pool[nMem++];
    }
    void init() {
        nMem = 0;
        root = new_Node();
    }
    void add(const string &str) { insert(root, str, 0); }
    void insert(Node *cur, const string &str, int pos) {
        for (int i = pos; i < str.size(); i++) {
            if (!cur->go[str[i] - 'a'])
                cur->go[str[i] - 'a'] = new_Node();
            cur = cur->go[str[i] - 'a'];
        }
        cur->cnt++;
    }
    void make_fail() { // 全部 add 完做
        queue<Node *> que;
        que.push(root);
        while (!que.empty()) {
            Node *fr = que.front();
            que.pop();
            for (int i = 0; i < 26; i++) {
                if (fr->go[i]) {
                    Node *ptr = fr->fail;
                    while (ptr && !ptr->go[i]) ptr = ptr->fail;
                    fr->go[i]->fail = ptr = (ptr ? ptr->go[i] : root);
                    fr->go[i]->dic = (ptr->cnt ? ptr : ptr->dic);
                    que.push(fr->go[i]);
                }
            }
        }
    }
    // 出現過不同string的總數
    int query_unique(const string& text) {
        Node* p = root;
        int ans = 0;
        for(char ch : text) {
            int i = ch - 'a';
            while(p && !p->go[i]) p = p ->fail;
            p = p ? p->go[i] : root;
            if(p->cnt) {ans += p->cnt, p->cnt = 0;}
            for(Node* t = p->dic; t; t = t->dic) if(t->cnt) {
                ans += t->cnt; t->cnt = 0;
            }
        }
        return ans;
    }
} AC;