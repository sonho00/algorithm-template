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
const ll MAX=400;
const ll MOD=1e9+7;
const ll LOG=20;

ll n,m;
vector<pll> adj[MAX+5];

struct MCMF{
    
};
MCMF mcmf;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m;
    FOR(i,1,n){
        ll cnt;
        cin>>cnt;
        while(cnt--){
            ll a,b;
            cin>>a>>b;
            adj[n].eb(b,a);
        }
    }

    return 0;
}