#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct node
{
    unsigned int data; // 0~999999999
    struct node *next;
    struct node *prev;
} node;
typedef struct
{
    struct node *head;
    struct node *curr_pos;
    size_t curr_index;
    size_t size;
    int sign;
    int exp; // 10^exp
} inf_float; // considered it smaller than 1.0

void init(inf_float *);
void destroy(inf_float *);
void append(inf_float *, unsigned int);
node *getLocation(inf_float *, intptr_t);
void insert(inf_float *, intptr_t, unsigned int);
void insert_head(inf_float *, unsigned int);

void LoadFromString(inf_float *, const char *);
void LoadFromStringN(inf_float *, const char *);
void FloatToString(inf_float *, char *);
void FloatToStringN(inf_float *, char *);
void FloatToStringNoExp(inf_float *, char *, size_t);
inf_float *inf_float_copy(inf_float *);
void quickNormalizeSelf(inf_float *);
void quickRShift10(inf_float *, size_t);


int compare(inf_float *, inf_float *);
int compareN(inf_float *, inf_float *);

inf_float *add(inf_float *, inf_float *);
inf_float *addN(inf_float *, inf_float *);
inf_float *substract(inf_float *, inf_float *);
inf_float *substractN(inf_float *, inf_float *);
inf_float *substractN_NoExp_NoSign(inf_float *, inf_float *);
inf_float *multiply(inf_float *, inf_float *);
inf_float *multiply_int(inf_float *, unsigned int);
inf_float *multiply_int_carry(inf_float *, unsigned int, unsigned int *);
inf_float *divide(inf_float *, inf_float *, size_t);
inf_float *divide_int(inf_float *, int, size_t);
inf_float *arcsin(inf_float *, size_t);
inf_float *PI(size_t, size_t, size_t);
inf_float *cubic_root(inf_float *, size_t, size_t);
inf_float *sqr_root(inf_float *, size_t, size_t);

void init(inf_float *a)
{
    a->head = NULL;
    a->curr_pos = NULL;
    a->curr_index = 0;
    a->size = 0;
    a->sign = 1;
    a->exp = 0;
}
void destroy(inf_float *a)
{
    if (a->head == NULL)
    {
        return;
    }
    node *temp = a->head;
    a->head = NULL;
    do
    {
        node *next = temp;
        temp = temp->next;
        free(next);
    } while (temp);
}
void append(inf_float *a, unsigned int data)
{
    // insert at tail
    node *new_node = (node *)malloc(sizeof(node));
    if (a->size == 0)
    {
        a->head = new_node;
        new_node->next = NULL;
        new_node->prev = NULL;
        new_node->data = data;
        a->curr_pos = new_node;
        a->curr_index = 0;
        a->size = 1;
        return;
    }
    new_node->data = data;
    new_node->next = NULL;
    new_node->prev = getLocation(a, a->size - 1);
    new_node->prev->next = new_node;
    a->size++;
}
node *getLocation(inf_float *a, intptr_t pos)
{
    if (pos < 0 || pos >= a->size)
    {
        return NULL;
    }
    if (a->size && (!a->curr_index || !a->curr_pos))
    {
        a->curr_pos = a->head;
        for (intptr_t i = 0; i < pos && a->curr_pos; i++)
        {
            a->curr_pos = a->curr_pos->next;
        }
        a->curr_index = pos;
        return a->curr_pos;
    }
    intptr_t offset = pos - a->curr_index;
    if (offset == 0)
    {
        return a->curr_pos;
    }
    else if (offset > 0)
    {
        for (size_t i = 0; i < offset && a->curr_pos && a->curr_pos->next; i++)
        {
            a->curr_pos = a->curr_pos->next;
        }
        a->curr_index = pos;
        return a->curr_pos;
    }
    else
    {
        for (size_t i = 0; i < -offset && a->curr_pos && a->curr_pos->prev; i++)
        {
            a->curr_pos = a->curr_pos->prev;
        }
        a->curr_index = pos;
        return a->curr_pos;
    }
}

void insert(inf_float *a, intptr_t pos, unsigned int data)
{
    a->curr_pos = NULL;
    node *location = getLocation(a, pos);
    if (location == NULL)
    {
        return;
    }
    node *new_node = (node *)malloc(sizeof(node));
    if (a->size == 0)
    {
        a->head = new_node;
        new_node->next = NULL;
        new_node->prev = NULL;
        new_node->data = data;
        a->curr_pos = new_node;
        a->curr_index = 0;
        a->size = 1;
        return;
    }
    new_node->data = data;
    new_node->next = location;
    new_node->prev = location->prev;
    location->prev->next = new_node;
    location->prev = new_node;
    a->size++;
}

