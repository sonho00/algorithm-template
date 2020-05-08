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

ll n,m;
vector<pll> adj[MAX+5];

struct LCA{
    ll lv[MAX+5];
    pll anc[MAX+5][LOG+5];
    void bfs(ll idx){
        queue<ll> q;
        vector<bool> visit(n+5,0);
        lv[idx]=visit[idx]=1;
        q.push(idx);
        while(!q.empty()){
            ll top=q.front();
            q.pop();
            for(pll& p:adj[top]){
                if(visit[p.se]) continue;
                visit[p.se]=1;
                lv[p.se]=lv[top]+1;
                anc[p.se][0]={p.fi,top};
                q.push(p.se);
            }
        }
        FOR(j,1,LOG) FOR(i,1,n){
            ll a,b;
            tie(a,b)=anc[i][j-1];
            anc[i][j]={a+anc[b][j-1].fi,anc[b][j-1].se};
        }
    }
    void updt(pll& a,ll& b,ll c){
        pll& p=anc[b][c];
        a.fi+=p.fi;
        b=a.se=p.se;
    }
    pll operator()(ll a,ll b){
        if(lv[a]>lv[b]) swap(a,b);
        pll ret(0,a);
        for(ll diff=lv[b]-lv[a],i=0; diff; ++i){
            if(diff&1<<i){
                diff^=1<<i;
                updt(ret,b,i);
            }
        }
        if(a==b) return ret;
        for(ll i=LOG; i>=0; --i){
            if(!anc[a][i].se) continue;
            if(anc[a][i].se!=anc[b][i].se){
                updt(ret,a,i);
                updt(ret,b,i);
            }
        }
        updt(ret,a,0);
        updt(ret,b,0);
        return ret;
    }
};
LCA lca;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    ll a,b,c;
    FOR(i,2,n){
        cin>>a>>b>>c;
        adj[a].eb(c,b);
        adj[b].eb(c,a);
    }
    lca.bfs(1);
    cin>>m;
    FOR(i,1,m){
        cin>>a>>b;
        cout<<lca(a,b).fi<<'\n';
    }
    return 0;
}