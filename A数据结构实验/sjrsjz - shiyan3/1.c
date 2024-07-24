#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct tree{
    int data;
    struct tree *left;
    struct tree *right;
    int located; //0: located, 1: left, -1: right
} tree;

tree *locate_curr_tree(tree* curr){
    if(curr == NULL){
        return NULL;
    }
    if(curr->located == 0){
        return curr;
    }
    else if(curr->located == 1){
        return locate_curr_tree(curr->left);
    }
    else{
        return locate_curr_tree(curr->right);
    }
}

int locate_to_left(tree* curr){
    if(curr == NULL){
        return 0;
    }
    tree* temp = locate_curr_tree(curr);
    if(temp == NULL || temp->left == NULL){
        return 0;
    }
    temp->located = 1;
} 

int locate_to_right(tree* curr){
    if(curr == NULL){
        return 0;
    }
    tree* temp = locate_curr_tree(curr);
    if(temp == NULL || temp->right == NULL){
        return 0;
    }
    temp->located = -1;
}

int __locate_to_parent(tree* curr, tree* parent){
    if (curr == NULL)
    {
        return 0;
    }
    if (curr->located == 0)
    {
        if(parent == NULL){
            return 0;
        }
        parent->located = 0;
        return 1;
    }
    else if (curr->located == 1)
    {
        return __locate_to_parent(curr->left, curr);
    }
    else
    {
        return __locate_to_parent(curr->right, curr);
    }
}

int locate_to_parent(tree* curr){
    return __locate_to_parent(curr, NULL);
}

int append_to_left(tree* curr, int data){
    if(curr == NULL){
        return 0;
    }
    tree* temp = locate_curr_tree(curr);
    if(temp == NULL){
        return 0;
    }
    tree* new_node = (tree*)malloc(sizeof(tree));
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->located = 0;
    temp->left = new_node;
    return 1;
}

int append_to_right(tree* curr, int data){
    if(curr == NULL){
        return 0;
    }
    tree* temp = locate_curr_tree(curr);
    if(temp == NULL){
        return 0;
    }
    tree* new_node = (tree*)malloc(sizeof(tree));
    new_node->data = data;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->located = 0;
    temp->right = new_node;
    return 1;
}

int destroy_tree(tree* curr){
    if(curr == NULL){
        return 0;
    }
    int p = 0;
    p |= destroy_tree(curr->left);
    p |= destroy_tree(curr->right);
    free(curr);
    return p;
}
int locate_to_root(tree* curr){
    while (locate_to_parent(curr));
}

tree* combine_tree(tree* tree1, tree* tree2){
    if(tree1 == NULL || tree2 == NULL){
        return 0;
    }
    tree* new_node = (tree*)malloc(sizeof(tree));
    new_node->data = 0;
    new_node->left = tree1;
    new_node->right = tree2;
    new_node->located = 0;
    return new_node;
}


int find_2_min_weight_idx(double weights[], unsigned int size, unsigned int* idx1, unsigned int* idx2){
    if(weights == NULL || size == 0){
        return 0;
    }
    if(size == 1){
        *idx1 = 0;
        *idx2 = 0;
        return 1;
    }
    double min1 = 0;
    double min2 = 0;
    unsigned int idx1_ = 0;
    unsigned int idx2_ = 0;

    for(unsigned int i = 0; i < size; i++){
        if(weights[i] == 0){
            continue;
        }
        if(min1 == 0){
            min1 = weights[i];
            idx1_ = i + 1;
        }
        else if(min2 == 0){
            min2 = weights[i];
            idx2_ = i + 1;
        }
        else if(weights[i] < min1){
            min2 = min1;
            idx2_ = idx1_;
            min1 = weights[i];
            idx1_ = i + 1;
        }
        else if(weights[i] < min2){
            min2 = weights[i];
            idx2_ = i + 1;
        }
        if (min1 > min2)
        {
            double temp = min1;
            min1 = min2;
            min2 = temp;
            unsigned int temp_idx = idx1_;
            idx1_ = idx2_;
            idx2_ = temp_idx;
        }
    }

    *idx1 = idx1_;
    *idx2 = idx2_;
    return idx1_!=0 && idx2_!=0;
}


tree* generate_huffman_tree(int data[],double weights[],unsigned int size){
    //生成哈夫曼树
    double *tree_weights = (double *)malloc(sizeof(double) * size);
    for (unsigned int i = 0; i < size; i++)
    {
        tree_weights[i] = weights[i];
    }
    tree** trees = (tree**)malloc(sizeof(tree*)*size);
    for (unsigned int i = 0; i < size; i++)
    {
        trees[i] = (tree*)malloc(sizeof(tree));
        trees[i]->data = data[i];
        trees[i]->left = NULL;
        trees[i]->right = NULL;
        trees[i]->located = 0;
    }
    unsigned int idx1 = 0;
    unsigned int idx2 = 0;
    while(find_2_min_weight_idx(tree_weights, size, &idx1, &idx2)){
        idx1--;
        idx2--;
        tree_weights[idx1] += tree_weights[idx2];
        tree_weights[idx2] = 0;
        trees[idx1] = combine_tree(trees[idx1], trees[idx2]);
        trees[idx2] = NULL;
    }
    for(unsigned int i = 0; i < size; i++){
        if(trees[i] != NULL){
            return trees[i];
        }
    }
}