void insert_head(inf_float *a, unsigned int data)
{
    // insert at head
    a->curr_pos = NULL;
    node *new_node = (node *)malloc(sizeof(node));
    if (a->size == 0)
    {
        a->head = new_node;
        new_node->next = NULL;
        new_node->prev = NULL;
        new_node->data = data;
        a->curr_pos = new_node;
        a->curr_index = 0;
        a->size = 1;
        return;
    }
    new_node->data = data;
    new_node->next = a->head;
    new_node->prev = NULL;
    a->head->prev = new_node;
    a->head = new_node;
    a->size++;
}
inf_float *inf_float_copy(inf_float *a)
{
    inf_float *result = (inf_float *)malloc(sizeof(inf_float));
    init(result);
    for (size_t i = 0; i < a->size; i++)
    {
        node *A = getLocation(a, i);
        append(result, A->data);
    }
    result->sign = a->sign;
    result->exp = a->exp;
    return result;
}

void quickRShift10(inf_float *a, size_t k)
{
    size_t bufSize = 9 * a->size + 1 + k;
    int sign = a->sign;
    char *buf = malloc(bufSize);
    int k0 = k;
    while (k0--)
    {
        *(buf + k0) = '0';
    }
    int exp = a->exp;
    FloatToStringN(a, buf + k);
    destroy(a);
    LoadFromStringN(a, buf);
    free(buf);
    a->sign = sign;
    a->exp = exp;
}
void quickNormalizeSelf(inf_float *a)
{
    if (a && a->head && a->head->data > 99999999)
        return;
    size_t bufSize = 9 * a->size + 1;
    int sign = a->sign;
    char *buf = malloc(bufSize);
    int exp = a->exp;
    FloatToStringN(a, buf);
    size_t start = 0;
    while (buf[start] == '0')
    {
        start++;
        exp--;
    }
    bufSize--;
    while (bufSize && buf[--bufSize] == '0')
    {
        buf[bufSize] = '\0';
    }

    destroy(a);
    LoadFromStringN(a, buf + start);
    free(buf);
    a->sign = sign;
    a->exp = exp;
}
inf_float *add(inf_float *a, inf_float *b)
{
    inf_float *result;
    if (a->sign == b->sign)
    {
        result = addN(a, b);
        result->sign = a->sign;
    }
    else
    {
        result = substractN(a, b);
        result->sign *= a->sign;
    }
    return result;
}
inf_float *addN(inf_float *a_, inf_float *b_)
{
    inf_float *a = a_, *b = b_;

    int exp_diff = a->exp - b->exp;
    int max_exp = a->exp > b->exp ? a->exp : b->exp;
    if (exp_diff > 0)
    {
        b = inf_float_copy(b_);
        quickRShift10(b, exp_diff);
    }
    else if (exp_diff < 0)
    {
        a = inf_float_copy(a_);
        quickRShift10(a, -exp_diff);
    }

    inf_float *result = (inf_float *)malloc(sizeof(inf_float));
    init(result);
    unsigned int carry = 0;
    size_t size = a->size > b->size ? a->size : b->size;

    for (intptr_t i = (intptr_t)size - 1; i >= 0; i--)
    {
        node *A = getLocation(a, i);
        node *B = getLocation(b, i);
        unsigned int sum = 0;
        if (A)
            sum += A->data;
        if (B)
            sum += B->data;
        sum += carry;
        carry = sum / 1000000000;
        insert_head(result, sum % 1000000000);
    }
    result->exp = max_exp;
    if (carry)
    {
        insert_head(result, carry);
        result->exp += 9;
    }
    if (exp_diff > 0)
    {
        destroy(b);
    }
    else if (exp_diff < 0)
    {
        destroy(a);
    }
    return result;
}
inf_float *substract(inf_float *a, inf_float *b)
{
    inf_float *result;
    if (a->sign == b->sign)
    {
        result = substractN(a, b);
        result->sign *= a->sign;
    }
    else
    {
        result = addN(a, b);
        result->sign = a->sign;
    }
    return result;
}
inf_float *substractN(inf_float *a_, inf_float *b_)
{
    inf_float *a0 = a_;
    inf_float *b0 = b_;
    inf_float *result = (inf_float *)malloc(sizeof(inf_float));
    init(result);
    unsigned int carry = 0;
    int exp_diff = a_->exp - b_->exp;
    int max_exp = a_->exp > b_->exp ? a_->exp : b_->exp;

    if (exp_diff > 0)
    {
        b0 = inf_float_copy(b_);
        quickRShift10(b0, exp_diff);
    }
    else if (exp_diff < 0)
    {
        a0 = inf_float_copy(a_);
        quickRShift10(a0, -exp_diff);
    }
    inf_float *a = a0;
    inf_float *b = b0;
    if (compareN(a, b) < 0)
    {
        inf_float *temp = a;
        a = b;
        b = temp;
        result->sign = -1;
    }
    size_t size = a->size > b->size ? a->size : b->size;
    for (intptr_t i = (intptr_t)size - 1; i >= 0; i--)
    {
        node *A = getLocation(a, i);
        node *B = getLocation(b, i);
        long long int sum = 0;
        if (A)
            sum += A->data;
        if (B)
            sum -= B->data;
        sum -= carry;
        if (sum < 0)
        {
            sum += 1000000000;
            carry = 1;
        }
        else
        {
            carry = 0;
        }
        insert_head(result, (unsigned int)(sum % 1000000000));
    }
    result->exp = max_exp;
    if (exp_diff > 0)
    {
        destroy(b0);
    }
    else if (exp_diff < 0)
    {
        destroy(a0);
    }
    return result;
}
inf_float *substractN_NoExp_NoSign(inf_float *a, inf_float *b)
{
    inf_float *result = (inf_float *)malloc(sizeof(inf_float));
    init(result);
    unsigned int carry = 0;
    size_t size = a->size > b->size ? a->size : b->size;
    for (intptr_t i = (intptr_t)size - 1; i >= 0; i--)
    {
        node *A = getLocation(a, i);
        node *B = getLocation(b, i);
        long long int sum = 0;
        if (A)
            sum += A->data;
        if (B)
            sum -= B->data;
        sum -= carry;
        if (sum < 0)
        {
            sum += 1000000000;
            carry = 1;
        }
        else
        {
            carry = 0;
        }
        insert_head(result, (unsigned int)(sum));
    }
    return result;
}
inf_float *multiply_int_carry(inf_float *a, unsigned int b, unsigned int *carry_)
{
    inf_float *result = (inf_float *)malloc(sizeof(inf_float));
    init(result);
    unsigned int carry = 0;
    for (intptr_t i = (intptr_t)a->size - 1; i >= 0; i--)
    {
        node *A = getLocation(a, i);
        unsigned long long int product = (unsigned long long int)A->data * (unsigned long long int)b + (unsigned long long int)carry;
        carry = (unsigned int)(product / 1000000000);
        insert_head(result, (unsigned int)(product % 1000000000));
    }
    *carry_ = carry;
    return result;
}

