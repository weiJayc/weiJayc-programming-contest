#include<cstdio>
#include<iostream>
#include<cstdlib>
using namespace std;

const int maxn = 100000 + 10;
int T,n,m,maxh[maxn<<1],setnode[maxn<<1],ans;
struct node {
    int l, r, h;
}a[maxn];

void pushup(int node) {
    maxh[node] = max(maxh[node<<1], maxh[node<<1|1]);
}
void build(int left, int right, int node) {
    int mid = (left + right) >> 1;
    maxh[node] = 0;
    setnode[node] = 0;
    if(left == right) return ;
    build(left, mid, node<<1);
    build(mid+1, right, node<<1|1);
}
void pushdown(int left, int right, int node) {
    if(setnode[node]) {
        setnode[node<<1] = setnode[node<<1|1] = setnode[node];
        maxh[node<<1] = maxh[node<<1|1] = maxh[node];
        setnode[node] = 0;
    }
}
void update(int L, int R, int h, int left, int right, int node) {
    int mid = (left + right) >> 1;
    if(setnode[node] && maxh[node] > h) return ;
    if(L <= left && right <= R) {
        if(maxh[node] <= h) {
            maxh[node] = h;
            setnode[node] = h;
            ans += right - left + 1;
            return ;
        }
    }
    if(left == right) return ;
    if (R<left||right<L) return; 
    pushdown(left, right, node);
    if(L <= mid) update(L, R, h, left, mid, node<<1);
    if(mid < R)  update(L, R, h, mid+1, right, node<<1|1);
    pushup(node);
}
int main() {
	// freopen("4108.in", "r", stdin);
    // freopen("4108.out","w",stdout);		
    while(~scanf("%d",&T) && T) {
        while(T--) {
            scanf("%d",&n);
            int datamaxx = 0;
            for(int i=0;i<n;i++) {
                scanf("%d%d%d",&a[i].l,&a[i].r,&a[i].h);
                datamaxx = max(datamaxx, a[i].r);
            }
            build(1, datamaxx, 1);
            ans = 0;
            for(int i=0;i<n;i++) {
                update(a[i].l, a[i].r-1, a[i].h, 1, datamaxx, 1);
            }
            printf("%d\n",ans);
        }
    }
    return 0;
}
