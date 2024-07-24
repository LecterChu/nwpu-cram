#include <stdio.h>
#include <stdlib.h>
void main()
{
    int A_n, B_n;
    scanf("%d", &A_n);
    int *A = (int *)malloc(sizeof(int) * A_n);
    for (int i = 0; i < A_n; i++)
        scanf("%d", &A[i]);
    scanf("%d", &B_n);
    int *B = (int *)malloc(sizeof(int) * B_n);
    for (int i = 0; i < B_n; i++)
        scanf("%d", &B[i]);
    int i = 0, j = 0;
    int size = A_n + B_n;
    for (int k = 0; k < size; k++)
    {
        if (A[i] < B[j] && i < A_n)
        {
            printf("%d", A[i]);
            i++;
        }
        else
        {
            printf("%d", B[j]);
            j++;
        }
        if (k < size - 1)
        {
            printf("\n");
        }
    }
    free(A);
    free(B);
}