inf_float *multiply_int(inf_float *a, unsigned int b)
{
    inf_float *result = (inf_float *)malloc(sizeof(inf_float));
    init(result);
    unsigned int carry = 0;
    for (intptr_t i = (intptr_t)a->size - 1; i >= 0; i--)
    {
        node *A = getLocation(a, i);
        unsigned long long int product = (unsigned long long int)A->data * (unsigned long long int)b + (unsigned long long int)carry;
        carry = (unsigned int)(product / 1000000000);
        insert_head(result, (unsigned int)(product % 1000000000));
    }
    if (carry)
    {
        insert_head(result, carry);
    }
    return result;
}

inf_float *multiply(inf_float *a, inf_float *b)
{
    inf_float *result = (inf_float *)malloc(sizeof(inf_float));
    init(result);
    if (a->size == 0 || b->size == 0)
    {
        return result;
    }
    if (a->size == 1 && a->head && a->head->data == 0 || b->size == 1 && b->head && b->head->data == 0)
    {
        result->sign = 1;
        append(result, 0);
        return result;
    }
    size_t k = 0;
    size_t sumLen = a->size + b->size;
    for (intptr_t i = (intptr_t)b->size - 1; i >= 0; i--)
    {
        node *B = getLocation(b, i);
        inf_float *temp = multiply_int(a, B->data);

        for (size_t j = 0; j < k; j++)
        {
            append(temp, 0);
        }
        intptr_t D = (intptr_t)sumLen - temp->size;
        for (size_t j = 0; j < D; j++)
        {
            insert_head(temp, 0);
        }

        k++;
        inf_float *R = add(result, temp);
        destroy(result);
        result = R;
        destroy(temp);
    }
    intptr_t D = (intptr_t)sumLen - result->size;
    for (intptr_t i = 0; i < D; i++)
    {
        insert_head(result, 0);
    }
    result->sign = a->sign * b->sign;
    result->exp = a->exp + b->exp;
    return result;
}

void print_float(inf_float *a)
{
    char str[8192];
    FloatToString(a, str);
    printf("%s\n", str);
}
void print_float_NoExp(inf_float *a, size_t N)
{
    char str[8192];
    FloatToStringNoExp(a, str, N);
    printf("%s\n", str);
}

