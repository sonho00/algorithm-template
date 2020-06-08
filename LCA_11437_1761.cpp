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

ll lb(ll x){
    ll ret=-1;
    while(x){
        x>>=1;
        ++ret;
    }
    return ret;
}
struct graph{
    ll n,log;
    vector<vp> adj,anc;
    vl lv;
    graph(ll n):n(n),log(lb(n)),adj(vector<vp>(n+5)){}
    void bfs(ll idx){
        anc=vector<vp>(n+5,vp(log+5));
        lv=vl(n+5);
        lv[idx]=1;
        queue<ll> q;
        q.push(idx);
        while(!q.empty()){
            ll top=q.front();
            q.pop();
            for(pll& p:adj[top]){
                if(lv[p.se]) continue;
                lv[p.se]=lv[top]+1;
                q.push(p.se);
                anc[p.se][0]={p.fi,top};
            }
        }
        FOR(j,1,log+3) FOR(i,1,n){
            ll a,b;
            tie(a,b)=anc[i][j-1];
            anc[i][j]={a+anc[b][j-1].fi,anc[b][j-1].se};
        }
    }
    void goai(pll& ret,ll& a,ll i){
        pll& p=anc[a][i];
        ret.fi+=p.fi;
        ret.se=a=p.se;
    }
    pll lca(ll a,ll b){
        pll ret(0,a);
        if(lv[a]>lv[b]) swap(a,b);
        for(ll diff=lv[b]-lv[a],i=0; diff; ++i){
            if(diff&1<<i){
                diff^=1<<i;
                goai(ret,b,i);
            }
        }
        if(a==b) return ret;
        for(ll i=log; i>=0; --i){
            if(anc[a][i].se!=anc[b][i].se){
                goai(ret,a,i);
                goai(ret,b,i);
            }
        }
        goai(ret,a,0);
        goai(ret,b,0);
        return ret;
    }
};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll n,a,b,c;
    cin>>n;
    graph G(n);
    FOR(i,2,n){
        cin>>a>>b>>c;
        G.adj[a].eb(c,b);
        G.adj[b].eb(c,a);
    }
    G.bfs(1);
    cin>>n;
    while(n--){
        cin>>a>>b;
        cout<<G.lca(a,b).fi<<endl;
    }
    return 0;
}