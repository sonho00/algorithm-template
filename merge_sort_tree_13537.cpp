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

struct MST{
    ll base;
    vector<vector<ll>> v;
    MST(ll n,ll* arr=NULL){
        base=1;
        while(base<n) base<<=1;
        v.resize(base<<1);
        if(arr==NULL) return;
        FOR(i,1,n) v[i+base-1].pb(arr[i]);
        for(ll i=base-1; i; --i){
            auto& lv=v[i<<1],rv=v[i<<1|1];
            ll lsz=lv.size(),rsz=rv.size();
            ll li=0,ri=0;
            while(li<lsz && ri<rsz){
                if(lv[li]<rv[ri]) v[i].pb(lv[li++]);
                else v[i].pb(rv[ri++]);
            }
            while(li<lsz) v[i].pb(lv[li++]);
            while(ri<rsz) v[i].pb(rv[ri++]);
        }
    }
    ll query(ll l,ll r,ll k){return query(l,r,k,1,base,1);}
    ll query(ll l,ll r,ll k,ll s,ll e,ll vi){
        if(r<s || e<l) return 0;
        if(l<=s && e<=r) return v[vi].end()-upper_bound(ALL(v[vi]),k);
        ll m=s+e>>1;
        ll lval=query(l,r,k,s,m,vi<<1);
        ll rval=query(l,r,k,m+1,e,vi<<1|1);
        return lval+rval;
    }
};

ll n;
ll a[MAX+5];

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    FOR(i,1,n) cin>>a[i];
    MST mst(n,a);
    ll m;
    cin>>m;
    while(m--){
        ll i,j,k;
        cin>>i>>j>>k;
        cout<<mst.query(i,j,k)<<'\n';
    }
    return 0;
}