inf_float *divide(inf_float *a_, inf_float *b_, size_t precision)
{
    // now consider a and b are INT
    inf_float *result = (inf_float *)malloc(sizeof(inf_float));
    init(result);
    // 使用二分法
    inf_float *a = inf_float_copy(a_);
    inf_float *b = inf_float_copy(b_);
    int sign = a_->sign * b_->sign;

    quickNormalizeSelf(a);
    quickNormalizeSelf(b);
    int exp = a->exp - b->exp;
    result->exp = 0;
    int cmp = compareN(a, b);
    exp += cmp <= 0 ? 0 : 9;
    if (cmp < 0)
    {
        insert_head(b, 0);
    }
    // print_float(a);
    // print_float(b);
    inf_float *mod = inf_float_copy(a);
    mod->exp = 0;
    for (size_t i = 0; cmp && i < precision; i++)
    {
        int L = 1000000000;
        int R = 0;
        append(result, 0);
        node *curr = getLocation(result, result->size - 1);
        int M = 0;
        int C = compareN(b, mod);
        if (C > 0)
        {
            curr->data = 0;
            goto label1;
        }
        if (C == 0)
        {
            curr->data = 1;
            M = 1;
            goto label0;
        }
        while (L > R)
        {
            M = (L + R) >> 1;
            curr->data = M;
            if (M == R)
                break;
            unsigned int carry = 0;
            inf_float *temp = multiply_int_carry(b, M, &carry);
            int cmp = 1;
            if (!carry)
            {
                cmp = compareN(temp, mod);
            }
            if (!cmp)
            {
                goto label;
            }
            else if (cmp <= 0)
            {
                R = M;
            }
            else
            {
                L = M;
            }
            destroy(temp);
        }
    label0:
        inf_float *temp = multiply_int(b, M);
        inf_float *t = substractN_NoExp_NoSign(mod, temp);
        destroy(mod);
        mod = t;
    label1:
        insert_head(b, 0);
    }
    if (!cmp)
    {
        append(result, 100000000);
        exp++;
    }
label:
    destroy(a);
    destroy(b);
    result->sign = sign;
    result->exp = exp;
    return result;
}

inf_float *divide_int(inf_float *a, int b, size_t precision)
{
    inf_float *result = (inf_float *)malloc(sizeof(inf_float));
    init(result);
    long long int X = 0;
    size_t i = 0;
    int b0 = b < 0 ? -b : b;
    while (precision--)
    {
        int S = 0;
        node *A=getLocation(a,i++);
        if(A)
            S=A->data;
        long long int Y = X * 1000000000 + S;
        append(result, Y / b0);
        X = Y % b0;
    }
    result->exp = a->exp;
    result->sign = a->sign * (b < 0 ? -1 : 1);
    
    return result;
}

void LoadFromStringN(inf_float *a, const char *buf)
{
    destroy(a);
    init(a);
    unsigned int N = strlen(buf) / 9;
    unsigned int M = strlen(buf) % 9;
    for (unsigned int i = 0; i < N; i++)
    {
        unsigned int num = 0;
        unsigned int E = 1e8;
        for (int j = 0; j < 9; j++)
        {
            num += (unsigned int)(buf[i * 9 + j] - '0') * E;
            E /= 10;
        }
        append(a, num);
    }
    unsigned int num = 0;
    unsigned int E = 1e8;
    for (unsigned int i = 0; i < M; i++)
    {
        num += (unsigned int)(buf[N * 9 + i] - '0') * E;
        E /= 10;
    }
    append(a, num);
}

int getIntFromStr(char *buf, int *offset)
{
    int num = 0;
    if (buf[*offset] == '-')
    {
        (*offset)++;
        return -getIntFromStr(buf, offset);
    }
    while (buf[*offset] >= '0' && buf[*offset] <= '9')
    {
        num = num * 10 + buf[*offset] - '0';
        (*offset)++;
    }
    return num;
}

void LoadFromString(inf_float *a, const char *buf)
{
    destroy(a);
    init(a);
    int exp = 0;
    int offset = 0;
    int exp_offset = 0;
    int start_float = 0;

    if (buf[0] == '-')
    {
        a->sign = -1;
        offset = 1;
    }
    while (buf[offset] == '0' || buf[offset] == '.')
    {
        exp_offset -= start_float;
        start_float = start_float | buf[offset++] == '.';
    }
    size_t size = strlen(buf + offset);
    unsigned int N = size / 9;
    unsigned int M = size % 9;
    for (unsigned int i = 0; i < N && !exp; i++)
    {

        unsigned int num = 0;
        unsigned int E = 1e8;
        for (int j = 0; j < 9; j++)
        {
            switch (buf[i * 9 + j])
            {
            case 'e':;
                int k = 0;
                a->exp = getIntFromStr(buf + i * 9 + j + offset + 1, &k);
                exp = 1;
                goto label;
            case '.':;
                start_float = 1;
                continue;
            }
            num += (unsigned int)(buf[i * 9 + offset + j] - '0') * E;
            E /= 10;
            if (!start_float)
                exp_offset++;
        }
    label:
        append(a, num);
    }
    unsigned int num = 0;
    unsigned int E = 1e8;
    for (unsigned int i = 0; i < M && !exp; i++)
    {
        switch (buf[N * 9 + offset + i])
        {
        case 'e':;
            int k = 0;
            a->exp = getIntFromStr(buf + N * 9 + i + offset + 1, &k);
            exp = 1;
            goto label2;
        case '.':;
            start_float = 1;
            continue;
        }
        num += (unsigned int)(buf[N * 9 + offset + i] - '0') * E;
        E /= 10;
        if (!start_float)
            exp_offset++;
    }
label2:
    if (num)
        append(a, num);
    a->exp += exp_offset;
}

