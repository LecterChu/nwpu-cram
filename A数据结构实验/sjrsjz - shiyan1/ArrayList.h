#ifndef ARRAYLIST_H
#define ARRAYLIST_H

#include <stdlib.h>

// 定义线性表结构体
#define DECLARE_ARRAYLIST(T) \
    typedef struct { \
        T* data; \
        int size; \
        int capacity; \
    } ArrayList_##T;

// 初始化线性表
#define ARRAYLIST_INIT(T, list) \
    do { \
        (list).data = NULL; \
        (list).size = 0; \
        (list).capacity = 0; \
    } while (0)

// 销毁线性表
#define ARRAYLIST_DESTROY(T, list) \
    do { \
        free((list).data); \
        (list).data = NULL; \
        (list).size = 0; \
        (list).capacity = 0; \
    } while (0)

// 获取线性表大小
#define ARRAYLIST_SIZE(T, list) ((list).size)

// 获取线性表容量
#define ARRAYLIST_CAPACITY(T, list) ((list).capacity)

// 判断线性表是否为空
#define ARRAYLIST_IS_EMPTY(T, list) ((list).size == 0)

// 在线性表末尾添加元素
#define ARRAYLIST_ADD(T, list, element) \
    do { \
        if ((list).size == (list).capacity) { \
            (list).capacity = ((list).capacity == 0) ? 1 : (list).capacity * 2; \
            (list).data = (T*)realloc((list).data, sizeof(T) * (list).capacity); \
        } \
        (list).data[(list).size++] = (element); \
    } while (0)

// 获取线性表指定位置的元素
#define ARRAYLIST_GET(T, list, index) ((list).data[(index)])

// 设置线性表指定位置的元素
#define ARRAYLIST_SET(T, list, index, element) ((list).data[(index)] = (element))

// 删除线性表指定位置的元素
#define ARRAYLIST_REMOVE(T, list, index) \
    do { \
        if ((index) >= 0 && (index) < (list).size) { \
            for (int i = (index); i < (list).size - 1; i++) { \
                (list).data[i] = (list).data[i + 1]; \
            } \
            (list).size--; \
        } \
    } while (0)

#endif /* ARRAYLIST_H */