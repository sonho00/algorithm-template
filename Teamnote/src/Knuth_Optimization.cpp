#include<bits/stdc++.h>

int tc, n;
int m[5005];
int dp[5005][5005], pos[5005][5005];
int sum[5005];
const int INF=1e9;

int main()
{
    for(scanf("%d",&tc) ; tc>0 ; tc--){
        scanf("%d",&n);
        for(int i=1 ; i<=n ; i++){
            scanf("%d",&m[i]);
            pos[i][i]=i;
            sum[i]=sum[i-1]+m[i];
        }
        for(int len=2 ; len<=n ; len++){
            for(int i=1 ; i<=n-len+1 ; i++){
                dp[i][i+len-1]=INF;
                int s=pos[i][i+len-2], f=pos[i+1][i+len-1];
                for(int j=s ; j<=f ; j++){
                    if(j<n && dp[i][i+len-1]>dp[i][j]+dp[j+1][i+len-1]){
                        pos[i][i+len-1]=j;
                        dp[i][i+len-1]=dp[i][j]+dp[j+1][i+len-1];
                    }
                }
                dp[i][i+len-1]+=sum[i+len-1]-sum[i-1];
            }
        }
        printf("%d\n",dp[1][n]);
    }
    return 0;
}
