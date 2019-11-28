#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e5+200;
int n,k;
int data[maxn];
vector<int> E[maxn];
vector< pair<int,int> > leaves;
pair<int,int> node[maxn];
int parent[maxn],nxt[maxn];
bool vis[maxn];

void init(){
    memset(nxt,-1,sizeof(nxt));
    memset(parent,-1,sizeof(parent));
    for(int i = 0; i < n; ++i) node[i].second=i;
}

//dfs(root,-1,1)
void dfs(int u,int uu,int dep){
    parent[u]=uu;
    if(E[u].size()==1){
        leaves.push_back({dep,u});
        return;
    }
    for(int i = 0; i < E[u].size(); ++i){
        if(E[u][i]==uu) continue;
        dfs(E[u][i],u,dep+1);
    }
}

void solve(int u){
    node[u].first = 1;
    while(parent[u]!=-1){
        if(node[u].first+1>node[parent[u]].first){
            node[parent[u]].first=node[u].first+1;
            nxt[parent[u]]=u;
            u=parent[u];
        }
        else break;
    }
}

void getlen(){
    sort(leaves.begin(),leaves.end(),greater< pair<int,int> >());
    for(int i = 0; i < leaves.size(); ++i) solve(leaves[i].second);
    sort(node,node+n,greater< pair<int,int> >());
}

void Erase(int u){
    while(u!=-1){
        vis[u]=1;
        u=nxt[u];
    }
}

int main()
{
    cin >> n >> k;
    for(int i = 0; i < k; ++i) cin >> data[i];
    sort(data,data+n,greater<int>());
    for(int i = 1; i < n; ++i){
        int x;
        cin >> x;
        E[x].push_back(i);
        E[i].push_back(x);
    }
    init();
    dfs(0,-1,1);
    getlen();
    int ans = 0,i = 0,j = 0;
    while(i<k&&j<n){
        if(vis[node[j].second]){
            j++;
            continue;
        }
        ans += node[j].first*data[i];
        Erase(node[j].second);
        ++i;++j;
    }
    cout << ans-data[0] << endl;
    return 0;
}
