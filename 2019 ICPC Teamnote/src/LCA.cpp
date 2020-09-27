#include<bits/stdc++.h>

using namespace std;

int n;
int a,b;
vector<int> v[100005];
int q[100005][2];
bool visit[100005]={1};
int anc[100005][20];
int lvl[100005];

void init(){
    int s=0,e=1;
    q[0][0]=1;
    while(s<e){
        int idx=q[s][0];
        lvl[idx]=q[s++][1];
        visit[idx]=1;
        for(auto x:v[idx]){
            if(!visit[x]){
                anc[x][0]=idx;
                q[e][0]=x;
                q[e++][1]=lvl[idx]+1;
            }
        }
    }
    for(int i=1; i<20; i++){
        for(int j=1; j<=n; j++){
            anc[j][i]=anc[anc[j][i-1]][i-1];
        }
    }
}
int lca(int x, int y){
    int temp=lvl[x]-lvl[y];
    if(temp<0){
        temp=-temp;
        swap(x,y);
    }
    for(int i=0; temp; i++){
        if(temp&(1<<i)){
            x=anc[x][i];
            temp-=1<<i;
        }
    }
    if(x==y) return x;
    for(int i=19; x!=y && i>=0; i--){
        if(anc[x][i] && anc[y][i] && anc[x][i]!=anc[y][i]){
            x=anc[x][i];
            y=anc[y][i];
        }
    }
    return anc[x][0];
}

int main(){
    scanf("%d",&n);
    for(int x,y,i=0; i<n-1; i++){
        scanf("%d%d",&x,&y);
        v[x].push_back(y);
        v[y].push_back(x);
    }
    init();
    int m;
    scanf("%d",&m);
    while(m--){
        int x,y;
        scanf("%d%d",&x,&y);
        printf("%d\n",lca(x,y));
    }
    return 0;
}