int compareN(inf_float *a, inf_float *b)
{
    size_t size = a->size > b->size ? a->size : b->size;
    for (size_t i = 0; i < size; i++)
    {
        node *A = getLocation(a, i);
        node *B = getLocation(b, i);
        unsigned int numA = 0;
        unsigned int numB = 0;
        if (A)
        {
            numA = A->data;
        }
        if (B)
        {
            numB = B->data;
        }
        if (numA > numB)
        {
            return 1;
        }
        if (numA < numB)
        {
            return -1;
        }
    }
    return 0;
}

int compare(inf_float *a, inf_float *b)
{
    inf_float *A = inf_float_copy(a);
    inf_float *B = inf_float_copy(b);
    quickNormalizeSelf(A);
    quickNormalizeSelf(B);
    if (A->sign > B->sign)
    {
        return 1;
    }
    if (A->sign < B->sign)
    {
        return -1;
    }
    if (A->sign == -1)
    {
        if (A->exp > B->exp)
        {
            return -1;
        }
        if (A->exp < B->exp)
        {
            return 1;
        }
        return -compareN(a, b);
    }
    if (A->exp > B->exp)
    {
        return 1;
    }
    if (A->exp < B->exp)
    {
        return -1;
    }
    return compareN(a, b);
}

void FloatToStringN(inf_float *a, char *buf)
{
    unsigned int N = a->size;
    unsigned int M = a->size * 9;
    size_t offset = 0;
    for (int i = 0; i < N; i++)
    {
        node *A = getLocation(a, i);
        unsigned int num = A->data;
        unsigned int E = 1e8;
        for (unsigned int j = 0; j < 9; j++)
        {
            buf[offset++] = num / E + '0';
            num %= E;
            E /= 10;
        }
    }
    node *A = getLocation(a, N - 1);
    unsigned int num = 0;
    if (A)
    {
        num = A->data;
    }
    unsigned int E = 1e8;
    M %= 9;
    for (unsigned int i = 0; i < M; i++)
    {
        buf[offset++] = num / E + '0';
        num %= E;
        E /= 10;
    }
    buf[offset++] = '\0';
}
void FloatToString(inf_float *a, char *buf)
{
    unsigned int N = a->size;
    unsigned int M = a->size * 9;
    int offset = 0;
    int exp = 0;
    if (a->sign == -1)
    {
        buf[0] = '-';
        offset = 1;
    }
    buf[offset++] = '0';
    buf[offset++] = '.';
    for (int i = 0; i < N; i++)
    {
        node *A = getLocation(a, i);
        unsigned int num = A->data;
        unsigned int E = 1e8;
        for (unsigned int j = 0; j < 9 && (i != N - 1 || num); j++)
        {
            buf[offset++] = num / E + '0';
            num %= E;
            E /= 10;
        }
    }
    while (buf[offset - 1] == '0')
    {
        offset--;
    }
    if (offset == 2)
    {
        buf[1] = '\0';
        return;
    }
    if (a->exp)
    {
        buf[offset++] = 'e';
        int flag = a->exp;
        if (a->exp < 0)
        {
            buf[offset++] = '-';
            flag = -a->exp;
        }
        int k = 1000000000;
        while (k > flag)
        {
            k /= 10;
        }
        while (k)
        {
            buf[offset++] = flag / k + '0';
            flag %= k;
            k /= 10;
        }
    }
    buf[offset] = '\0';
}

