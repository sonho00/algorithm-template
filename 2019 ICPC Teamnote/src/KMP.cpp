#include<bits/stdc++.h>

using namespace std;

int nh, ns;
char h[1000005], s[1000005]; // h=total string, s=target string
int fail[1000005]; // size=length of s
vector<int> res;

void KMP()
{
    nh=strlen(h);
    ns=strlen(s);
    for(int i=1, j=0 ; i<ns ; i++){
        fail[i]=0;
        while(j>0 && s[i]!=s[j]) j=fail[j-1];
        if(s[i]==s[j]) fail[i]=++j;
    }
    for(int i=0, j=0 ; i<nh ; i++){
        while(j>0 && h[i]!=s[j]) j=fail[j-1];
        if(h[i]==s[j]){
            if(j==ns-1){
                res.push_back(i-ns+1);
                j=fail[j];
            }
            else j++;
        }
    }
}
