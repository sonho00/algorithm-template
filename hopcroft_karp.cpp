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
vector<ll> adj[MAX+5];

struct bimat{
    vector<ll> mata,matb,lv;
    void make(ll n,ll m){
        mata=vector<ll>(n+5,0);
        matb=vector<ll>(m+5,0);
    }
    void hop_bfs(){
        lv=vector<ll>(n+5,0);
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

bimat hopcroft;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m;
    hopcroft.make(n,m);
    FOR(i,1,n){
        ll s;
        cin>>s;
        while(s--){
            ll sn;
            cin>>sn;
            adj[i].pb(sn);
        }
    }
    cout<<hopcroft();
    return 0;
}