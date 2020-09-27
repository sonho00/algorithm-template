#include<bits/stdc++.h>

using namespace std;
typedef pair<int,int> P;

struct Edge{
    int v, cost;
    Edge() {}
    Edge(int a, int b) : v(a), cost(b) {}
};

struct SegmentTree{
    vector<int> tree;
    int base;
    SegmentTree() {}
    void setup(int a){
        base=1;
        while(base<a) base<<=1;
        tree.resize(base*2+2);
        base--;
    }
    void update(int idx, int val){
        idx+=base;
        tree[idx]=val;
        idx=idx>>1;
        while(idx!=0){
            tree[idx]=max(tree[idx*2],tree[idx*2+1]);
            idx=idx>>1;
        }
    }
    int get_value(int num, int st, int fn, int ns=1, int nf=-1){
        if(nf==-1) nf=base+1;
        if(ns>fn || nf<st) return 0;
        if(st<=ns && nf<=fn) return tree[num];
        int mid=(ns+nf)>>1;
        return max(get_value(num*2,st,fn,ns,mid),get_value(num*2+1,st,fn,mid+1,nf));
    }
};

struct HeavyLightDecomposition{
    vector<vector<Edge> > lst;
    vector<int> par, sub, depth;
    vector<int> tail, dfsn, chain;
    vector<SegmentTree> HLDSegTree;
    int dn;
    HeavyLightDecomposition(int a){
        lst.resize(a+2);

        sub.resize(a+2);

        par.resize(a+2);
        depth.resize(a+2);
        dn=0;
        tail.resize(a+2);
        dfsn.resize(a+2);
        chain.resize(a+2);

        HLDSegTree.resize(a+2);
    }
    void add_edge(int v1, int v2, int cost){
        lst[v1].emplace_back(v2,cost);
        lst[v2].emplace_back(v1,cost);
    }
    void get_subsize(int cur, int prev);
    void HLD(int cur, int prev, int c_num);
    void construct_segtree(int a);
    void update_segtree(int v1, int v2, int cost);
    int get_max(int x, int y);
};
//get_subsize(1,0)
void HeavyLightDecomposition::get_subsize(int cur, int prev)
{
    sub[cur]=1;
    for(int i=0 ; i<lst[cur].size() ; i++){
        int nxt=lst[cur][i].v;
        if(nxt!=prev){
            HeavyLightDecomposition::get_subsize(nxt,cur);
            sub[cur]+=sub[nxt];
        }
    }
}
//chain number = initial vertex of dfsn
//tail = terminal vertex of dfsn
//dfsn is continuous in chain
//HLD(1,0,1)
void HeavyLightDecomposition::HLD(int cur, int prev, int c_num)
{
    dfsn[cur]=++dn;
    chain[dn]=c_num;
    tail[c_num]=dn;
    depth[dfsn[cur]]=depth[dfsn[prev]]+1;
    par[dfsn[cur]]=dfsn[prev];
    int idx=-1;
    for(int i=0 ; i<lst[cur].size() ; i++){
        int nxt=lst[cur][i].v;
        if(nxt!=prev && (idx==-1 || sub[nxt]>sub[idx])) idx=nxt;
    }
    if(idx!=-1) HeavyLightDecomposition::HLD(idx,cur,c_num);
    for(int i=0 ; i<lst[cur].size() ; i++){
        int nxt=lst[cur][i].v;
        if(nxt!=prev && nxt!=idx)
            HeavyLightDecomposition::HLD(nxt,cur,dn+1);
    }
}

void HeavyLightDecomposition::construct_segtree(int a)
{
    for(int i=1 ; i<=a ; i++){
        if(chain[dfsn[i]]==dfsn[i]) HLDSegTree[dfsn[i]].setup(tail[dfsn[i]]-dfsn[i]+1);
    }
    for(int i=1 ; i<=a ; i++){
        for(int j=0 ; j<lst[i].size() ; j++){
            int v1=i;
            int v2=lst[i][j].v;
            int cost=lst[i][j].cost;
            v1=dfsn[v1], v2=dfsn[v2];
            if(par[v2]!=v1) continue;
            int seg_num=chain[v2];
            if(chain[v1]!=chain[v2]) HLDSegTree[seg_num].update(1,cost);
            else HLDSegTree[seg_num].update(v2-chain[v2]+1,cost);
        }
    }
}

void HeavyLightDecomposition::update_segtree(int v1, int v2, int cost)
{
    v1=dfsn[v1], v2=dfsn[v2];
    if(depth[v1]>depth[v2]) swap(v1,v2);
    int seg_num=chain[v2];
    if(chain[v1]==chain[v2]) HLDSegTree[seg_num].update(v2-chain[v2]+1,cost);
    else HLDSegTree[seg_num].update(1,cost);
}

int HeavyLightDecomposition::get_max(int x, int y)
{
    int ret=0;
    x=dfsn[x];
    y=dfsn[y];
    while(chain[x]!=chain[y]){
        int x1=chain[x];
        int y1=chain[y];
        if(depth[x1]>depth[y1]){
            ret=max(ret,HLDSegTree[chain[x]].get_value(1,1,x-chain[x]+1));
            x=par[x1];
        }
        else{
            ret=max(ret,HLDSegTree[chain[y]].get_value(1,1,y-chain[y]+1));
            y=par[y1];
        }
    }
    if(depth[x]>depth[y]) swap(x,y);
    //x=LCA
    if(x!=y) ret=max(ret,HLDSegTree[chain[x]].get_value(1,x-chain[x]+2,y-chain[x]+1));
    return ret;
}

int main()
{
    int n, m;
    scanf("%d",&n);
    HeavyLightDecomposition T(n);
    vector<P> elist(n);
    for(int i=1 ; i<n ; i++){
        int v1, v2, cost;
        scanf("%d %d %d",&v1,&v2,&cost);
        elist[i]=P(v1,v2);
        T.add_edge(v1,v2,cost);
    }
    T.get_subsize(1,0);
    T.HLD(1,0,1);
    T.construct_segtree(n);
    scanf("%d",&m);
    for(int i=0 ; i<m ; i++){
        int t, x, y;
        scanf("%d %d %d",&t,&x,&y);
        if(t==1) T.update_segtree(elist[x].first,elist[x].second,y);
        else printf("%d\n",T.get_max(x,y));
    }
    return 0;
}
