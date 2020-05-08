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
const ll MAX=200;
const ll MOD=1e9+7;
const ll LOG=20;

ll n,m;
ll cost[MAX+5][MAX+5];
ll cap[MAX+5][MAX+5];

struct MCMF{
    ll n;
    ll flow[MAX+5][MAX+5]={};
    vector<ll> lv;
    void make(ll ver){n=ver;}
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
    mcmf.make(n+m);
    FOR(i,1,n) cin>>cap[n+m+1][i];
    FOR(i,1,m) cin>>cap[n+i][n+m+2];
    FOR(i,1,n) FOR(j,n,2*n) cin>>cost[i][j];
    return 0;
}