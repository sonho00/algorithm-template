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

struct graph{
    ll n;
    vector<vector<pll>> adj;
    vector<ll> dist,par;
    graph(ll n):n(n),adj(vector<vector<pll>>(n+5)){}
    void dijk(ll idx){
        dist=vector<ll>(n+5,INF);
        dist[idx]=0;
        par=vector<ll>(n+5,0);
        priority_queue<pll> pq;
        pq.emplace(0,idx);
        ll d,top;
        while(!pq.empty()){
            tie(d,top)=pq.top();
            pq.pop();
            if(dist[top]!=-d) continue;
            for(pll& p:adj[top]){
                d=dist[top]+p.fi;
                if(dist[p.se]>d){
                    dist[p.se]=d;
                    par[p.se]=top;
                    pq.emplace(-d,p.se);
                }
            }
        }
    }
};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll n,m;
    cin>>n>>m;
    graph G(n);
    while(m--){
        ll a,b,c;
        cin>>a>>b>>c;
        G.adj[a].eb(c,b);
        G.adj[b].eb(c,a);
    }
    G.dijk(1);
    cout<<n-1<<'\n';
    FOR(i,2,n) cout<<i<<' '<<G.par[i]<<'\n';
    return 0;
}