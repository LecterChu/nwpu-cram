#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <iostream>

using namespace std;

int map[105][105]; // the path len
int path[105][105]; // the path
int n, m; //the number of node and vertex pair

//递归输出，输出u,path[u][v] 之间最短路，然后输出 path[u][v],v之间的最短路
void PrintPath(int u, int v) {
	int k = path[u][v];
	if (path[u][v] == -1)
		return ;
	PrintPath(u, k);
	printf("%d\n", k);
	PrintPath(k, v);
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			scanf("%d", &map[i][j]);
			path[i][j] = -1;
		}
	}

	//floyed算法是每次判断一下用k来做中转点的时候，是否能够使得i，j之间的路径最短
	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (i != j && j != k && i != k) {
					if (map[i][j] > map[i][k] + map[k][j]) {
						map[i][j] = map[i][k] + map[k][j];
						path[i][j] = k;
					}
				}
			}
		}
	}
	scanf("%d", &m);
	int u, v;
	for (int i = 0; i < m; i++) {
		scanf("%d%d", &u, &v);
		printf("%d\n", u);
		PrintPath(u, v);
		printf("%d\n", v);
	}
	return 0;
}