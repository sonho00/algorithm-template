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
const ll MAX=1e6;
const ll MOD=1e9+7;
const ll LOG=20;

struct node{
    ll val;
    node(ll val=0):val(val){}
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
        FOR(i,1,n) v[base+i-1]=arr[i];
        for(ll i=base-1; i; --i){
            v[i].updt(v[i<<1],v[i<<1|1]);
        }
    }
    void updt(ll idx,ll val){
        idx+=base-1;
        v[idx].val=val;
        while(idx){
            idx>>=1;
            v[idx].updt(v[idx<<1],v[idx<<1|1]);
        }
    }
    ll query(ll l,ll r){return query(l,r,1,base,1);}
    ll query(ll l,ll r,ll s,ll e,ll vi){
        if(l<=s && e<=r) return v[vi].val;
        if(r<s || e<l) return 0;
        ll m=s+e>>1;
        ll lval=query(l,r,s,m,vi<<1);
        ll rval=query(l,r,m+1,e,vi<<1|1);
        return lval+rval;
    }
};

ll n,m,k,q;
ll arr[MAX+5];
seg tree;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m>>k;
    q=m+k;
    FOR(i,1,n) cin>>arr[i];
    tree.make(n,arr);
    while(q--){
        ll a,b,c;
        cin>>a>>b>>c;
        if(a==1) tree.updt(b,c);
        else cout<<tree.query(b,c)<<'\n';
    }
    return 0;
}