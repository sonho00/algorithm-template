#include<bits/stdc++.h>
using namespace std;

struct SCC{
    int n,sccn,dfsn;
    vector<int> scc,dfn,low;
    vector<vector<int>> adj;
    stack<int> s;
    SCC(int n):n(n),adj(n+5),scc(n+5),dfn(n+5),low(n+5){}
    void dfs(int idx){
        low[idx]=dfn[idx]=++dfsn;
        s.push(idx);
        for(int nxt:adj[idx]){
            if(!dfn[nxt]) dfs(nxt);
            if(!scc[nxt]) low[idx]=min(low[idx],low[nxt]);
        }
        if(low[idx]==dfn[idx]){
            ++sccn;
            while(1){
                int tmp=s.top();
                s.pop();
                scc[tmp]=sccn;
                if(tmp==idx) break;
            }
        }
    }
    void solve(){
        for(int i=1; i<=n; ++i){
            if(!dfn[i]) dfs(i);
        }
    }
};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int v,e;
    cin>>v>>e;
    SCC scc(v);
    for(int i=0; i<e; ++i){
        int a,b;
        cin>>a>>b;
        scc.adj[a].push_back(b);
    }
    scc.solve();
    vector<vector<int>> ans(scc.sccn);
    for(int i=1; i<=v; ++i){
        ans[scc.scc[i]-1].push_back(i);
    }
    for(int i=0; i<scc.sccn; ++i){
        sort(ans[i].begin(),ans[i].end());
    }
    sort(ans.begin(),ans.end());
    cout<<scc.sccn<<'\n';
    for(int i=0; i<scc.sccn; ++i){
        for(int j:ans[i]){
            cout<<j<<' ';
        }
        cout<<"-1\n";
    }
    return 0;
}