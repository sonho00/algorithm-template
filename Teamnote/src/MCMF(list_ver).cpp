#include<bits/stdc++.h>
#define SRC 0
#define SNK 2*n+1

using namespace std;

struct Edge{
    int nxt, rev, cst, cap, flw;
    Edge() {}
    Edge(int a, int b, int c, int d) : nxt(a), rev(b), cst(c), cap(d), flw(0) {}
};

int n, xy[202][202];
vector<Edge> lst[405];
int res;
const int INF=1e9;

void MCMF()
{
    while(1){
        int prev[405], dist[405], idx[405];
        bool InQ[405]={0};
        queue<int> Q;
        memset(prev,-1,sizeof(prev));
        for(int i=0 ; i<=SNK ; i++) dist[i]=INF;
        Q.push(SRC);
        dist[SRC]=0, InQ[SRC]=true;
        while(!Q.empty()){
            int v=Q.front();
            Q.pop();
            InQ[v]=false;
            for(int i=0 ; i<lst[v].size() ; i++){
                int nxt=lst[v][i].nxt;
                if(dist[nxt]>dist[v]+lst[v][i].cst && lst[v][i].cap-lst[v][i].flw){
                    dist[nxt]=dist[v]+lst[v][i].cst;
                    prev[nxt]=v;
                    idx[nxt]=i;
                    if(!InQ[nxt]) Q.push(nxt), InQ[nxt]=true;
                }
            }
        }
        if(prev[SNK]==-1) break;
        int v=SNK, flw=INF;
        while(v!=SRC){
            int v1=prev[v];
            int v2=idx[v];
            int pos=lst[v1][v2].cap-lst[v1][v2].flw;
            flw=min(flw,pos);
            v=prev[v];
        }
        v=SNK;
        while(v!=SRC){
            int v1=prev[v];
            int v2=idx[v];
            lst[v1][v2].flw+=flw;

            res+=lst[v1][v2].cst*flw;

            v2=lst[v1][v2].rev;
            v1=v;
            lst[v1][v2].flw-=flw;
            v=prev[v];
        }
    }
}
