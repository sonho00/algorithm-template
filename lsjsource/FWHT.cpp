template<typename T>
void fwht(vector<T> &a, bool invert) {
    int bit = 31 - __builtin_clz((int)a.size());
    for (int i = 0; i < bit ;++i)
    {
        for (int j = 0; j < (1 << bit); ++j)
        {
            if ((j >> i) & 1) continue;
            T u = a[j], v = a[j | (1 << i)];
            a[j] = u + v;
            a[j | (1 << i)] = u - v;
        }
    }
    if (invert) for (int i = 0; i < (int)a.size(); ++i)
        a[i] /= (T)a.size();
}
template<typename T>
vector<T> xor_mult(vector<T> a, vector<T> b)
{
    int ma = max((int)a.size(), (int)b.size());
    int N = 1;
    while(N < ma) N <<= 1;
    a.resize(N); b.resize(N);
    fwht(a, false); fwht(b, false);
    for(int i = 0; i < N; ++i) a[i] *= b[i];
    fwht(a, true);
    return a;
}
