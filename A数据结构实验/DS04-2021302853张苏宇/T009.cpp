#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <iostream>

using namespace std;

const int maxn = 1000;
const int inf = 10000;
int n;
int map[maxn][maxn];
int dis[maxn];
bool vis[maxn];
int pre[maxn];
int u, v;

void dijkstra(int s) {
	//s start
	for (int i = 0; i < n; i++) {
		dis[i] = inf;
		vis[i] = false;
	}
	//用dis，vis分别标记s点到到节点i的最短路径长度，以及节点i是否用过
	int u = s;
	dis[u] = 0;
	//对其余T中顶点的距离值进行修改：若加进W作中间顶点，从V0到Vi的距离值缩短，则修改此距离值 [1]
	while (!vis[u]) {
		vis[u] = true;
		for (int i = 0; i < n; i++) {
			if (!vis[i] && dis[i] > dis[u] + map[u][i]) {
				dis[i] = map[u][i] + dis[u];
				pre[i] = u;
			}
		}
		int tag = inf;
		for (int i = 0; i < n; i++) {
			if (!vis[i] && dis[i] < tag) {
				tag = dis[i];
				u = i;
			}
		}
	}
}

void PrintPath(int u, int v) {
	//这个函数利用递归的思想，从尾部v一直向前递归，到达u后，向后递归输出最短路径
	if (u == v) {
		printf("%d\n", u);
		return ;
	}
	PrintPath(u, pre[v]);
	printf("%d\n", v);
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%d", &map[i][j]);
		}
	}
	scanf("%d%d", &u, &v);
	dijkstra(0);
	dijkstra(u);
	PrintPath(u, v);
	return 0;
}