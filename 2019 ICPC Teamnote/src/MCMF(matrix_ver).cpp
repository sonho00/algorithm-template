#include<bits/stdc++.h>

using namespace std;

int n, m;
vector<int> lst[805];
int SRC, SNK, cst[805][805];
int cap[805][805], flw[805][805];
int rcost, rflow;
const int INF=1e9;

void MCMF()
{
    while(1){
        int prev[805], dist[805];
        bool InQ[805]={0};
        memset(prev,-1,sizeof(prev));
        for(int i=0 ; i<=SNK ; i++) dist[i]=INF;
        queue<int> Q;
        dist[SRC]=0;
        Q.push(SRC);
        InQ[SRC]=true;
        while(!Q.empty()){
            int v=Q.front();
            Q.pop();
            InQ[v]=false;
            for(int i=0 ; i<lst[v].size() ; i++){
                int nxt=lst[v][i];
                if(dist[nxt]>dist[v]+cst[v][nxt] && cap[v][nxt]-flw[v][nxt]>0){
                    prev[nxt]=v;
                    dist[nxt]=dist[v]+cst[v][nxt];
                    if(!InQ[nxt]) Q.push(nxt), InQ[nxt]=true;
                }
            }
        }
        if(prev[SNK]==-1) break;
        int v=SNK, flow=INF;
        while(v!=SRC){
            flow=min(flow,cap[prev[v]][v]-flw[prev[v]][v]);
            v=prev[v];
        }
        v=SNK;
        while(v!=SRC){
            flw[prev[v]][v]+=flow;
            flw[v][prev[v]]-=flow;
            rcost+=flow*cst[prev[v]][v];
            v=prev[v];
        }
        rflow+=flow;
    }
}
