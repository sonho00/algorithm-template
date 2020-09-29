#include<bits/stdc++.h>

using namespace std;

struct Trie{
    Trie *nxt[10];
    bool epoint, nexist;
    Trie(){
        memset(nxt,0,sizeof(nxt));
        epoint=nexist=false;
    }
    ~Trie(){
        for(int i=0 ; i<10 ; i++) if(nxt[i]) delete nxt[i];
    }
    void update(const char *key){
        if(*key==0) epoint=true;
        else{
            int idx=*key-'0';
            if(!nxt[idx]) nxt[idx]=new Trie;
            nexist=true;
            nxt[idx]->update(key+1);
        }
    }
    bool consistent(){
        if(epoint && nexist) return false;
        for(int i=0 ; i<10 ; i++){
            if(nxt[i] && !nxt[i]->consistent()) return false;
        }
        return true;
    }
};

int t, n;
char s[12];

int main()
{
    for(scanf("%d",&t) ; t>0 ; t--){
        scanf("%d",&n);
        Trie *root=new Trie;
        for(int i=0 ; i<n ; i++){
            scanf("%s",s);
            root->update(s);
        }
        printf("%s\n",root->consistent() ? "YES" : "NO");
        delete root;
    }
    return 0;
}
