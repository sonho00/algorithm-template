#include<bits/stdc++.h>

using namespace std;

struct in{
    int sx, sy, fx, fy;
    in() {}
    in(int x1, int y1, int x2, int y2) : sx(x1), sy(y1), fx(x2), fy(y2) {}
};

bool operator < (in a, in b){
    return a.fx>b.fx;
}

int n;
in m[10005];
int x[20005], xidx[20005];
int y[20005], yidx[20005];
vector<int> lst[20005];
priority_queue<in> PQ;

struct node{
    int len, cnt;
    node() {}
    node(int a, int b) : len(a), cnt(b) {}
};

struct SegmentTree{
    vector<node> tree;
    int base;
    SegmentTree() {}
    void setup(int a){
        base=1;
        while(base<a) base=base<<1;
        tree.resize(base*2+2);
        base--;
    }
    void update(int num, int st, int fn, int val, int ns=1, int nf=-1){
        if(nf==-1) nf=base+1;
        if(st>nf || fn<ns) return;
        if(st<=ns && nf<=fn){
            tree[num].cnt+=val;
            if(tree[num].cnt==0){
                if(ns!=nf) tree[num].len=tree[num*2].len+tree[num*2+1].len;
                else tree[num].len=0;
            }
            if(tree[num].cnt>0)
                tree[num].len=y[nf+1]-y[ns];
            return;
        }
        int mid=(ns+nf)>>1;
        update(num*2,st,fn,val,ns,mid);
        update(num*2+1,st,fn,val,mid+1,nf);
        if(tree[num].cnt==0){
            if(ns!=nf) tree[num].len=tree[num*2].len+tree[num*2+1].len;
            else tree[num].len=0;
        }
        if(tree[num].cnt>0)
            tree[num].len=y[nf+1]-y[ns];
    }
    int get_len() {return tree[1].len;}
};

int get_idx(int val, int *arr, int *iarr)
{
    int st=1, fn=n*2, mid;
    while(st<=fn){
        mid=(st+fn)>>1;
        if(val==arr[mid]) return iarr[mid];
        else if(val>arr[mid]) st=mid+1;
        else if(val<arr[mid]) fn=mid-1;
    }
}

void contraction()
{
    sort(x+1,x+1+2*n);
    int cnt=1;
    xidx[1]=1;
    for(int i=2 ; i<=n*2 ; i++){
        if(x[i-1]!=x[i]) cnt++;
        xidx[i]=cnt;
    }
    sort(y+1,y+1+2*n);
    cnt=1, yidx[1]=1;
    for(int i=2 ; i<=n*2 ; i++){
        if(y[i-1]!=y[i]) cnt++;
        yidx[i]=cnt;
    }
    for(int i=1 ; i<=n ; i++){
        m[i].sx=get_idx(m[i].sx,x,xidx);
        m[i].fx=get_idx(m[i].fx,x,xidx);
        m[i].sy=get_idx(m[i].sy,y,yidx);
        m[i].fy=get_idx(m[i].fy,y,yidx);
        lst[m[i].sx].push_back(i);
    }
    for(int i=1 ; i<=2*n ; i++) x[xidx[i]]=x[i], y[yidx[i]]=y[i];
}

int main()
{
    scanf("%d",&n);
    for(int i=1 ; i<=n ; i++){
        scanf("%d %d %d %d",&m[i].sx,&m[i].sy,&m[i].fx,&m[i].fy);
        x[i*2-1]=m[i].sx, x[i*2]=m[i].fx;
        y[i*2-1]=m[i].sy, y[i*2]=m[i].fy;
    }
    contraction();
    SegmentTree T;
    T.setup(yidx[2*n]-1);
    int res=0;
    for(int i=1 ; i<xidx[2*n] ; i++){
        for(int j=0 ; j<lst[i].size() ; j++){
            int idx=lst[i][j];
            PQ.push(m[idx]);
            T.update(1,m[idx].sy,m[idx].fy-1,1);
        }
        while(!PQ.empty() && PQ.top().fx==i){
            in val=PQ.top();
            T.update(1,val.sy,val.fy-1,-1);
            PQ.pop();
        }
        res+=T.get_len()*(x[i+1]-x[i]);
    }
    printf("%d",res);
    return 0;
}
