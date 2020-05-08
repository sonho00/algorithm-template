#include<bits/stdc++.h>
#define FOR(i,a,b) for(int i=a; i<=b; ++i)
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

struct cor{
    vector<ll> v;
    void make(){
        sort(ALL(v));
        v.erase(unique(ALL(v)),v.end());
    }
    ll operator[](ll val){return lower_bound(ALL(v),val)-v.begin();}
};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll n;
    ll x[MAX+5];
    cor xc;
    cin>>n;
    FOR(i,1,n){
        cin>>x[i];
        xc.v.pb(x[i]);
    }
    xc.make();
    FOR(i,1,n) cout<<xc[x[i]]<<' ';
    return 0;
}