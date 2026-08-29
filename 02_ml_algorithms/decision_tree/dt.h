#ifndef DT_H
#define DT_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct {
    float *data;
    int rows;
    int cols;
} Matrix;

typedef struct Node {
    int is_leaf;
    int prediction;
    int feature_index;
    float threshold;
    struct Node *left;
    struct Node *right;
} Node;

float gini_impurity(int *labels, int n);
Node* build_tree(Matrix X, int *Y, int n, int depth, int max_depth);
int predict(Node *root, float *sample, int num_features);

#endif