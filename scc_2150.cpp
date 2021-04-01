#include<bits/stdc++.h>
using namespace std;

int v,e;
vector<int> adj[10101];
int dfsn;
int dfn[10101];
stack<int> s;
int scn[10101];
int sccn;

int dfs(int idx){
    int ret=dfn[idx]=++dfsn;
    s.push(idx);
    for(int nxt:adj[idx]){
        if(!dfn[nxt]) ret=min(ret,dfs(nxt));
        if(!scn[nxt]) ret=min(ret,dfn[nxt]);
    }
    if(ret==dfn[idx]){
        ++sccn;
        int tmp;
        do{
            tmp=s.top();
            s.pop();
            scn[tmp]=sccn;
        } while(tmp!=idx);
    }
    return ret;
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin>>v>>e;
    while(e--){
        int a,b;
        cin>>a>>b;
        adj[a].push_back(b);
    }

    for(int i=1; i<=v; ++i){
        if(!dfn[i]) dfs(i);
    }

    vector<vector<int>> ans(sccn);
    for(int i=1; i<=v; ++i){
        ans[scn[i]-1].push_back(i);
    }
    sort(ans.begin(),ans.end());
    cout<<ans.size()<<'\n';
    for(auto& v:ans){
        for(int x:v) cout<<x<<' ';
        cout<<"-1\n";
    }
    return 0;
}