#include<bits/stdc++.h>
using namespace std;

struct SAT{
    int n,sccn,dfsn;
    vector<int> scc,dfn,low;
    vector<vector<int>> adj;
    vector<bool> tf;
    stack<int> s;
    SAT(int n):n(n),adj(2*n+5),scc(2*n+5),dfn(2*n+5),low(2*n+5),tf(n+5){}
    void add(int a,int b){
        adj[a^1].push_back(b);
        adj[b^1].push_back(a);
    }
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
    bool solve(){
        for(int i=0; i<2*n; ++i){
            if(!dfn[i]) dfs(i);
        }
        for(int i=0; i<n; ++i){
            if(scc[i<<1]==scc[i<<1|1]) return 0;
        }
        for(int i=0; i<n; ++i){
            tf[i]=(scc[i<<1|1]>scc[i<<1]);
        }
        return 1;
    }
};

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n,m;
    cin>>n>>m;
    SAT sat(n);
    for(int i=0; i<m; ++i){
        int a,b;
        cin>>a>>b;
        if(a>0) a=2*a-2;
        else a=2*abs(a)-1;
        if(b>0) b=2*b-2;
        else b=2*abs(b)-1;
        sat.add(a,b);
    }
    if(sat.solve()){
        cout<<"1\n";
        for(int i=0; i<n; ++i){
            cout<<sat.tf[i]<<' ';
        }
    }
    else cout<<0;
}