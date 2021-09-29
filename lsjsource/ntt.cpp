/*
Numeric FFT
P == MOD == A*2^B + 1
R  A  B  P
5  3  30 3221225473
3  17 27 2281701377
31 15 27 2013265921
3  7  26 469762049
3 119 23 998244353
*/
const int A = 119, B = 23, MOD = A<<B | 1, R = 3;//MOD = 998244353
int power(int a, int n) {
    int res = 1;
    for (;n; n >>= 1, a = ((long long) a * a) % MOD)
        if (n & 1) res = ((long long) res * a) % MOD;
    return res;
}
inline int inv(int a) { return power(a, MOD - 2); }
void NTT(vector<int> &a, bool invert)
{
    int N=a.size();
    for(int i=1,j=0; i<N; i++){
        int bit=N>>1;
        for(; j>=bit ; bit>>=1) j-=bit;
        j+=bit;
        if(i<j) swap(a[i],a[j]);
    }
    int ang = invert?inv(R):R;
    for(int len=2; len<=N; len<<=1){
        int wlen = power(ang, (A<<B)/len);
        for(int i=0; i<N; i+=len){
            int w = 1;
            for(int j=0; j<len>>1; j++){
                int u=a[i|j], v=(long long)a[i|j|len>>1]*w%MOD;
                a[i|j]=(u+v)%MOD;
                a[i|j|len>>1] = (u-v+MOD)%MOD;
                w=(long long)w*wlen%MOD;
            }
        }
    }
    if(invert)
    {
        int j = inv(N);
        for(int& x:a) x = (long long)x * j % MOD;
    }
}
vector<int> operator*(vector<int> a, vector<int> b)
{
    int N = 1, na = a.size(), nb = b.size();
    while(N < na + nb - 1) N <<= 1;
    a.resize(N); b.resize(N);
    NTT(a, false), NTT(b, false);
    for (int i = 0; i<N;++i) a[i] = (long long)a[i] * b[i] % MOD;
    NTT(a, true);
    return a;
}
