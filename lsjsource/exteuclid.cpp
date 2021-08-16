int inverse(int n, int m)
{
    n %= m;
    if (n <= 1) return n;
    return m - ((m * inverse(m, n) - 1) / n);
}