void FloatToStringNoExp(inf_float *a, char *buf, size_t N0)
{
    // 输出不带指数的字符串
    inf_float *temp = inf_float_copy(a);
    quickNormalizeSelf(temp);
    unsigned int N = a->size;
    unsigned int M = a->size * 9;
    int offset = 0;
    if (a->sign == -1)
    {
        buf[0] = '-';
        offset = 1;
    }

    if (temp->exp <= 0)
    {
        if (!(N0--))
            goto label;
        buf[offset++] = '0';
        if (!(N0--))
            goto label;
        buf[offset++] = '.';
        for (int i = 0; i < -temp->exp; i++)
        {
            if (!(N0--))
                goto label;
            buf[offset++] = '0';
        }
        for (int i = 0; i < N; i++)
        {
            node *A = getLocation(temp, i);
            if (!A)
                break;
            unsigned int num = A->data;
            unsigned int E = 1e8;
            for (unsigned int j = 0; j < 9 && (i != N - 1 || num); j++)
            {
                if (!(N0--))
                    goto label;
                buf[offset++] = num / E + '0';
                num %= E;
                E /= 10;
            }
        }
    }
    else
    {
        size_t k = a->exp + 1;
        for (int i = 0; i < N; i++)
        {
            node *A = getLocation(temp, i);
            if (!A)
                break;
            unsigned int num = A->data;
            unsigned int E = 1e8;
            for (unsigned int j = 0; j < 9 && (i != N - 1 || num); j++)
            {
                if (k == 1)
                {
                    if (!(N0--))
                        goto label;
                    buf[offset++] = '.';
                }
                if (!(N0--))
                    goto label;
                buf[offset++] = num / E + '0';
                num %= E;
                E /= 10;
                if (k)
                    k--;
            }
        }
    }
label:
    buf[offset] = '\0';
}

inf_float *pow2(inf_float *a)
{
    return multiply(a, a);
}
inf_float *pow3(inf_float *a)
{
    inf_float *temp = multiply(a, a);
    inf_float *ret = multiply(temp, a);
    destroy(temp);
    return ret;
}
inf_float *multiply_single(inf_float *a, int num)
{
    inf_float *num_1 = (inf_float *)malloc(sizeof(inf_float));
    init(num_1);
    append(num_1, num < 0 ? -num : num);
    num_1->exp = 9;
    num_1->sign = num < 0 ? -1 : 1;
    inf_float *ret = multiply(a, num_1);
    destroy(num_1);
    return ret;
}
inf_float *add_single(inf_float *a, int num)
{
    inf_float *num_1 = (inf_float *)malloc(sizeof(inf_float));
    init(num_1);
    append(num_1, num < 0 ? -num : num);
    num_1->exp = 9;
    num_1->sign = num < 0 ? -1 : 1;
    inf_float *ret = add(a, num_1);
    destroy(num_1);
    return ret;
}

inf_float *substract_single_1(inf_float *a, int num)
{
    inf_float *num_1 = (inf_float *)malloc(sizeof(inf_float));
    init(num_1);
    append(num_1, num < 0 ? -num : num);
    num_1->exp = 9;
    num_1->sign = num < 0 ? -1 : 1;
    inf_float *ret = substract(num_1, a);
    destroy(num_1);
    return ret;
}
inf_float *single(int num)
{
    inf_float *num_1 = (inf_float *)malloc(sizeof(inf_float));
    init(num_1);
    append(num_1, num < 0 ? -num : num);
    num_1->exp = 9;
    num_1->sign = num < 0 ? -1 : 1;
    return num_1;
}
void cut_tail(inf_float *a, size_t n)
{
    if (a == NULL || a->size == 0)
    {
        return;
    }
    if (n >= a->size)
    {
        return;
    }
    node *tail = getLocation(a, n);
    a->size = n;
    node *temp = tail->next;
    tail->next = NULL;
    while (temp)
    {
        node *next = temp->next;
        free(temp);
        temp = next;
    }
}
inf_float *cubic_root(inf_float *a, size_t precise, size_t step)
{
    inf_float *result = inf_float_copy(a);
    inf_float *tri = (inf_float *)malloc(sizeof(inf_float));
    init(tri);
    LoadFromString(tri, "3");
    inf_float *temp = NULL;
    while (step--)
    {
        inf_float *sqr = multiply(result, result);
        inf_float *triple = multiply(sqr, result);
        inf_float *A = substract(triple, a);
        inf_float *B = multiply(tri, sqr);
        inf_float *C = divide(A, B, precise);
        quickNormalizeSelf(C);
        temp = substract(result, C);
        destroy(result);
        result = temp;
        destroy(sqr);
        destroy(triple);
        destroy(A);
        destroy(B);
        destroy(C);
        cut_tail(result, precise);
    }
    destroy(tri);
    return result;
}

inf_float *sqr_root(inf_float *a, size_t precise, size_t step)
{
    inf_float *result = inf_float_copy(a);
    inf_float *bi = (inf_float *)malloc(sizeof(inf_float));
    init(bi);
    LoadFromString(bi, "2");
    inf_float *temp = NULL;
    while (step--)
    {
        inf_float *sqr = multiply(result, result);
        inf_float *A = substract(sqr, a);
        inf_float *B = multiply(bi, result);
        inf_float *C = divide(A, B, precise);
        quickNormalizeSelf(C);
        temp = substract(result, C);
        destroy(result);
        result = temp;
        destroy(sqr);
        destroy(A);
        destroy(B);
        destroy(C);
        cut_tail(result, precise);
    }
    destroy(bi);
    return result;
}

