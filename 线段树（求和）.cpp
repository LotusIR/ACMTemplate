#include <bits/stdc++.h>
#define FAST ios::sync_with_stdio(0);cin.tie(0);cout.tie(0)
typedef long long ll;
const int maxn = 2e5+300;
const int inf = 0x3f3f3f3f;
using namespace std;

ll N,M,a[maxn],Sum[maxn<<2],pos[maxn];

//更新当前节点
void pushup(ll rt){
    Sum[rt] = Sum[rt<<1] + Sum[rt<<1|1];
}

//l:当前节点的左端点 r：当前节点的右端点 rt:当前节点的编号
void build(ll l,ll r,ll rt){
    if(l == r){
        pos[l] = rt;
        Sum[rt] = a[l];
        return;
    }
    ll m = (l+r) >> 1;
    build(l,m,rt<<1);
    build(m+1,r,rt<<1|1);
    pushup(rt);
}

//l:当前节点的左端点 r：当前节点的右端点 rt:当前节点的编号 [L,R]查询的区间
ll query(ll L,ll R,ll l,ll r,ll rt){
    if(L <= l && R >= r) return Sum[rt];
    ll m = (l+r) >> 1;
    ll res = 0;
    if(L <= m) res += query(L,R,l,m,rt<<1);
    if(R > m) res += query(L,R,m+1,r,rt<<1|1);
    return res;
}

//l:当前节点的左端点 r：当前节点的右端点 rt:当前节点的编号 将L的值改为V
ll update(ll L,ll V,ll l,ll r,ll rt){
    if(l==r){Sum[rt]=V;return rt;}
    ll m = (l+r) >> 1;
    if(L <= m) update(L,V,l,m,rt<<1);
    else update(L,V,m+1,r,rt<<1|1);
    pushup(rt);
}

int main(){
    scanf("%lld%lld",&N,&M);
    for(ll i = 1; i <= N; ++i) scanf("%lld",&a[i]);
    build(1,N,1);
    while(M--){
        int f;
        scanf("%d",&f);
        if(f == 1){
            ll L,R;
            scanf("%lld%lld",&L,&R);
            printf("%lld\n",query(L,R,1,N,1));
        }
        if(f == 2){
            ll L,R,K;
            scanf("%lld%lld%lld",&L,&R,&K);
            for(ll i = L; i <= R; ++i) update(i,Sum[pos[i-K]],1,N,1);
        }
        if(f == 3){
            ll L,R;
            scanf("%lld%lld",&L,&R);
            for(ll i = L; i <= R; ++i) update(i,a[i],1,N,1);
        }
    }


}
