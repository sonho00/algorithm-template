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

vector<ll> ext_euc(ll a,ll b){
    vector<ll> ret={1,0,a};
    vector<ll> tmp={0,1,b};
    while(tmp[2]){
        ll q=ret[2]/tmp[2];
        ret={ret[0]-q*tmp[0],ret[1]-q*tmp[1],ret[2]-q*tmp[2]};
        swap(ret,tmp);
    }
    return ret;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll n,a;
    cin>>n>>a;
    auto tmp=ext_euc(n,a);
    cout<<n-a<<' ';
    if(tmp[2]!=1) cout<<-1;
    else{
        for(ll& x:tmp) x=(n+x%n)%n;
        cout<<tmp[1];
    }
    return 0;
}