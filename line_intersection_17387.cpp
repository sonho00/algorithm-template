#include<bits/stdc++.h>
#define x first
#define y second
#define fi first
#define se second
using namespace std;
using ll=long long;
using point=pair<ll,ll>;
using line=pair<point,point>;

template<typename T>
istream& operator>>(istream& in,T& a){return in>>a.fi>>a.se;}
point operator-(point a,point b){return point(a.x-b.x,a.y-b.y);}
ll outpro(point a,point b){return a.x*b.y-b.x*a.y;}
ll ccw(point a,point b,point c){
    ll dir=outpro(b-a,c-a);
    if(!dir) return 0;
    if(dir>0) return 1;
    else return -1;
}
bool cross(line a,line b){
    ll c=ccw(a.fi,a.se,b.fi)*ccw(a.fi,a.se,b.se);
    ll d=ccw(b.fi,b.se,a.fi)*ccw(b.fi,b.se,a.se);
    if(!c && !d){
        if(a.fi>a.se) swap(a.fi,a.se);
        if(b.fi>b.se) swap(b.fi,b.se);
        return !(a.se<b.fi || b.se<a.fi);
    }
    return c<=0 && d<=0;
}

int main(){
    line l1,l2;
    cin>>l1>>l2;
    cout<<cross(l1,l2);
    return 0;
}
