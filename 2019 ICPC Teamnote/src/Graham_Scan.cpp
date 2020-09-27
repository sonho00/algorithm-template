#include<bits/stdc++.h>

using namespace std;
typedef long long ll;

struct A{
    ll x, y, p, q;
};

bool cmp1(const A &a, const A &b) {return a.y<b.y || (a.y==b.y && a.x<b.x);}
bool cmp2(const A &a, const A &b) {return a.p*b.q-a.q*b.p>0 || (a.p*b.q-a.q*b.p==0 && a.p*a.p+a.q*a.q<b.p*b.p+b.q*b.q);}
bool ccw(ll x1, ll y1, ll x2, ll y2) {return x1*y2-y1*x2>0;}

int n;
A m[100002];
stack<int> S;

int main()
{
    scanf("%d",&n);
    for(int i=1 ; i<=n ; i++) scanf("%lld %lld",&m[i].x,&m[i].y);
    sort(m+1,m+1+n,cmp1);
    for(int i=1 ; i<=n ; i++) m[i].p=m[i].x-m[1].x, m[i].q=m[i].y-m[1].y;
    sort(m+2,m+1+n,cmp2);
    S.push(1); S.push(2);
    for(int i=3 ; i<=n ; i++){
        while(S.size()!=1){
            int first=S.top();
            S.pop();
            int second=S.top();
            if(ccw(m[first].p-m[second].p,m[first].q-m[second].q,m[i].p-m[first].p,m[i].q-m[first].q)){
                S.push(first);
                break;
            }
        }
        S.push(i);
    }
    printf("%d",S.size());
    return 0;
}
