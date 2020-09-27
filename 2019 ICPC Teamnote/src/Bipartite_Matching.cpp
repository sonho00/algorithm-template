#include<bits/stdc++.h>

using namespace std;

int n, m;
vector<int> lst[102];
int G1[102], G2[102];
bool visit[102];
//size of lst, G1 and visit is MAXN
//size of G2 is MAXM
//vertex number should be 1~n in G1 and 1~m in G2
// only add edges which is from G1 to G2

bool dfs(int v1)
{
    visit[v1]=true;
    for(int i=0 ; i<lst[v1].size() ; i++){
        int v2=lst[v1][i];
        if(G2[v2]==-1 || (!visit[G2[v2]] && dfs(G2[v2]))){
            G1[v1]=v2;
            G2[v2]=v1;
            return true;
        }
    }
    return false;
}

int main()
{
    int match=0;
    memset(G1,-1,sizeof(G1));
    memset(G2,-1,sizeof(G2));
    for(int i=1 ; i<=n ; i++){
        if(G1[i]==-1){
            memset(visit,false,sizeof(visit));
            if(dfs(i)) match++;
        }
    }
    return 0;
}
