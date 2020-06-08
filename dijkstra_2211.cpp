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
const ll MAXV=1e3;

ll n,m;
vp adj[MAXV+5];
ll dist[MAXV+5];
ll par[MAXV+5];

void dijk(ll idx){
    FOR(i,1,n) dist[i]=INF;
    dist[idx]=0;
    priority_queue<pll,vp,greater<pll>> pq;
    pq.emplace(0,idx);
    while(!pq.empty()){
        ll a,b;
        tie(a,b)=pq.top();
        pq.pop();
        if(dist[b]!=a) continue;
        for(pll& p:adj[b]){
            ll c,d;
            tie(c,d)=p;
            c+=a;
            if(dist[d]>c){
                dist[d]=c;
                par[d]=b;
                pq.emplace(c,d);
            }
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m;
    while(m--){
        ll a,b,c;
        cin>>a>>b>>c;
        adj[a].eb(c,b);
        adj[b].eb(c,a);
    }
    dijk(1);
    cout<<n-1<<endl;
    FOR(i,2,n) cout<<i<<' '<<par[i]<<endl;
    return 0;
}