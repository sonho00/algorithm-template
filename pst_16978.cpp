#include<bits/stdc++.h>
using namespace std;
using ll=long long;

struct node{
    ll li,ri,val;
    node(ll li=0,ll ri=0,ll val=0):li(li),ri(ri),val(val){}
};

struct PST{
    ll base;
    vector<ll> root;
    vector<node> v;
    PST(ll n):base(1<<64-__builtin_clzll(n)),root(1,1),v(base<<1){
        for(ll i=base; --i;){
            v[i].li=i<<1;
            v[i].ri=i<<1|1;
        }
    }
    void updt(ll idx,ll val){
        ll rt=v.size();
        updt(idx,val,1,base,root.back(),rt);
        root.push_back(rt);
    }
    void updt(ll idx,ll val,ll s,ll e,ll prv,ll cur){
        v.push_back(v[prv]);
        if(s==e){
            v[cur].val=val;
            return;
        }
        ll m=s+e>>1;
        if(idx<=m){
            v[cur].li=v.size();
            updt(idx,val,s,m,v[prv].li,v[cur].li);
        }
        else{
            v[cur].ri=v.size();
            updt(idx,val,m+1,e,v[prv].ri,v[cur].ri);
        }
        v[cur].val=v[v[cur].li].val+v[v[cur].ri].val;
    }
    ll qry(ll l,ll r,ll rt){return qry(l,r,1,base,rt);}
    ll qry(ll l,ll r,ll s,ll e,ll vi){
        if(r<s || e<l) return 0;
        if(l<=s && e<=r) return v[vi].val;
        ll m=s+e>>1;
        ll lv=qry(l,r,s,m,v[vi].li);
        ll rv=qry(l,r,m+1,e,v[vi].ri);
        return lv+rv;
    }
};

ll n;
ll a[101010];

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    PST pst(n);
    for(ll i=1; i<=n; ++i){
        cin>>a[i];
        pst.v[i+pst.base-1].val=a[i];
    }
    for(ll i=pst.base; --i;){
        pst.v[i].val=pst.v[i<<1].val+pst.v[i<<1|1].val;
    }
    ll m;
    cin>>m;
    while(m--){
        ll a,b,c,d;
        cin>>a>>b>>c;
        if(a==1) pst.updt(b,c);
        else{
            cin>>d;
            cout<<pst.qry(c,d,pst.root[b])<<'\n';
        }
    }
}