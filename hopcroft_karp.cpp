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
const ll MAX=1e4;
const ll MOD=1e9+7;
const ll LOG=20;

ll n,m;
ll mata[MAX+5],matb[MAX+5];
ll lv[MAX+5];
vector<ll> adj[MAX+5];

void hop_bfs(){
    memset(lv,0,sizeof(lv));
    ll q[MAX+5];
    ll s=0,e=0;
    FOR(i,1,n){
        if(!mata[i]){
            lv[i]=1;
            q[e++]=i;
        }
    }
    while(s<e){
        ll top=q[s++];
        for(ll nxt:adj[top]){
            nxt=matb[nxt];
            if(nxt && !lv[nxt]){
                lv[nxt]=lv[top]+1;
                q[e++]=nxt;
            }
        }
    }
}
bool hop_dfs(ll idx){
    for(ll i:adj[idx]){
        ll nxt=matb[i];
        if(!nxt || lv[nxt]==lv[idx]+1 && hop_dfs(nxt)){
            matb[i]=idx;
            mata[idx]=i;
            return true;
        }
    }
    return false;
}
ll hopcroft(){
    ll ret=0;
    while(1){
        hop_bfs();
        ll tmp=0;
        FOR(i,1,n) if(!mata[i] && hop_dfs(i)) ++tmp;
        if(tmp) ret+=tmp;
        else break;
    }
    return ret;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m;
    FOR(i,1,n){
        ll s;
        cin>>s;
        while(s--){
            ll sn;
            cin>>sn;
            adj[i].pb(sn);
        }
    }
    cout<<hopcroft()<<'\n';
    return 0;
}