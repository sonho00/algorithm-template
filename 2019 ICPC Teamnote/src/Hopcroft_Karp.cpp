#include<bits/stdc++.h>

using namespace std;

int n;
vector<int> lst[10005];
int G1[10005], G2[10005], dist[10005];
bool used[10005];
const int INF=1e9;
// size of lst, G1, dist and used is MAXN
// size of G2 is MAXM
// vertex number should be 1~n in G1 and 1~m in G2
// only add edges which is from G1 to G2

void bfs()
{
    queue<int> Q;
    for(int i=0 ; i<n ; i++){
        if(!used[i]) Q.push(i), dist[i]=0;
        else dist[i]=INF;
    }
    while(!Q.empty()){
        int v=Q.front();
        Q.pop();
        for(int i=0 ; i<lst[v].size() ; i++){
            int nxt=lst[v][i];
            if(G2[nxt]!=-1 && dist[G2[nxt]]==INF){
                dist[G2[nxt]]=dist[v]+1;
                Q.push(G2[nxt]);
            }
        }
    }
}

bool dfs(int v1)
{
    for(int i=0 ; i<lst[v1].size() ; i++){
        int v2=lst[v1][i];
        if(G2[v2]==-1 || (dist[G2[v2]]==dist[v1]+1 && dfs(G2[v2]))){
            used[v1]=true;
            G1[v1]=v2;
            G2[v2]=v1;
            return true;
        }
    }
    return false;
}

int Hopcroft_Karp()
{
    int matched=0;
    memset(used,false,sizeof(used));
    memset(G1,-1,sizeof(G1));
    memset(G2,-1,sizeof(G2));
    while(1){
        bfs();
        int flow=0;
        for(int i=0 ; i<n ; i++){
            if(!used[i] && dfs(i)) flow++;
        }
        if(flow==0) break;
        matched+=flow;
    }
    return matched;
}
