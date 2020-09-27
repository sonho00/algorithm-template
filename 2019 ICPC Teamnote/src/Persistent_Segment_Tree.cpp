#include<bits/stdc++.h>

using namespace std;

struct PST{
    vector<int> tree, left, right;
    vector<int> root;
    int height, t, base;
    //a=minimum # of node at leaf level
    //b=total # of updating operation
    //rn=maximum # of root
    PST(int a, int b, int rn){
        base=height=t=1;
        while(base<a) height++, base=base<<1;
        int tmp=base*2+2+height*b+5;
        tree.resize(tmp);
        left.resize(tmp);
        right.resize(tmp);
        root.resize(rn+2);
        root[0]=setup(1,base);
    }
    int setup(int ns, int nf){
        int k=t++;
        tree[k]=0;
        if(ns<nf){
            int mid=(ns+nf)>>1;
            left[k]=setup(ns,mid);
            right[k]=setup(mid+1,nf);
        }
        return k;
    }
    void update_Kth_tree(int k, int idx, int val){
        if(root[k]==0) root[k]=root[k-1];
        root[k]=make(root[k],idx,val);
    }
    int make(int bef, int idx, int val, int ns=1, int nf=-1){
        if(nf==-1) nf=base;
        if(idx<ns || nf<idx) return bef;
        int k=t++;
        if(ns==nf) tree[k]=tree[bef]+val;
        else{
            int mid=(ns+nf)>>1;
            left[k]=make(left[bef],idx,val,ns,mid);
            right[k]=make(right[bef],idx,val,mid+1,nf);
            tree[k]=tree[left[k]]+tree[right[k]];
        }
        return k;
    }
    //To get the value of Kth segtree -> get_sum(T.root[k],...)
    int get_sum(int num, int st, int fn, int ns=1, int nf=-1){
        if(nf==-1) nf=base;
        if(fn<ns || nf<st) return 0;
        if(st<=ns && nf<=fn) return tree[num];
        int mid=(ns+nf)>>1;
        return get_sum(left[num],st,fn,ns,mid)+get_sum(right[num],st,fn,mid+1,nf);
    }
};
