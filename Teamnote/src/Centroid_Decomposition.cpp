#include<bits/stdc++.h>

using namespace std;
typedef vector<vector<int> > graph;

struct CentroidDecomposition{
    graph CentTree; // result of Centroid Tree
    vector<bool> visit;
    vector<int> sub; // size of subtree
    int tot;
    CentroidDecomposition(int N){
        CentTree.resize(N+5);
        visit.resize(N+5);
        sub.resize(N+5);
    }
    void get_sz(int cur, int prev, graph &tree){
        sub[cur]=1;
        for(int i=0 ; i<tree[cur].size() ; i++){
            int nxt=tree[cur][i];
            if(!visit[nxt] && nxt!=prev){
                get_sz(nxt,cur,tree);
                sub[cur]+=sub[nxt];
            }
        }
    }
    int get_cen(int cur, int prev, graph &tree){
        for(int i=0 ; i<tree[cur].size() ; i++){
            int nxt=tree[cur][i];
            if(!visit[nxt] && nxt!=prev && sub[nxt]>tot/2)
                return get_cen(nxt,cur,tree);
        }
        return cur;
    }
    int decomp(int cur, int prev, graph &tree){
        get_sz(cur,prev,tree);
        tot=sub[cur];
        int cen=get_cen(cur,prev,tree);
        visit[cen]=true;
        for(int i=0 ; i<tree[cen].size() ; i++){
            int nxt=tree[cen][i];
            int nxtcen;
            if(!visit[nxt] && nxt!=prev){
                nxtcen=decomp(nxt,cen,tree);
                CentTree[cen].push_back(nxtcen);
                CentTree[nxtcen].push_back(cen);
            }
        }
        return cen;
    }
};
