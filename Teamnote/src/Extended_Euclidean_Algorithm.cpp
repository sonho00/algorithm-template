#include<bits/stdc++.h>

using namespace std;

tuple<int, int, int> extended_euclidean(int a, int b) {
    if (b == 0)
        return make_tuple(a, 1, 0);
    int g, x, y;
    tie(g, x, y) = extended_euclidean(b, a%b);
    return make_tuple(g, y, x-(a/b)*y);
}
