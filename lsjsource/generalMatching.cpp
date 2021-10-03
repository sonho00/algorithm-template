#include <bits/stdc++.h>
using namespace std;
constexpr int MOD = 998244353;
int power(int a, int n)
{
    int ret = 1;
    for (; n; a = 1LL * a * a % MOD, n >>= 1)
        if (n % 2) ret = 1LL * ret * a % MOD;
    return ret;
}
int N, M;
signed main()
{
    cin.tie(0)->sync_with_stdio(false);
    mt19937 rand(time(0));
    cin>>N>>M;
    vector<vector<int>> A(N, vector<int>(N));
    for (int i = 0; i < M; ++i)
    {
        int u, v; cin>>u>>v; --u, --v;
        int r = (int)rand() % (MOD - 1) + 1;
        A[u][v] = A[v][u] = r;
    }
    for (int i = 0; i < N; ++i)
    {
        for (int j = i; j < N; ++j)
        {
            if (A[j][i])
            {
                swap(A[i], A[j]);
                break;
            }
        }
        if (!A[i][i]) continue;
        int k = power(A[i][i], MOD - 2);
        for (int j = i; j < N; ++j) A[i][j] = (1LL * A[i][j] * k) % MOD;
        for (int j = i + 1; j < N; ++j)
        {
            if (A[j][i])
            {
                int x = A[j][i];
                for (int k = i; k < N; ++k) A[j][k] = (A[j][k] - 1LL * A[i][k] * x % MOD + MOD) % MOD;
            }
        }
    }
    int rk = 0;
    for (int i = 0; i < N; ++i) if (A[i][i]) ++rk;
    cout << rk / 2 << '\n';
    return 0;
}
