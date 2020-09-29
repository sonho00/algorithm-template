#include<bits/stdc++.h>
using namespace std;
using ll=long long;

const ll A = 7, B = 26, P = A << B | 1, R = 3;
const ll SZ = 20, N = 1<<20;
ll Pow(ll x, ll y) {
    ll r = 1;
    while (y) {
        if (y & 1) r = r * x % P;
        x = x * x % P;
        y >>= 1;
    }
    return r;
}
void FFT(ll *a, bool f) {
    ll i, j, k, x, y, z;
    j = 0;
    for (i = 1; i < N; i++) {
        for (k = N >> 1; j >= k; k >>= 1) j -= k;
        j += k;
        if (i < j) {
            k = a[i];
            a[i] = a[j];
            a[j] = k;
        }
    }
    ll ang=f?Pow(R,P-2):R;
    for (i = 1; i < N; i <<= 1) {
        x = Pow(ang, P / i >> 1);
        for (j = 0; j < N; j += i << 1) {
            y = 1;
            for (k = 0; k < i; k++) {
                z = a[i | j | k] * y % P;
                a[i | j | k] = a[j | k] - z;
                if (a[i | j | k] < 0) a[i | j | k] += P;
                a[j | k] += z;
                if (a[j | k] >= P) a[j | k] -= P;
                y = y * x % P;
            }
        }
    }
    if (f) {
        j = Pow(N, P - 2);
        for (i = 0; i < N; i++) a[i] = a[i] * j % P;
    }
}

ll a[N];
ll c[N];
ll b[N];

int main() {
    ll i, n;
    cin>>n;
    for (i = 0; i < n; i++){
        ll x;
        cin>>x;
        a[x]=c[x]=1;
    }
    FFT(c, false);
    for (i = 0; i < N; i++){
        b[i]=c[i]*c[i]%P;
    }
    FFT(b, true);
    cin>>n;
    ll cnt=0;
    while(n--){
        ll x;
        cin>>x;
        if(a[x]||b[x]) ++cnt;
    }
    cout<<cnt;
    return 0;
}
