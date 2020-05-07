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

bool spfa(int idx){
    FOR(i,1,n) dist[i]=INF;
    dist[idx]=0;
    int cnt[MAX+5]={};
    bool inq[MAX+5]={};
    queue<int> q;
    q.push(idx);
    inq[idx]=1;
    while(!q.empty()){
        int top=q.front();
        q.pop();
        if(++cnt[top]>=n) return 0;
        inq[top]=0;
        for(pll& p:adj[top]){
            ll d=dist[top]+p.fi;
            if(dist[p.se]>d){
                dist[p.se]=d;
                // par[p.se]=top;
                if(!inq[p.se]){
                    inq[p.se]=1;
                    q.push(p.se);
                }
            }
        }
    }
    return 1;
}

int main(){
    ll m,a,b,c;
    cin>>n>>m;
    while(m--){
        cin>>a>>b>>c;
        adj[a].eb(c,b);
        adj[b].eb(c,a);
    }
    spfa(1);
    cout<<n-1<<endl;
    FOR(i,2,n) cout<<i<<' '<<par[i]<<endl;
    return 0;
}