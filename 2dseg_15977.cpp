#include<bits/stdc++.h>
using namespace std;

struct node1{
    int li,ri,val;
    node1(int li=-1,int ri=-1,int val=0):li(li),ri(ri),val(val){}
};

struct seg1{
    int n,idx,val,l,r;
    vector<node1> v;
    seg1(int n):n(n),v(1){}
    void update(int idx,int val){
        this->idx=idx;
        this->val=val;
        updt(0,1,n);
    }
    void updt(int vi,int s,int e){
        v[vi].val=max(v[vi].val,val);
        if(s==e) return;
        int m=s+e>>1;
        if(idx<=m){
            if(v[vi].li==-1){
                v[vi].li=v.size();
                v.emplace_back();
            }
            updt(v[vi].li,s,m);
        }
        else{
            if(v[vi].ri==-1){
                v[vi].ri=v.size();
                v.emplace_back();
            }
            updt(v[vi].ri,m+1,e);
        }
    }
    int query(int l,int r){
        this->l=l;
        this->r=r;
        return qry(0,1,n);
    }
    int qry(int vi,int s,int e){
        if(vi==-1 || r<s || e<l) return 0;
        if(l<=s && e<=r) return v[vi].val;
        int m=s+e>>1;
        int lv=qry(v[vi].li,s,m);
        int rv=qry(v[vi].ri,m+1,e);
        return max(lv,rv);
    }
};

struct node2{
    int li,ri;
    seg1 seg;
    node2(int n,int li=-1,int ri=-1):li(li),ri(ri),seg(n){}
};

struct seg2{
    int nx,ny,x,y,val,xs,xe,ys,ye;
    vector<node2> v;
    seg2(int nx,int ny):nx(nx),ny(ny),v(1,ny){}
    void update(int x,int y,int val){
        this->x=x;
        this->y=y;
        this->val=val;
        updt(0,1,nx);
    }
    void updt(int vi,int s,int e){
        v[vi].seg.update(y,val);
        if(s==e) return;
        int m=s+e>>1;
        if(x<=m){
            if(v[vi].li==-1){
                v[vi].li=v.size();
                v.emplace_back(ny);
            }
            updt(v[vi].li,s,m);
        }
        else{
            if(v[vi].ri==-1){
                v[vi].ri=v.size();
                v.emplace_back(ny);
            }
            updt(v[vi].ri,m+1,e);
        }
    }
    int query(int xs,int xe,int ys,int ye){
        this->xs=xs;
        this->xe=xe;
        this->ys=ys;
        this->ye=ye;
        return qry(0,1,nx);
    }
    int qry(int vi,int s,int e){
        if(vi==-1 || xe<s || e<xs) return 0;
        if(xs<=s && e<=xe) return v[vi].seg.query(ys,ye);
        int m=s+e>>1;
        int lv=qry(v[vi].li,s,m);
        int rv=qry(v[vi].ri,m+1,e);
        return max(lv,rv);
    }
};


int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int m,n;
    cin>>m>>n;
    vector<vector<int>> a(n,vector<int>(m));
    for(int j=0; j<m; ++j){
        vector<int> v(n);
        for(int i=0; i<n; ++i){
            cin>>a[i][j];
            v[i]=a[i][j];
        }
        sort(v.begin(),v.end());
        for(int i=0; i<n; ++i){
            a[i][j]=lower_bound(v.begin(),v.end(),a[i][j])-v.begin()+1;
        }
    }
    sort(a.begin(),a.end());
    int ans=0;
    if(m==2){
        seg1 seg(n);
        for(int i=0; i<n; ++i){
            int tmp=seg.query(1,a[i][1])+1;
            ans=max(ans,tmp);
            seg.update(a[i][1],tmp);
        }
    }
    else{
        seg2 seg(n,n);
        for(int i=0; i<n; ++i){
            int tmp=seg.query(1,a[i][1],1,a[i][2])+1;
            ans=max(ans,tmp);
            seg.update(a[i][1],a[i][2],tmp);
        }
    }
    cout<<ans;
}