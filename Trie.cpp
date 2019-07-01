#include <stdio.h>
#include <iostream>
#include <cstring>
typedef unsigned long long ull;
const int maxn = 11;
const int inf = 0x3f3f3f3f;
using namespace std;
struct trie
{
    trie *nxt[26];
    int cnt;
    trie()
    {
        cnt = 1;
        memset(nxt,NULL,sizeof(nxt));
    }
};

trie *root;
int i,id;
char S[maxn],s1[maxn];

void Insert(char *s)
{
    trie *p = root;
    i = 0;
    while(s[i]){
        id = s[i] - 'a';
        if(p->nxt[id])
        {
            p = p->nxt[id];
            p -> cnt++;
        }
        else
        {
            p -> nxt[id] = new trie;
            p = p -> nxt[id];
        }
        i++;
    }
}


int query(char* s)
{
    trie *p = root;
    i = 0;
    while(s[i])
    {
        id = s[i] - 'a';
        if(p -> nxt[id]) p = p -> nxt[id];
        else return 0;
        i++;
    }
    return p -> cnt;
}

void Free(trie *p)
{
    for(i = 0; i < 26; ++i) if(p -> nxt[i] != NULL) Free(p->nxt[i]);
    delete(p);
    p = NULL;
}

int main()
{
    root = new trie;
    while(scanf("%s",S)){
        Insert(S);
        cin.get();
        if(cin.peek() == '\n') break;
    }
    while(scanf("%s",s1) != EOF){
        printf("%d\n",query(s1));
    }
    return 0;
}
