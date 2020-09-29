#include<bits/stdc++.h>

using namespace std;
typedef pair<int,int> P;

int n;
vector<P> lst[10002];
bool check[10002];
int d[10002];
queue<int> Q;

int bfs(int st)
{
    int rd=0, rv=st;
    memset(check,false,sizeof(check));
    memset(d,0,sizeof(d));
    Q.push(st);
    check[st]=true;
    while(!Q.empty()){
        int v=Q.front();
        Q.pop();
        if(rd<d[v]) rd=d[v], rv=v;
        for(int i=0 ; i<lst[v].size() ; i++){
            int nxt=lst[v][i].first;
            if(!check[nxt]){
                check[nxt]=true;
                d[nxt]=d[v]+lst[v][i].second;
                Q.push(nxt);
            }
        }
    }
    return rv;
}

int main()
{
    scanf("%d",&n);
    for(int i=1 ; i<n ; i++){
        int a, b, d;
        scanf("%d %d %d",&a,&b,&d);
        lst[a].push_back(P(b,d));
        lst[b].push_back(P(a,d));
    }
    int v1=bfs(1);
    int v2=bfs(v1);
    printf("%d",d[v2]);
    return 0;
}