inf_float *PI(size_t precise, size_t step, size_t iteration)
{
    // https://www.zhihu.com/question/312520105
    inf_float *result = (inf_float *)malloc(sizeof(inf_float));
    init(result);
    inf_float *num_1 = (inf_float *)malloc(sizeof(inf_float));
    init(num_1);
    LoadFromString(num_1, "1");
    inf_float *num_2 = (inf_float *)malloc(sizeof(inf_float));
    init(num_2);
    LoadFromString(num_2, "2");
    inf_float *num_3 = (inf_float *)malloc(sizeof(inf_float));
    init(num_3);
    LoadFromString(num_3, "3");
    inf_float *a0 = divide(num_1, num_3, precise);
    inf_float *r0_0 = sqr_root(num_3, precise, step);
    inf_float *r0_1 = substract(r0_0, num_1);
    inf_float *r0 = divide(r0_1, num_2, precise);
    inf_float *s0_0 = pow3(r0);
    inf_float *s0_1 = substract(num_1, s0_0);
    inf_float *s0 = cubic_root(s0_1, precise, step);

    inf_float *t_n, *u_n, *v_n, *w_n, *a_n, *s_n, *r_n;
    r_n = inf_float_copy(r0);
    a_n = inf_float_copy(a0);
    s_n = inf_float_copy(s0);
    print_float(a_n);
    print_float(r_n);
    print_float(s_n);
    int k = 3;
    while (iteration--)
    {
        inf_float *t_n_0 = multiply_single(r_n, 2);
        t_n = add_single(t_n_0, 1);
        inf_float *u_n_0 = pow2(r_n);
        inf_float *u_n_1 = add_single(u_n_0, 1);
        inf_float *u_n_2 = add(u_n_1, r_n);
        inf_float *u_n_3 = multiply(u_n_2, r_n);
        inf_float *u_n_4 = multiply_single(u_n_3, 9);
        u_n = cubic_root(u_n_4, precise, step);
        destroy(u_n_0);
        destroy(u_n_1);
        destroy(u_n_2);
        destroy(u_n_3);
        destroy(u_n_4);

        inf_float *v_n_0 = pow2(t_n);
        inf_float *v_n_1 = pow2(u_n);
        inf_float *v_n_2 = multiply(t_n, u_n);
        inf_float *v_n_3 = add(v_n_0, v_n_1);
        v_n = add(v_n_3, v_n_2);
        destroy(v_n_0);
        destroy(v_n_1);
        destroy(v_n_2);
        destroy(v_n_3);

        inf_float *w_n_0 = pow2(s_n);
        inf_float *w_n_1 = add(w_n_0, s_n);
        inf_float *w_n_2 = add_single(w_n_1, 1);
        inf_float *w_n_3 = multiply_single(w_n_2, 27);
        w_n = divide(w_n_3, v_n, precise);
        destroy(w_n_0);
        destroy(w_n_1);
        destroy(w_n_2);
        destroy(w_n_3);

        inf_float *a_n_0 = multiply(w_n, a_n);
        inf_float *a_n_1 = substract_single_1(w_n, 1);
        inf_float *a_n_2 = multiply_single(a_n_1, k);
        inf_float *a_n_3 = add(a_n_0, a_n_2);
        destroy(a_n);
        a_n = a_n_3;
        destroy(a_n_1);
        destroy(a_n_2);
        destroy(a_n_0);

        inf_float *s_n_0 = substract_single_1(r_n, 1);
        inf_float *s_n_1 = pow3(s_n_0);
        inf_float *s_n_2 = multiply_single(u_n, 2);
        inf_float *s_n_3 = add(t_n, s_n_2);
        inf_float *s_n_4 = multiply(s_n_3, v_n);
        inf_float *s_n_5 = divide(s_n_1, s_n_4, precise);
        destroy(s_n);
        s_n = s_n_5;
        destroy(s_n_0);
        destroy(s_n_1);
        destroy(s_n_2);
        destroy(s_n_3);
        destroy(s_n_4);

        inf_float *r_n_0 = pow3(s_n);
        inf_float *r_n_1 = substract_single_1(r_n_0, 1);
        inf_float *r_n_2 = cubic_root(r_n_1, precise, step);
        destroy(r_n);
        r_n = r_n_2;
        destroy(r_n_0);
        destroy(r_n_1);

        destroy(t_n);
        destroy(u_n);
        destroy(v_n);
        destroy(w_n);

        k *= 9;
        cut_tail(a_n, precise);
        cut_tail(r_n, precise);
        cut_tail(s_n, precise);
        print_float(a_n);
        print_float(r_n);
        print_float(s_n);
    }
    print_float(a_n);
    print_float(r_n);
    print_float(s_n);
    destroy(a_n);
    destroy(r_n);
    destroy(s_n);
}

