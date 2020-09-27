#include<bits/stdc++.h>

using namespace std;

struct Edge{
    int nxt, rev, cap, flw;
    Edge() {}
    Edge(int a, int b, int c) : nxt(a), rev(b), cap(c), flw(0) {}
};

int m, n;
int xy[102][102], num[102][102];
vector<Edge> lst[20005];
int SRC, SNK, res, work[20005], level[20005];
const int INF=1e9;

void add_edge(int v1, int v2, int f)
{
    lst[v1].emplace_back(v2,lst[v2].size(),f);
    lst[v2].emplace_back(v1,lst[v1].size()-1,0);
}

bool bfs()
{
    queue<int> Q;
    memset(level,-1,sizeof(level));
    level[SRC]=0;
    Q.push(SRC);
    while(!Q.empty()){
        int v=Q.front();
        Q.pop();
        for(int i=0 ; i<lst[v].size() ; i++){
            int nxt=lst[v][i].nxt;
            if(level[nxt]==-1 && lst[v][i].cap-lst[v][i].flw>0){
                Q.push(nxt);
                level[nxt]=level[v]+1;
            }
        }
    }
    return level[SNK]!=-1;
}

int dfs(int v, int fn, int flow)
{
    if(v==fn) return flow;
    for(int &i=work[v] ; i<lst[v].size() ; i++){
        int nxt=lst[v][i].nxt;
        if(level[nxt]==level[v]+1 && lst[v][i].cap-lst[v][i].flw>0){
            int df=dfs(nxt,fn,min(flow,lst[v][i].cap-lst[v][i].flw));
            if(df>0){
                lst[v][i].flw+=df;
                lst[nxt][lst[v][i].rev].flw-=df;
                return df;
            }
        }
    }
    return 0;
}

void dinic()
{
    while(bfs()){
        memset(work,0,sizeof(work));
        while(1){
            int flow=dfs(SRC,SNK,INF);
            if(flow==0) break;
            res+=flow;
        }
    }
}
