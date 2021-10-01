#include <bits/stdc++.h>
using namespace std;
constexpr __int128_t inf = 1e18;
istream& operator>>(istream& in, __int128_t& a)
{
    long long tmp; in>>tmp;
    a = tmp;
    return in;
}
signed main()
{
    cin.tie(0)->sync_with_stdio(false);
    int N; __int128_t K; cin>>N>>K;
    vector<__int128_t> A(N);
    for (auto& it: A) cin>>it;
    vector<__int128_t> suf(N + 1);
    for (int i = N - 1; i >= 0; --i)
        suf[i] = suf[i + 1] + A[i];
    __int128_t lf = 0, rg = 1e16;
    __int128_t ans = inf;
    while(lf <= rg)
    {
        __int128_t mid = (lf + rg) / 2;
        vector<__int128_t> dp(N + 1);
        vector<int> cnt(N + 1);
        vector<pair<__int128_t, int>> memo(N + 1);
        pair<__int128_t, int> mx = make_pair(-mid, 0);
        for (int i = N - 1; i >= 0; --i)
        {
            dp[i] = suf[i] + mx.first;
            cnt[i] = mx.second + 1;
            memo[i] = max(memo[i + 1], make_pair(dp[i], cnt[i]));
            mx = max(mx, make_pair(memo[i].first - mid - suf[i], memo[i].second));
        }
        ans = min(ans, memo[0].first + mid * K);
        if (cnt[0] <= K) rg = mid - 1;
        else lf = mid + 1;
    }
    cout << (long long)ans << '\n';
    return 0;
}