inf_float *PI_2(size_t n)
{
    char *buf = (char *)malloc(n + 1);
    const char PI_C[] = "3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679821480865132823066470938446095505822317253594081284811174502841027019385211055596446229489549303819644288109756659334461284756482337867831652712019091456485669234603486104543266482133936072602491412737245870066063155881748815209209628292540917153643678925903600113305305488204665213841469519415116094330572703657595919530921861173819326117931051185480744623799627495673518857527248912279381830119491";

    inf_float *result = (inf_float *)malloc(sizeof(inf_float));
    init(result);
    LoadFromString(result, "2");
    size_t precise = n/8+10;
    size_t iteration = 2000;
    inf_float *num_16 = single(16);
    inf_float *num_4 = single(4);
    inf_float *num_5k = single(5);
    inf_float *num_25 = single(-25);
    inf_float *num_239k = single(239);
    inf_float *num_239_239 = single(-239 * 239);
    inf_float *num_1 = single(1);

    inf_float *div_5k = divide_int(num_16, 5, precise);
    inf_float *div_239k = divide_int(num_4, 239, precise);
    inf_float *div_239_239 = divide_int(num_1, 239*239, precise);
    inf_float *div_25 = divide_int(num_1, 25, precise);

    //print_float(div_25);
    //print_float(div_239_239);

    size_t i = 0;
    while (i++ < iteration)
    {
        inf_float *t3 = substract(div_5k, div_239k);
        inf_float *t4 = divide_int(t3, 2 * i - 1, precise);

        inf_float *t5 = add(result, t4);
        destroy(result);
        result = t5;

        destroy(t3);
        destroy(t4);
        cut_tail(result, precise);
        //printf("iteration = %d\n", i);
        quickNormalizeSelf(result);
        inf_float *v1 = divide_int(div_5k, -25, precise);
        inf_float *v2 = divide_int(div_239k, -239 * 239, precise);
        destroy(div_5k);
        quickNormalizeSelf(v1);
        destroy(div_239k);
        quickNormalizeSelf(v2);
        div_5k = v1;
        div_239k = v2;
        cut_tail(div_5k, precise);
        cut_tail(div_239k, precise);
    }
    inf_float *num_2 = single(2);
    inf_float *tmp = substract(result, num_2);
    destroy(result);
    result = tmp;
    quickNormalizeSelf(result);
    //printf("%s\n", PI_C);
    //print_float(result);
    destroy(num_16);
    destroy(num_4);
    destroy(num_5k);
    destroy(num_25);
    destroy(num_239k);
    destroy(num_239_239);
    destroy(num_1);
    destroy(div_5k);
    destroy(div_239k);
    destroy(div_239_239);
    destroy(div_25);
    return result;
}

void main()
{
    //test divide_int
    inf_float *a = (inf_float *)malloc(sizeof(inf_float));
    init(a);
    char buf[8192];
    scanf("%s", buf);
    LoadFromString(a, buf);
    //int b;
    //scanf("%d", &b);
    inf_float *b = (inf_float *)malloc(sizeof(inf_float));
    init(b);
    scanf("%s", buf);
    LoadFromString(b, buf);
    
    printf("a = ");
    print_float(a);
    printf("b = ");
    print_float(b);

    inf_float *result = add(a, b);
    quickNormalizeSelf(result);
    printf("a+b = ");
    print_float(result);
    destroy(result);

    result = substract(a, b);
    quickNormalizeSelf(result);
    printf("a-b = ");
    print_float(result);
    destroy(result);

    result = multiply(a, b);
    quickNormalizeSelf(result);
    printf("a*b = ");
    print_float(result);
    destroy(result);

    printf("a/b = ");
    result = divide(a, b, 64);
    quickNormalizeSelf(result);
    print_float(result);
    destroy(result);

    printf("a^1/2 = ");
    result = sqr_root(a, 64, 30);
    quickNormalizeSelf(result);
    print_float(result);
    destroy(result);

    printf("a^1/3 = ");
    result = cubic_root(a, 64, 30);
    quickNormalizeSelf(result);
    print_float(result);
    destroy(result);


    destroy(a);
    destroy(b);
    return;
    int n;
    scanf("%d", &n);
    inf_float *pi = PI_2(n + 2);
    print_float_NoExp(pi, n + 2);
    return;
}