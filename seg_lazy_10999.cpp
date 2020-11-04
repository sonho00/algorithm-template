#include<bits/stdc++.h>
#define FOR(i,a,b) for(ll i=a; i<=b; ++i)
#define ALL(x) x.begin(),x.end()
#define pb push_back
#define eb emplace_back
#define fi first
#define se second
#define endl '\n'
using namespace std;
using ll=long long;
using pll=pair<ll,ll>;
using vl=vector<ll>;
using vp=vector<pll>;
const ll INF=1e18;

struct node{
    ll lz,val;
    node():lz(0),val(0){}
    void updt(node& a,node& b){
        val=a.val+b.val;
    }
};
struct seg{
    vector<node> v;
    ll base;
    seg(ll n){
        base=1;
        while(base<=n) base<<=1;
        v.resize(base<<1);
    }
    void build(){
        for(ll i=base-1; i>=1; --i){
            v[i].updt(v[i<<1],v[i<<1|1]);
        }
    }
    void busy(ll vi,ll s,ll e){
        ll& lz=v[vi].lz;
        if(!lz) return;
        if(s!=e){
            v[vi<<1].lz+=lz;
            v[vi<<1|1].lz+=lz;
        }
        v[vi].val+=(e-s+1)*lz;
        lz=0;
    }
    void updt(ll l,ll r,ll val){updt(l,r,val,0,base-1,1);}
    void updt(ll l,ll r,ll val,ll s,ll e,ll vi){
        if(l<=s && e<=r){
            v[vi].lz+=val;
            busy(vi,s,e);
            return;
        }
        busy(vi,s,e);
        if(r<s || e<l) return;
        ll m=s+e>>1;
        updt(l,r,val,s,m,vi<<1);
        updt(l,r,val,m+1,e,vi<<1|1);
        v[vi].updt(v[vi<<1],v[vi<<1|1]);
    }
    ll query(ll l,ll r){return query(l,r,0,base-1,1);}
    ll query(ll l,ll r,ll s,ll e,ll vi){
        if(r<s || e<l) return 0;
        busy(vi,s,e);
        if(l<=s && e<=r) return v[vi].val;
        ll m=s+e>>1;
        ll lval=query(l,r,s,m,vi<<1);
        ll rval=query(l,r,m+1,e,vi<<1|1);
        return lval+rval;
    }
};

ll n;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll q,m,k,a,b,c,d;
    cin>>n>>m>>k;
    q=m+k;
    seg tree(n);
    FOR(i,1,n) cin>>tree.v[i+tree.base].val;
    tree.build();
    while(q--){
        cin>>a;
        if(a==1){
            cin>>b>>c>>d;
            tree.updt(b,c,d);
        }
        else{
            cin>>b>>c;
            cout<<tree.query(b,c)<<endl;
        }
    }
    return 0;
}