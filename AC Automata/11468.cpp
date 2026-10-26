#include<cstdio>
#include<cstring>
#include<queue>
#include<string>
using namespace std;

const int SIGMA_SIZE = 62+2;
const int MAXNODE = 20*20+100; 

int idx[256], n;
double prob[SIGMA_SIZE];

struct AhoCorasickAutomata {
  int ch[MAXNODE][SIGMA_SIZE];
  int f[MAXNODE];    
  int match[MAXNODE]; 
  int sz; 
  void init() {
    sz = 1;
    memset(ch[0], 0, sizeof(ch[0]));
  }

  void insert(char *s) {
    int u = 0, n = strlen(s);
    for(int i = 0; i < n; i++) {
      int c = idx[s[i]];
      if(!ch[u][c]) {
        memset(ch[sz], 0, sizeof(ch[sz]));
        match[sz] = 0;
        ch[u][c] = sz++;
      }
      u = ch[u][c];
    }
    match[u] = 1;
  }

  void getFail() {
    queue<int> q;
    f[0] = 0;
    for(int c = 0; c < SIGMA_SIZE; c++) {
      int u = ch[0][c];
      if(u) { f[u] = 0; q.push(u); }
    }
    while(!q.empty()) {
      int r = q.front(); q.pop();
      for(int c = 0; c < SIGMA_SIZE; c++) {
        int u = ch[r][c];
        if(!u) { ch[r][c] = ch[f[r]][c]; continue; }
        q.push(u);
        int v = f[r];
        while(v && !ch[v][c]) v = f[v];
        f[u] = ch[v][c];
        match[u] |= match[f[u]];
      }
    }
  }
};

AhoCorasickAutomata ac;

double d[MAXNODE][105];
int vis[MAXNODE][105];

double getProb(int u, int L) {
  if(!L) return 1.0;
  if(vis[u][L]) return d[u][L];
  vis[u][L] = 1;
  double &ans = d[u][L];
  ans = 0.0;
  for(int i = 0; i < n; i++)
    if(!ac.match[ac.ch[u][i]]) ans += prob[i] * getProb(ac.ch[u][i], L-1);
  return ans;
}

char s[30][30];

int main() {
  int T;
  // freopen("11468.in","r",stdin);
  // freopen("11468.out","w",stdout);
  memset(idx, 0, sizeof(idx));    
  scanf("%d", &T);
  for(int kase = 1; kase <= T; kase++) {
    int k, L;
    scanf("%d", &k);
    for(int i = 0; i < k; i++) scanf("%s", s[i]);
    scanf("%d", &n);
    for(int i = 0; i < n; i++) {
      char ch[9];
      scanf("%s%lf", ch, &prob[i]);
      idx[ch[0]] = i;
    }
    ac.init();
    for(int i = 0; i < k; i++) ac.insert(s[i]);
    ac.getFail();
    scanf("%d", &L);
    memset(vis, 0, sizeof(vis));
    printf("Case #%d: %.6lf\n", kase, getProb(0, L));
  }
  return 0;
}
