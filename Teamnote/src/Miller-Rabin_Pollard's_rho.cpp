#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
ll mult(ll p,ll q, ll m){
    p %= m;
    q %= m;
    ll r = 0;
    ll w = p;
    while(q){
        if(q%2)
            r = (r+w)%m;
        w=(w+w)%m;
        q>>=1;
    }
    return r;
}
ll fpow(ll x, ll y, ll p){
    ll result=1;
    x=x%p;
    while(y>0){
        if(y&1)
            result=mult(result,x,p);
        y=y>>1;
        x=mult(x,x,p);
    }
    return result;
}

ll gcd(ll a, ll b){
    if(a<b)
        swap(a,b);
    while(b!=0){
        ll r = a%b;
        a=b;
        b=r;
    }
    return a;
}
bool millerRabin(ll n,ll a){
    ll r=0;
    ll d=n-1;
    while(d%2==0){
        r+=1;
        d/=2;
    }
    ll x=fpow(a,d,n);
    if(x==1 || x==n-1)
        return true;
    for(int i=0;i<r-1;i++){
        x=fpow(x,2,n);
        if(x==n-1)
            return true;
    }
    return false;
}
bool isPrime(ll n){
    ll aL[]={2, 325, 9375, 28178, 450775, 9780504, 1795265022};
    if(n==1) return false;
    if(n<=3) return true;
    if(!(n%2)) return false;
    for(auto a : aL){
        if(n==a)
            return true;
        if(!millerRabin(n,a))
            return false;
    }
    return true;
}
ll pollardRho(ll n){
    if(isPrime(n))
        return n;
    if(n==1)
        return 1;
    if(!(n%2))
        return 2;
    ll x=rand()%n+2;
    ll y=x;
    ll c=rand()%n+1;
    ll d=1;
    while(d==1){
        x=(mult(x,x,n)+c+n)%n;
        y=(mult(y,y,n)+c+n)%n;
        y=(mult(y,y,n)+c+n)%n;
        d=gcd(abs(x-y),n);
        if(d==n)
            return pollardRho(n);
    }
    if(isPrime(d))
        return d;
    else
        return pollardRho(d);
}
int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);
    vector<ll> v;
    ll n;
    cin>>n;
    int cnt=0;
    while(n>1){
        ll div = pollardRho(n);
        v.push_back(div);
        n/=div;
        cnt++;
    }
    sort(v.begin(),v.end());
    v.push_back(2);
    ll mul=1;
    for(int i=0,j=0;i<cnt;i++,j++){
        if(v[i]!=v[i+1]){
            mul*=fpow(v[i],j+1,1e18)-fpow(v[i],j,1e18);
            j=-1;
        }
    }
    cout<<mul;
}