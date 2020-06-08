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
const ll MAXV=4e4;
const ll LOG=20;

ll n;
vp adj[MAXV+5];
pll anc[MAXV+5][LOG+5];
ll lv[MAXV+5];

void bfs(ll idx){
    lv[idx]=1;
    queue<ll> q;
    q.push(idx);
    while(!q.empty()){
        ll top=q.front();
        q.pop();
        for(pll& p:adj[top]){
            ll a,b;
            tie(a,b)=p;
            if(lv[b]) continue;
            lv[b]=lv[top]+1;
            q.push(b);
            anc[b][0]={a,top};
        }
    }
    FOR(j,1,LOG) FOR(i,1,n){
        ll a,b;
        tie(a,b)=anc[i][j-1];
        ll c,d;
        tie(c,d)=anc[b][j-1];
        anc[i][j]={a+c,d};
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
    for(ll i=LOG; i>=0; --i){
        if(anc[a][i].se!=anc[b][i].se){
            goai(ret,a,i);
            goai(ret,b,i);
        }
    }
    goai(ret,a,0);
    goai(ret,b,0);
    return ret;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll a,b,c;
    cin>>n;
    FOR(i,2,n){
        cin>>a>>b>>c;
        adj[a].eb(c,b);
        adj[b].eb(c,a);
    }
    bfs(1);
    ll m;
    cin>>m;
    while(m--){
        cin>>a>>b;
        cout<<lca(a,b).fi<<endl;
    }
    return 0;
}