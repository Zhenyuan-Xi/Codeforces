
/*

Your friend is developing a computer game. He has already decided how the game world should look like — 
it should consist of n locations connected by m two-way passages. 
The passages are designed in such a way that it should be possible to get from any location to any other location.

Of course, some passages should be guarded by the monsters. 
Some crucial passages will be guarded by really fearsome monsters, requiring the hero to prepare for battle and 
designing his own tactics of defeating them (commonly these kinds of monsters are called bosses). 
And your friend wants you to help him place these bosses.

The game will start in location s and end in location t, but these locations are not chosen yet. 
After choosing these locations, your friend will place a boss in each passage 
such that it is impossible to get from s to t without using this passage. 
Your friend wants to place as much bosses as possible (because more challenges means more fun, right?), 
so he asks you to help him determine the maximum possible number of bosses, considering that any location can be chosen as s or as t.

Input
The first line contains two integers n and m (2≤n≤3⋅105, n−1≤m≤3⋅105) — the number of locations and passages, respectively.
Then m lines follow, each containing two integers x and y (1≤x,y≤n, x≠y) describing the endpoints of one of the passages.
It is guaranteed that there is no pair of locations directly connected by two or more passages, 
and that any location is reachable from any other location.

Output
Print one integer — the maximum number of bosses your friend can place, considering all possible choices for s and t.

Examples
input
5 5
1 2
2 3
3 1
4 1
5 2
output
2

input
4 3
1 2
4 3
3 2
output
3

题意：无向图，任意两点都要能连通，则存在一些必经的边为关键边，找一条路径，使得其关键边最多，输出关键边的数量

解法：若几个节点之间存在环，则这个环的任意一条边都不是关键边，用Tarjan算法缩点，重新建图得到树图，该树的直径即为关键边的数量
      
            _____________                      _______
           |             |                    |       |           1
      1 —— 2 ——— 3   4   5  将1,2,3缩点，得到  1   4   5  即为    /  \    求树的直径为2
      ||_________|   |                        |___|            4     5
      |______________|
      
Tarjan缩点：即为Tarjan算法求强连通分量，在无向图中无需vis[]标记当前节点是否in stack
强连通分量：在有向图G中，如果两个顶点u,v之间有一条从u到v的有向路径，同时还有一条从v到u的有向路径，则两个顶点强连通
           如果有向图G的每两个顶点都强连通，则G为强连通图
           有向图中的极大强连通子图，称为强连通分量(strongly connected components)
Tarjan算法：基于深度优先搜索，搜索时，把当前搜索树中未处理的节点加入一个堆栈，回溯时可以判断栈顶到栈中的节点是否为一个强连通分量           

*/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN=600060;

struct node{
    int to,next;
}adj[MAXN];
int head[MAXN],tot;  // 链式前向星建原图
vector<int>G[MAXN];  // 缩点后的新图

int dfn[MAXN];  // 表示节点在DFS时的次序编号，即为时间戳
int low[MAXN];  // 表示该节点及其子节点能够回溯到的最小dfn次序编号
int depth;  // 表示DFS深度，即为时间戳
int st[MAXN],top;  // 表示栈
int scc[MAXN],cnt;  // 记录强连通分量结果
int dia[MAXN];  // 记录当前树的各节点的深度，即可得到树的直径

void init(){
    tot=1;
    depth=top=cnt=0;
    memset(head,-1,sizeof(head));
    memset(scc,0,sizeof(scc));
    memset(dfn,0,sizeof(dfn));
    memset(dia,0,sizeof(dia));
}

void addEdge(int u,int v){
    adj[tot].next=head[u];
    adj[tot].to=v;
    head[u]=tot++;
}

void tarjan(int u,int fa){
    dfn[u]=low[u]=++depth;  // 初始化当前时间戳
    st[++top]=u;  // 入栈，若为有向图需要新增vis[]来记录已访问过的节点，vis[u]=true;
    for(int i=head[u];~i;i=adj[i].next){
        int v=adj[i].to;
        if(v==fa) continue;  // 避免重边
        if(!dfn[v]){  // 未访问过节点v，从节点v开始DFS
            tarjan(v,u);
            low[u]=min(low[u],low[v]);  // 更新low[u]，因为节点v是节点u的子节点
        }else low[u]=min(low[u],dfn[v]);  // 更新low[u]，同理，有向图中先判断是否已在栈中，if(vis[v])
    }
    if(low[u]==dfn[u]){  // 若发现节点u及其子节点都不能回溯到dfn次序更小的节点，则节点u及其子节点构成一个强连通分量
        cnt++;
        while(true){
            int x=st[top--];
            scc[x]=cnt;  // 将栈中该强连通分量的节点都打上对应的scc标记
            if(x==u) break;
        }
    }
}

void dfs(int u,int fa){
    dia[u]=dia[fa]+1;
    for(int i=0;i<G[u].size();++i){
        if(G[u][i]!=fa) dfs(G[u][i],u);
    }
}

int main(){
    int n,m,u,v,i,j;
    scanf("%d%d",&n,&m);
    init();
    for(i=0;i<m;++i){
        scanf("%d%d",&u,&v);
        addEdge(u,v);
        addEdge(v,u);
    }
    tarjan(1,0);  // tarjan缩点
    for(i=1;i<=n;++i){
        for(j=head[i];~j;j=adj[j].next){
            if(scc[i]!=scc[adj[j].to]){
                G[scc[i]].push_back(scc[adj[j].to]);  // 根据缩点后的标记重新建图
            }
        }
    }
    dfs(1,0);  // 从任意点出发初始化当前树各点的深度
    int S=0,ans=0;
    for(i=1;i<=cnt;++i) if(dia[i]>dia[S]) S=i;  // 寻找当前树中最深的节点
    dfs(S,0);  // 从最深的节点出发，即可得到最大直径
    for(i=1;i<=cnt;++i) ans=max(ans,dia[i]-1);
    printf("%d\n",ans);
}


