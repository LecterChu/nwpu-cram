#include <stdio.h>

int main(void) {
    long a[2] = {956, 80}, b[2] = {57121, 25}, i = 0, j, k, p, q, r, s = 2, t, u, v, N, M = 10000;
    printf("%9cMachin%6cpi=16arctan(1/5)-4arctan(1/239)\nPlease input a number.\n", 32, 32);
    scanf("%ld", &N);
    long N0 = N;
    N = N / 4 + 3;
    long *pi = malloc(sizeof(long) * N), *e = malloc(sizeof(long) * N);
    while (i < N)
        pi[i++] = 0;
    while (--s + 1) {
        for (*e = a[k = s], i = N; --i;)
            e[i] = 0;
        for (q = 1; j = i - 1, i < N; e[i] ? 0 : ++i, q += 2, k = !k)
            for (r = v = 0; ++j < N; pi[j] += k ? u : -u)
                u = (t = v * M + (e[j] = (p = r * M + e[j]) / b[s])) / q, r = p % b[s], v = t % q;
    }
    while (--i){
        (pi[i] = (t = pi[i] + s) % M) < 0 ? (pi[i] += M, s = t / M - 1) : (s = t / M);
    }
    printf("3.");
    for (++i; i < N - 2; ++i)
        printf("%04ld", pi[i]);
    switch ((N0 - 4) % 4)
    {
    case 0:
        break;
    case 1:
        printf("%01ld", pi[N-2] / 1000);
        break;
    case 2:
        printf("%02ld", pi[N-2] / 100);
        break;
    case 3:
        printf("%03ld", pi[N-2] / 10);
        break;
    }

    free(pi),
    free(e);
    return 0;
}