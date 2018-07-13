#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <stack>
using namespace std;
struct Edge{
	int to,next;
};
Edge edges[100000];
int pos[100000];
int n,m;
int scc[100000];
int cnt;
int pre[100000];
int lowlink[100000];
int time;

void addedge(int from,int to){
	cnt++;
	edges[cnt]=(Edge){to,pos[from]};
	pos[from]=cnt;
}
stack<int> q;
void init(){
	freopen("1.in","r",stdin);
	memset(edges,0,sizeof(edges));
	memset(pos,0,sizeof(pos));
	memset(scc,0,sizeof(scc));
	memset(pre,0,sizeof(pre));
	memset(lowlink,0,sizeof(lowlink));
	cnt=0;
	time =0;
	scanf("%d%d",&n,&m);
	for(int i=1,from,to;i<=m;i++){
		scanf("%d%d",&from,&to);
		addedge(from,to);
	}
	memset(scc,0,sizeof(scc));
}
void tarjan(int v){
	q.push(v);
	time++;
	pre[v]=lowlink[v]=time;
	int x=pos[v];
	while(x){
		if(!scc[edges[x].to]){
			if(!pre[edges[x].to]){
				tarjan(edges[x].to);
				lowlink[v]=min(lowlink[v],lowlink[edges[x].to]);
			}else{
				lowlink[v]=min(lowlink[v],pre[edges[x].to]);
			}
		}
		x=edges[x].next;
	}
	if(lowlink[v]==pre[v]){
		int x=q.top();
		q.pop();
		while(x!=v){
			scc[x]=v;
			x=q.top();
			q.pop();
		}
		scc[v]=v;
	}
}
int main() {
	init();
	while(!q.empty()) q.pop();
	for(int i=1;i<=n;i++){
		if(!scc[i]) tarjan(i);
	}
	for(int i=1;i<=n;i++){
		printf("%d",scc[i]);
	}
	return 0;
}