int __generate_huffman_code(tree *root, char **code, int treeDirection, int depth, char* buffer)
{
    if (root == NULL)
    {
        return treeDirection == 0 ? 0 : 1;
    }

    if (depth > 0)
    {
        buffer[depth - 1] = treeDirection == 1 ? '1' : '0';
        buffer[depth] = '\0';
    }

    if (root->left == NULL && root->right == NULL)
    {
        strcpy(code[root->data], buffer);
        return 1;
    }
    int p = 0;
    p |= __generate_huffman_code(root->left, code, -1, depth + 1, buffer);
    p |= __generate_huffman_code(root->right, code, 1, depth + 1, buffer);
    return p;
}

char** generate_huffman_code(tree *root, unsigned int max_size, unsigned int max_code_len)
{
    if (root == NULL)
    {
        return NULL;
    }
    char **code = (char **)malloc(sizeof(char *) * max_size);
    char *buffer = (char *)malloc(sizeof(char) * max_code_len);
    buffer[0] = '\0';
    for (unsigned int i = 0; i < max_size; i++)
    {
        code[i] = (char *)malloc(sizeof(char) * max_code_len);
        code[i][0] = '\0';
    }
    int p = __generate_huffman_code(root, code, 0, 0, buffer);
    free(buffer);
    if (p == 0)
    {
        for (unsigned int i = 0; i < max_size; i++)
        {
            free(code[i]);
        }
        free(code);
        return NULL;
    }
    return code;
}

tree* construct_huffman_tree_from_codes(char** code, unsigned int max_size){
    tree* root = (tree*)malloc(sizeof(tree));
    root->data = 0;
    root->left = NULL;
    root->right = NULL;
    root->located = 0;
    for(unsigned int i = 0; i < max_size; i++){
        if(code[i] == NULL){
            continue;
        }
        tree* curr = root;
        for(unsigned int j = 0; j < strlen(code[i]); j++){
            if(code[i][j] == '0'){
                if(curr->left == NULL){
                    curr->left = (tree*)malloc(sizeof(tree));
                    curr->left->data = 0;
                    curr->left->left = NULL;
                    curr->left->right = NULL;
                    curr->left->located = 0;
                }
                curr = curr->left;
            }
            else{
                if(curr->right == NULL){
                    curr->right = (tree*)malloc(sizeof(tree));
                    curr->right->data = 0;
                    curr->right->left = NULL;
                    curr->right->right = NULL;
                    curr->right->located = 0;
                }
                curr = curr->right;
            }
        }
        curr->data = i;
    }
    return root;
}

char* huffman_encode(char* str, unsigned int str_len, char** code, unsigned int max_code_len){
    char *buffer = (char *)malloc(sizeof(char) * max_code_len * str_len);
    buffer[0] = '\0';
    for(unsigned int i = 0; i < str_len; i++){
        strcat(buffer, code[str[i]]);
    }
    return buffer;
}

char *huffman_decode(char *str, unsigned int str_len, tree *root)
{
    char *buffer = (char *)malloc(sizeof(char) * (str_len + 1));
    buffer[0] = '\0';
    char *ip = &buffer[0];
    tree *curr = root;
    for (unsigned int i = 0; i < str_len; i++)
    {
        if (str[i] == '0')
        {
            curr = curr->left;
        }
        else
        {
            curr = curr->right;
        }
        if (curr->left == NULL && curr->right == NULL)
        {
            *(ip++) = curr->data;
            *(ip) = '\0';
            curr = root;
        }
    }
    return buffer;
}

int main(){
    int N;
    scanf("%d", &N);
    int* data = (int*)malloc(sizeof(int)*N);
    double* weights = (double*)malloc(sizeof(double)*N);
    for(int i = 0; i < N; i++){
        char c;
        scanf(" %c", &c);
        data[i] = c;
    }
    for(int i = 0; i < N; i++){
        scanf("%lf", &weights[i]);
    }
    tree* root = generate_huffman_tree(data, weights, N);
    char** code = generate_huffman_code(root, 256, 256);
    unsigned int max_str_len = 1024;
    char *str = (char *)malloc(sizeof(char) * (max_str_len + 1));

    unsigned int str_len = 0;
    /*char input;
    //先清空缓冲区
    while ((input = getchar()) != '\n' && input != EOF);
    while (1)
    {
        scanf("%c", &input);
        if(input == '\n'){
            break;
        }
        if (str_len >= max_str_len)
        {
            max_str_len += 1024;
            char *new_str = (char *)malloc(sizeof(char) * max_str_len);
            memcpy(new_str, str, sizeof(char) * (max_str_len + 1));
            free(str);
            str = new_str;
        }
        str[str_len] = input;
        str_len++;
    }
    str[str_len] = '\0';
    */
    scanf("%s", str);
    str_len = strlen(str);
    char *encoded = huffman_encode(str, str_len, code, 1024);    

    printf("%s\n", encoded);

    char *decoded = huffman_decode(encoded, strlen(encoded), root);
    printf("%s\n", decoded);

    free(str);
    free(encoded);
    free(decoded);
    for(int i = 0; i < 256; i++){
        free(code[i]);
    }
    free(code);
    destroy_tree(root);
    free(data);
    free(weights);
    return 0;
}