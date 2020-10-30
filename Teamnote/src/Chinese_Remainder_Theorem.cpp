#include<bits/stdc++.h>
#define fi first
#define se second
using namespace std;
using ll=long long;
using pll=pair<ll,ll>;

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
write x=a mod n as pll{a,n}

input = array of {a_i,n_i}
output = {x,N}
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
/*
CRT 확장
n_i가 서로소가 아닐 때도 사용 가능
복잡도 ~ k*sqrt(max(n_i))
k는 mod식 개수
*/
pll ext_crt(vector<pll> arr){
    vector<pll> tmp;
    ll m=1,a=0,b=1,c;
    for(pll& p:arr){
        c=1;
        while(!(p.se&1)){
            p.se>>=1;
            c<<=1;
        }
        if(b<c){
            if((p.fi-a)%b) return {-1,-1};
            a=p.fi;
            b=c;
        }
        else{
            if((p.fi-a)%c) return {-1,-1};
        }
        m=max(m,p.se);
    }
    if(b!=1) tmp.emplace_back(a,b);
    ll sqm=sqrt(m)+3;
    vector<bool> visit(sqm+5);
    for(ll i=3; i<=sqm; i+=2){
        if(visit[i]) continue;
        a=0,b=1;
        for(pll& p:arr){
            c=1;
            while(!(p.se%i)){
                p.se/=i;
                c*=i;
            }
            if(b<c){
                if((p.fi-a)%b) return {-1,-1};
                a=p.fi;
                b=c;
            }
            else{
                if((p.fi-a)%c) return {-1,-1};
            }
        }
        if(b!=1) tmp.emplace_back(a,b);
        for(ll j=i*i; j<=sqm; j+=i<<1){
            visit[j]=1;
        }
    }
    for(pll& p:arr){
        tie(a,b)=p;
        if(b==1) continue;
        for(pll& p:arr){
            if(p.se==b){
                if((p.fi-a)%b) return {-1,-1};
                p.se=1;
            }
        }
        tmp.emplace_back(a,b);
    }
    return crt(tmp);
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    ll a[3],b[3];
    for(ll i=0; i<3; ++i) cin>>a[i];
    for(ll i=0; i<3; ++i) cin>>b[i];
    vector<pll> arr;
    for(ll i=0; i<3; ++i) arr.emplace_back(b[i],a[i]);
    cout<<ext_crt(arr).fi;
    return 0;
}