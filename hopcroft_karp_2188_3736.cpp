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

struct bimat{
    ll n,m;
    vector<vector<ll>> adj;
    vector<ll> mata,matb,lv;
    bimat(ll n,ll m):n(n),m(m),
    adj(vector<vector<ll>>(n+5)),
    mata(vector<ll>(n+5)),
    matb(vector<ll>(m+5))
    {}
    void hop_bfs(){
        lv=vector<ll>(n+5);
        queue<ll> q;
        FOR(i,1,n){
            if(!mata[i]){
                lv[i]=1;
                q.push(i);
            }
        }
        while(!q.empty()){
            ll top=q.front();
            q.pop();
            for(ll nxt:adj[top]){
                nxt=matb[nxt];
                if(nxt && !lv[nxt]){
                    lv[nxt]=lv[top]+1;
                    q.push(nxt);
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
    ll operator()(){
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
};

ll n;
void tc(){
    bimat hop(n,n);
    ll j,s,a;
    FOR(i,1,n){
        scanf("%lld: (%lld)",&j,&s);
        while(s--){
            scanf("%lld",&a);
            hop.adj[j+1].pb(a-n+1);
        }
    }
    printf("%lld\n",hop());
}

int main(){
    // ios_base::sync_with_stdio(0);
    // cin.tie(0);
    while(scanf("%lld",&n)>0) tc();
    return 0;
}