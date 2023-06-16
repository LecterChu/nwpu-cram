#include <stdlib.h>
#include <stdio.h>


int main()
{
	int i, j = 0, k=0, m, n,s;
	int a[20], b[20], c[40];
	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		scanf("%d", &a[i]);
	}
	scanf("%d", &m);
	for (i = 0; i < m; i++) {
		scanf("%d", &b[i]);
	}
	i=0;
	while(i<n&&j<m)
    {
        if(a[i]<=b[j])
        {
            c[k]=a[i];
            i++;k++;
        }
        else
        {
            c[k]=b[j];
            j++;k++;
        }
    }
    while(i<n)
    {
        c[k]=a[i];
        k++;i++;
    }
    while(j<m)
    {
        c[k]=b[j];
        k++;j++;
    }
    s=m+n;
    for(i=0;i<s;i++) printf("%d\n",c[i]);
}
