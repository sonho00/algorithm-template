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
struct cor{
    vector<T> v;
    void build(){
        sort(ALL(v));
        v.erase(unique(ALL(v)),v.end());
    }
    ll operator[](T val){return lower_bound(ALL(v),val)-v.begin();}
};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll n;
    cor<ll> xc;
    cin>>n;
    vl x(n+5);
    FOR(i,1,n){
        cin>>x[i];
        xc.v.pb(x[i]);
    }
    xc.build();
    FOR(i,1,n) cout<<xc[x[i]]<<' ';
    return 0;
}