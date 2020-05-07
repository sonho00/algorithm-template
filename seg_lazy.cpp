#include<bits/stdc++.h>
#define FOR(i,a,b) for(int i=a; i<=b; ++i)
#define pb push_back
#define eb emplace_back
#define fi first
#define se second
using namespace std;
using ll=long long;
using pll=pair<ll,ll>;
const ll INF=1e18;
const ll MAX=1e6;

struct node{
    ll lz,val;
    node():lz(0),val(0){}
    void updt(node& a,node& b){
        val=a.val+b.val;
    }
};
struct seg{
    ll base;
    vector<node> v;
    void make(ll n, ll* arr=NULL){
        base=1;
        while(base<n) base<<=1;
        v.resize(base<<1);
        if(arr==NULL) return;
        FOR(i,1,n) v[base+i-1].val=arr[i];
        for(ll i=base-1; i; --i){
            v[i].updt(v[i<<1],v[i<<1|1]);
        }
    }
    void lazy(ll vi,ll s,ll e){
        ll& lz=v[vi].lz;
        if(!lz) return;
        if(s!=e){
            v[vi<<1].lz+=lz;
            v[vi<<1|1].lz+=lz;
        }
        v[vi].val+=(e-s+1)*lz;
        lz=0;
    }
    void updt(ll l,ll r,ll val){updt(l,r,val,1,base,1);}
    void updt(ll l,ll r,ll val,ll s,ll e,ll vi){
        if(l<=s && e<=r){
            v[vi].lz+=val;
            lazy(vi,s,e);
            return;
        }
        lazy(vi,s,e);
        if(r<s || e<l) return;
        ll m=s+e>>1;
        updt(l,r,val,s,m,vi<<1);
        updt(l,r,val,m+1,e,vi<<1|1);
        v[vi].updt(v[vi<<1],v[vi<<1|1]);
    }
    ll query(ll l,ll r){return query(l,r,1,base,1);}
    ll query(ll l,ll r,ll s,ll e,ll vi){
        if(r<s || e<l) return 0;
        lazy(vi,s,e);
        if(l<=s && e<=r) return v[vi].val;
        ll m=s+e>>1;
        ll lval=query(l,r,s,m,vi<<1);
        ll rval=query(l,r,m+1,e,vi<<1|1);
        return lval+rval;
    }
};

ll n;
ll arr[MAX+5];
seg tree;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll q,m,k,a,b,c,d;
    cin>>n>>m>>k;
    q=m+k;
    FOR(i,1,n) cin>>arr[i];
    tree.make(n,arr);
    while(q--){
        cin>>a;
        if(a==1){
            cin>>b>>c>>d;
            tree.updt(b,c,d);
        }
        else{
            cin>>b>>c;
            cout<<tree.query(b,c)<<'\n';
        }
    }
    return 0;
}