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

template<typename T>
struct seg{
    vector<T> v;
    ll base;
    seg(ll n){
        base=1;
        while(base<=n) base<<=1;
        v.resize(base<<1);
    }
    void build(){
        for(ll i=base-1; i; --i){
            v[i]=v[i<<1]+v[i<<1|1];
        }
    }
    void updt(ll idx,T val){
        for(v[idx+=base]=val; idx>=2; idx>>=1){
            v[idx>>1]=v[idx]+v[idx^1];
        }
    }
    T query(ll l,ll r){
        T ret=0;
        for(l+=base,r+=base+1; l<r; l>>=1,r>>=1){
            if(l&1) ret+=v[l++];
            if(r&1) ret+=v[--r];
        }
        return ret;
    }
};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll n,m,k;
    cin>>n>>m>>k;
    seg<ll> tree(n);
    FOR(i,1,n) cin>>tree.v[i+tree.base];
    tree.build();
    for(ll q=m+k; q--;){
        ll a,b,c;
        cin>>a>>b>>c;
        if(a==1) tree.updt(b,c);
        else cout<<tree.query(b,c)<<endl;
    }
    return 0;
}