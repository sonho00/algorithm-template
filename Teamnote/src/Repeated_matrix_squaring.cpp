#include<bits/stdc++.h>

using namespace std;
typedef vector<vector<int> > matrix;

int d, t;
const int MOD=31991;

matrix multiply(matrix A, matrix B)
{
    matrix C(d,vector<int>(d,0));
    for(int i=0 ; i<d ; i++)
        for(int j=0 ; j<d ; j++)
            for(int k=0 ; k<d ; k++) (C[i][j]+=A[i][k]*B[k][j])%=MOD;
    return C;
}

matrix get_pow(int p, matrix M)
{
    if(p==1) return M;
    matrix ret=get_pow(p/2,M);
    ret=multiply(ret,ret);
    if(p%2==1) ret=multiply(ret,M);
    return ret;
}

int main()
{
    scanf("%d %d",&d,&t);
    matrix base(d,vector<int>(d,0));
    for(int i=1 ; i<d ; i++) base[i-1][i]=1;
    for(int i=0 ; i<d ; i++) base[d-1][i]=1;
    matrix res=base;
    int sum=0;
    if(t>1){
        res=get_pow(t-1,base);
        for(int i=0 ; i<d ; i++) (sum+=res[i][d-1])%=MOD;
    }
    else sum=1;
    printf("%d",sum);
    return 0;
}
