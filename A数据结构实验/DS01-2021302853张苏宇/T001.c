#include <stdlib.h>
#include <stdio.h>


int main() {
	int i = 0, j = 0, k = 0, l = 0, m, n;
	int a[20] = {0}, b[20] = {0}, c[40] = {0};
	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		scanf("%d", &a[i]);
	}
	scanf("%d", &m);
	for (i = 0; i < m; i++) {
		scanf("%d", &b[i]);
	}
	while (l < n || j < m) {
		if (l == n)
			c[k++] = b[j++];
		else if (j == m)
			c[k++] = a[l++];
		else if (a[l] <= b[j])
			c[k++] = a[l++];
		else
			c[k++] = b[j++];

	}
	int s = m + n;
	for (i = 0; i < s; i++)
		printf("%d\n", c[i]);
	return 0;


}