#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;
typedef struct List {
    ElemType *eleArr;
    int capacity;
} *ArrayList;

void createArr(ArrayList list, int capacity) {
    list->capacity = capacity;
    list->eleArr = (ElemType *) malloc(sizeof(ElemType) * capacity);
}

void Combine(ArrayList A, ArrayList B, ArrayList C) {
    int index_a = 0, index_b = 0, index_c = 0;
    while (index_a < A->capacity && index_b < B->capacity) {
        /* 比较a b 数组中的元素，将较小的存入c 数组，并将下标+1 */
        if (A->eleArr[index_a] < B->eleArr[index_b]) {
            C->eleArr[index_c] = A->eleArr[index_a];
            index_a++;
            index_c++;
        } else {
            C->eleArr[index_c] = B->eleArr[index_b];
            index_b++;
            index_c++;
        }
    }

    /* 将数组a或b中剩余的元素存入c中 */
    while (index_a < A->capacity) {
        C->eleArr[index_c] = A->eleArr[index_a];
        index_a++;
        index_c++;
    }
    while (index_b < B->capacity) {
        C->eleArr[index_c] = B->eleArr[index_b];
        index_b++;
        index_c++;
    }
}

int main() {
    int size_a;
    scanf("%d", &size_a);
    struct List A;
    createArr(&A, size_a);
    for (int i = 0; i < size_a; ++i)
        scanf("%d", &A.eleArr[i]);

    int size_b;
    scanf("%d", &size_b);
    struct List B;
    createArr(&B, size_b);
    for (int i = 0; i < size_b; ++i)
        scanf("%d", &B.eleArr[i]);

    struct List C;
    createArr(&C, size_a + size_b);

    /* 合并两个数组到新的数组C */
    Combine(&A, &B, &C);

    /* 输出新的数组C; */
    for (int i = 0; i < size_a + size_b; ++i)
        printf("%d ", C.eleArr[i]);

    scanf("%d", &size_a);
}