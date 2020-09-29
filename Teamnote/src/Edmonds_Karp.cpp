#include<bits/stdc++.h>

using namespace std;
typedef pair<int, int> P;

vector<P> lst[55];
queue<int> Q;

int n, st, fn;
int flow[55][55];

int find_maximum_flow()
{
    int x, v, c, min_f, sum=0;
    P path[55];
    bool tf=true, check[55];
    while(tf){
        tf=false;
        Q.push(st);
        memset(check,false,sizeof(check));
        memset(path,0,sizeof(path));
        check[st]=true;
        while(!Q.empty()){
            x=Q.front();
            Q.pop();
            for(int i=0 ; i<lst[x].size() ; i++){
                v=lst[x][i].first;
                c=lst[x][i].second;
                if(!check[v] && c-flow[x][v]>0){
                    check[v]=true;
                    path[v]=P(x,c-flow[x][v]);
                    Q.push(v);
                }
            }
        }
        if(check[fn]){
            tf=true;
            x=fn;
            min_f=1e9;
            while(path[x].first!=0){
                min_f=min(min_f,path[x].second);
                x=path[x].first;
            }
            x=fn;
            while(path[x].first!=0){
                flow[path[x].first][x]+=min_f;
                flow[x][path[x].first]-=min_f;
                x=path[x].first;
            }
        }
    }
    for(int i=1 ; i<=52 ; i++) sum+=flow[i][fn];
    return sum;
}
