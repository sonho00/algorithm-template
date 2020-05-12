#include<bits/stdc++.h>
#define FOR(i,a,b) for(ll i=a; i<=b; ++i)
#define ALL(x) x.begin(),x.end()
#define pb push_back
#define eb emplace_back
#define fi first
#define se second
using namespace std;
using ll=long long;
using pll=pair<ll,ll>;
const ll INF=1e18;
const ll MAX=1e5;
const ll MOD=1e9+7;
const ll LOG=20;

struct node{
    ll li,ri,val;
    node():li(0),ri(0),val(0){}
    node(ll li,ll ri,ll val):li(li),ri(ri),val(val){}
};
struct PST{
    ll base;
    vector<ll> root;
    vector<node> v;
    PST(ll n,ll* arr=NULL):base(base){
        base=1;
        while(base<n) base<<=1;
        v.resize(base<<1);
        root.pb(1);
        if(arr!=NULL) FOR(i,1,n) v[i+base-1].val=arr[i];
        for(ll i=base-1; i; --i) v[i]=node(i<<1,i<<1|1,v[i<<1].val+v[i<<1|1].val);
    }
    void updt(ll idx,ll val){
        ll rt=v.size();
        updt(idx,val,1,base,root.back(),rt);
        root.pb(rt);
    }
    void updt(ll idx,ll val,ll s,ll e,ll rt,ll vi){
        if(idx<s || e<idx) return;
        v.pb(v[rt]);
        if(s==e){
            v[vi].val=val;
            return;
        }
        ll m=s+e>>1;
        if(idx<=m) v[vi].li=v.size();
        else v[vi].ri=v.size();
        updt(idx,val,s,m,v[rt].li,v[vi].li);
        updt(idx,val,m+1,e,v[rt].ri,v[vi].ri);
        v[vi].val=v[v[vi].li].val+v[v[vi].ri].val;
    }
    ll query(ll l,ll r,ll rt){return query(l,r,1,base,root[rt]);}
    ll query(ll l,ll r,ll s,ll e,ll vi){
        if(r<s || e<l) return 0;
        if(l<=s && e<=r) return v[vi].val;
        ll m=s+e>>1;
        ll lval=query(l,r,s,m,v[vi].li);
        ll rval=query(l,r,m+1,e,v[vi].ri);
        return lval+rval;
    }
};

ll n,m;
ll a[MAX+5];

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    FOR(i,1,n) cin>>a[i];
    PST tree(n,a);
    cin>>m;
    while(m--){
        ll a,b,c,d;
        cin>>a;
        if(a==1){
            cin>>b>>c;
            tree.updt(b,c);
        }
        else{
            cin>>b>>c>>d;
            cout<<tree.query(c,d,b)<<'\n';
        }
    }
    return 0;
}