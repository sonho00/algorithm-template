#include<bits/stdc++.h>

using namespace std;

int n, m;
vector<int> lst[20002];
int dfsn[20002], cnt, scc_num[20002], scc_cnt;
stack<int> S;

int dfs(int v)
{
    dfsn[v]=++cnt;
    S.push(v);
    int minv=dfsn[v];
    for(int i=0 ; i<lst[v].size() ; i++){
        int nxt=lst[v][i];
        if(dfsn[nxt]==0) minv=min(minv,dfs(nxt));
        else if(scc_num[nxt]==0) minv=min(minv,dfsn[nxt]);
    }
    if(dfsn[v]==minv){
        scc_cnt++;
        while(1){
            int cur=S.top();
            S.pop();
            scc_num[cur]=scc_cnt;
            if(v==cur) break;
        }
    }
    return minv;
}

int main()
{
    scanf("%d %d",&n,&m);
    for(int i=1 ; i<=m ; i++){
        int a, b;
        scanf("%d %d",&a,&b);
        lst[n-a].push_back(b+n);
        lst[n-b].push_back(a+n);
    }
    for(int i=0 ; i<=2*n ; i++) if(dfsn[i]==0 && i!=n) dfs(i);
    for(int i=1 ; i<=n ; i++){
        if(scc_num[n+i]==scc_num[n-i]){
            printf("0");
            return 0;
        }
    }
    printf("1\n");
    for(int i=1 ; i<=n ; i++){
        // SCC_num of not Xn is greater than SCC_num of Xn means
        // the result of topological sort by SCC -> not Xn has higher priority
        // therefore not Xn should be false -> Xn is true
        if(scc_num[n+i]<scc_num[n-i]) printf("1 ");
        else printf("0 ");
    }
    return 0;
}
