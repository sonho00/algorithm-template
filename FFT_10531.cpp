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

typedef complex<double> base;
void FFT(vector<base> &a, bool invert)
{
    int N=a.size();
    for(int i=1,j=0; i<N; i++){
        int bit=N>>1;
        for(; j>=bit ; bit>>=1) j-=bit;
        j+=bit;
        if(i<j) swap(a[i],a[j]);
    }
    double ang=invert?-M_PI:M_PI;
    for(int len=2; len<=N; len<<=1,ang/=2){
        base wlen(cos(ang),sin(ang));
        for(int i=0; i<N; i+=len){
            base w(1);
            for(int j=0; j<len>>1; j++){
                base u=a[i|j], v=a[i|j|len>>1]*w;
                a[i|j]=u+v;
                a[i|j|len>>1]=u-v;
                w*=wlen;
            }
        }
    }
    if(invert)
        for(base& x:a) x/=N;
}
//when result of A(x)*B(x) is needed, resize a and b by na+nb-1 before using function
//size of both a and b is equal to length of equation A(x) and B(x)
void multiply(const vector<int> &a, const vector<int> &b, vector<int> &res)
{
    vector<base> fa(a.begin(),a.end());
    vector<base> fb(b.begin(),b.end());
    int N=1, na=a.size(), nb=b.size();
    while(N<na+nb) N<<=1;
    fa.resize(N), fb.resize(N);
    FFT(fa,false), FFT(fb,false);
    for(int i=0 ; i<N ; i++) fa[i]*=fb[i];
    FFT(fa,true);
    res.resize(N);
    for(int i=0 ; i<N ; i++) res[i]=(int)(fa[i].real()+(fa[i].real()>0 ? 0.5 : -0.5));
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin>>n;
    vector<int> k(2e5+1);
    while(n--){
        int x;
        cin>>x;
        k[x]=1;
    }
    vector<int> res;
    multiply(k,k,res);
    cin>>n;
    int cnt=0;
    while(n--){
        int d;
        cin>>d;
        if(res[d] || k[d]) ++cnt;
    }
    cout<<cnt;
    return 0;
}