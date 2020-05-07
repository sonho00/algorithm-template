#include<bits/stdc++.h>
#define FOR(i,a,b) for(int i=a; i<=b; ++i)
#define pb push_back
#define eb emplace_back
#define fi first
#define se second
using namespace std;
using ll=long long;
using pll=pair<ll,ll>;
const ll INF=1e18;
const ll MAX=1e3;

int n;
vector<pll> adj[MAX+5];
ll dist[MAX+5];
// int par[MAX+5];

void dijk(ll idx){
    FOR(i,1,n) dist[i]=INF;
    dist[idx]=0;
    bool visit[MAX+5]={};
    priority_queue<pll> pq;
    pq.emplace(0,idx);
    while(!pq.empty()){
        ll v=pq.top().se;
        pq.pop();
        if(visit[v]) continue;
        visit[v]=1;
        for(pll& p:adj[v]){
            if(visit[p.se]) continue;
            if(dist[p.se]>dist[v]+p.fi){
                // par[p.se]=v;
                dist[p.se]=dist[v]+p.fi;
                pq.emplace(-dist[p.se],p.se);
            }
        }
    }
}

int main(){
    ll m,a,b,c;
    cin>>n>>m;
    while(m--){
        cin>>a>>b>>c;
        adj[a].eb(c,b);
        adj[b].eb(c,a);
    }
    dijk(1);
    cout<<n-1<<endl;
    FOR(i,2,n) cout<<i<<' '<<par[i]<<endl;
    return 0;
}