mt19937 rng(random_device{}());
struct Treap
{
	Treap *l,*r;
	int val,num,pri;
	Treap(int k)
	{
		l=r=NULL;
		val=k;
		num=1;
		pri=rng();
	}
};
int siz(Treap *now){return now?now->num:0;}
void pull(Treap *&now)
{
	now->num=siz(now->l)+siz(now->r)+1;
}
Treap* merge(Treap *a,Treap *b)
{
	if(!a||!b)return a?a:b;
	else if(a->pri>b->pri)
	{
		a->r=merge(a->r,b);
		pull(a);
		return a;
	}
	else 
	{
		b->l=merge(a,b->l);
		pull(b);
		return b;
	}
}
void split_size(Treap *rt,Treap *&a,Treap *&b,int val)
{
	if(!rt)
	{
		a=b=NULL;
		return;
	}
	if(siz(rt->l)+1>val)
	{
		b=rt;
		split_size(rt->l,a,b->l,val);
		pull(b);
	}
	else 
	{
		a=rt;
		split_size(rt->r,a->r,b,val-siz(a->l)-1);
		pull(a);
	}
}
void split_val(Treap *rt,Treap *&a,Treap *&b,int val)
{
	if(!rt)
	{
		a=b=NULL;
		return;
	}
	if(rt->val<=val)
	{
		a=rt;
		split_val(rt->r,a->r,b,val);
		pull(a);
	}
	else
	{
		b=rt;
		split_val(rt->l,a,b->l,val);
		pull(b);
	}
}
void treap_dfs(Treap *now)
{
	if(!now)return;
	treap_dfs(now->l);
	cout<<now->val<<" ";
	treap_dfs(now->r);
}
