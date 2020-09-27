#include<bits/stdc++.h>

using namespace std;
typedef pair<int,int> P;

int n, st;
vector<P> lst[20002];
priority_queue<P, vector<P>, greater<P> > PQ;
int dist[20002];
bool visit[20002];
const int INF=1e9;

int main()
{
    int m, a, b, c, v;
    scanf("%d %d",&n,&m);
    scanf("%d",&st);
    for(int i=0 ; i<m ; i++){
        scanf("%d %d %d",&a,&b,&c);
        lst[a].push_back(P(b,c));
    }
    for(int i=1 ; i<=n ; i++) dist[i]=INF;
    dist[st]=0;
    PQ.push(P(0,st));
    while(!PQ.empty()){
        do{
            v=PQ.top().second;
            PQ.pop();
        }while(!PQ.empty() && visit[v]);
        visit[v]=true;
        for(int i=0 ; i<lst[v].size() ; i++){
            if(dist[lst[v][i].first]>dist[v]+lst[v][i].second){
                dist[lst[v][i].first]=dist[v]+lst[v][i].second;
                PQ.push(P(dist[lst[v][i].first],lst[v][i].first));
            }
        }
    }
    for(int i=1 ; i<=n ; i++){
        if(dist[i]==INF) printf("INF\n");
        else printf("%d\n",dist[i]);
    }
    return 0;
}
