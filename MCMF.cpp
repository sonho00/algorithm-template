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
    vector<ll> lv;
    bool bfs(){
        lv=vector<ll>(n+5,0);
        lv[n+1]=1;
        ll q[MAX+5];
        ll s=0,e=0;
        while(s<e){
            ll top=q[s++];
            FOR(i,1,n+2){
                if(!lv[i] && flow[top][i]<cap[top][i]){
                    lv[i]=lv[top]+1;
                    q[e++]=i;
                }
            }
        }
        return lv[n+2];
    }
    ll operator()(){
        ll ret=0,f;
        while(bfs()){
            while(f=dfs()) ret+=f;
        }
        return ret;
    }
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