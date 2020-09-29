#include<bits/stdc++.h>

using namespace std;

int n, m;
vector<int> lst[10002];
vector<vector<int> > res;
int dfsn[10002], cnt, scc;
stack<int> S;
bool finished[10002];

int dfs(int v)
{
    dfsn[v]=++cnt;
    S.push(v);
    int minv=dfsn[v];
    for(int i=0 ; i<lst[v].size() ; i++){
        int nxt=lst[v][i];
        if(dfsn[nxt]==0) minv=min(minv,dfs(nxt));
        else if(!finished[nxt]) minv=min(minv,dfsn[nxt]);
    }
    if(dfsn[v]==minv){
        vector<int> res1;
        while(1){
            int c=S.top();
            S.pop();
            finished[c]=true;
            res1.push_back(c);
            if(c==v) break;
        }
        scc++;
        sort(res1.begin(),res1.end());
        res.push_back(res1);
    }
    return minv;
}

int main()
{
    scanf("%d %d",&n,&m);
    for(int i=0 ; i<m ; i++){
        int a, b;
        scanf("%d %d",&a,&b);
        lst[a].push_back(b);
    }
    for(int i=1 ; i<=n ; i++) if(dfsn[i]==0) dfs(i);
    sort(res.begin(),res.end());
    printf("%d\n",scc);
    for(int i=0 ; i<scc ; i++){
        for(int j=0 ; j<res[i].size() ; j++) printf("%d ",res[i][j]);
        printf("-1\n");
    }
    return 0;
}
