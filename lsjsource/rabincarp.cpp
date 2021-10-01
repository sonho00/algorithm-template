constexpr int HMOD = 1e9 + 7;
mt19937_64 rng(time(0));
uniform_int_distribution<int> distr(HMOD>>3, HMOD>>1);
using H = array<int, 2>;
const H base = {distr(rng), distr(rng)};
H operator+(H l, H r) {
    for (int i = 0; i < 2; ++i) if ((l[i] += r[i]) >= HMOD) l[i] -= HMOD;
    return l;
}
H operator-(H l, H r) {
    for (int i = 0; i < 2; ++i) if ((l[i] -= r[i]) < 0) l[i] += HMOD;
    return l;
}
H operator*(H l, H r) {
    for (int i = 0; i < 2; ++i) l[i] = (long long)l[i] * r[i] % HMOD;
    return l;
}
struct substring_hash{
    static vector<H> pows;
    vector<H> cum = {{0, 0}};
    substring_hash(string x){
        for (auto c: x) cum.push_back(cum.back() * base + H({c, c}));
    }
    void extend(int len) {
        while(len >= (int)pows.size()) pows.push_back(pows.back() * base);
    }
    H hash(int l, int r) {
        int len = r - l + 1;
        extend(len);
        return cum[r + 1] - cum[l] * pows[len];
    }
};
vector<H> substring_hash::pows = {{1, 1}};
