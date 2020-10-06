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

vector<ll> ext_euc(ll a,ll b){
    vector<ll> ret={1,0,a};
    vector<ll> tmp={0,1,b};
    while(tmp[2]){
        ll q=ret[2]/tmp[2];
        ret={ret[0]-q*tmp[0],ret[1]-q*tmp[1],ret[2]-q*tmp[2]};
        swap(ret,tmp);
    }
    return ret;
}
/*
Chinese remainder theorem
write x=r mod n as pll{r,n}

input = array of {r_i,n_i}
output = {R,mul n_i}
*/
pll crt(vector<pll> arr){
    ll r=0,n=1;
    for(pll& p:arr){
        p.fi=(p.se+p.fi%p.se)%p.se;
        n*=p.se;
    }
    for(pll& p:arr) r=(r+n/p.se*ext_euc(n/p.se,p.se)[0]*p.fi%n)%n;
    return {(n+r%n)%n,n};
}

void tc(){
    ll m,n,x,y;
    cin>>m>>n>>x>>y;
    --x,--y;
    ll g=ext_euc(m,n)[2];
    ll a,b;
    tie(a,b)=crt({{x,m/g},{y,n/g}});
    for(ll i=a; i<=m*n/g; i+=b){
        if(i%m==x%m && i%n==y%n){
            cout<<i+1;
            return;
        }
    }
    cout<<-1;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll t;
    cin>>t;
    FOR(i,1,t){
        // cout<<"Case #"<<i;
        // cout<<":";
        // cout<<endl;
        tc();
        cout<<endl;
    }
    return 0;
}