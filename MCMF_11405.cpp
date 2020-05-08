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

struct MCMF{
    ll n;
    vector<vector<ll>> cap,cost,flow;
    vector<ll> lv;
    MCMF(ll n):n(n),
    cap(vector<vector<ll>>(n+5,vector<ll>(n+5))),
    cost(vector<vector<ll>>(n+5,vector<ll>(n+5))),
    flow(vector<vector<ll>>(n+5,vector<ll>(n+5)))
    {}
    pll spfa(){
        vector<ll> dist(n+5,INF);
        dist[n+1]=0;
        vector<ll> par(n+5);
        vector<bool> inq(n+5);
        inq[n+1]=1;
        queue<ll> q;
        q.push(n+1);
        while(!q.empty()){
            ll top=q.front();
            q.pop();
            inq[top]=0;
            FOR(i,1,n+2){
                if(flow[top][i]<cap[top][i]){
                    ll d=dist[top]+cost[top][i];
                    if(dist[i]>d){
                        dist[i]=d;
                        par[i]=top;
                        if(!inq[i]){
                            inq[i]=1;
                            q.push(i);
                        }
                    }
                }
            }
        }
        if(dist[n+2]==INF) return pll(0,0);
        ll f=INF,v=n+2,p;
        while(v!=n+1){
            p=par[v];
            f=min(f,cap[p][v]-flow[p][v]);
            v=p;
        }
        v=n+2;
        while(v!=n+1){
            p=par[v];
            flow[p][v]+=f;
            flow[v][p]-=f;
            v=p;
        }
        return pll(f*dist[n+2],f);
    }
    pll operator()(){
        pll ret,tmp;
        while(1){
            tmp=spfa();
            if(!tmp.fi) break;
            ret.fi+=tmp.fi;
            ret.se+=tmp.se;
        }
        return ret;
    }
};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll n,m,v,a;
    cin>>n>>m;
    MCMF mcmf(n+m);
    FOR(i,1,n) cin>>mcmf.cap[mcmf.n+1][i];
    FOR(i,n+1,n+m) cin>>mcmf.cap[i][mcmf.n+2];
    FOR(j,n+1,n+m) FOR(i,1,n){
        cin>>mcmf.cost[i][j];
        mcmf.cost[j][i]=-mcmf.cost[i][j];
        mcmf.cap[i][j]=INF;
    }
    cout<<mcmf().fi;
    return 0;
}