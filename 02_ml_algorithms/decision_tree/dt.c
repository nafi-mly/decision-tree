#include "dt.h"

// binary classification
float gini_impurity(int *labels, int n) {
    if (n == 0) return 0.0;

    int count_class_0 = 0;
    for (int i = 0; i < n; i++) if (labels[i] == 0) count_class_0++;

    float p0 = count_class_0 / n;
    float p1 = 1.0 - p0;

    return 1.0 - (p0 * p0 + p1 * p1);
}

void split_data(Matrix X, int *Y, int n, int feature, float threshold,
                Matrix *X_left, int **Y_left, int *n_left,
                Matrix *X_right, int **Y_right, int *n_right) {
    
    // count how many on left and right
    *n_left = 0; *n_right = 0;
    for (int i = 0; i < n; i++) {
        if (X.data[i * X.cols + feature] <= threshold) 
            (*n_left)++;
        else 
            (*n_right)++;
    }

    X_left->rows = *n_left;
    X_left->cols = X.cols;
    X_left->data = (float*)malloc(sizeof(float) * (*n_left) * X.cols);
    *Y_left = (int*)malloc(sizeof(int) * (*n_left));

    X_right->rows = *n_right;
    X_right->cols = X.cols;
    X_right->data = (float*)malloc(sizeof(float) * (*n_right) * X.cols);
    *Y_right = (int*)malloc(sizeof(int) * (*n_right));
        
    int l = 0, r = 0;
    for (int i = 0; i < n; i++) {
        if (X.data[i * X.cols + feature] <= threshold) {
            // Copy row to left
            for (int j = 0; j < X.cols; j++) 
                X_left->data[l * X.cols + j] = X.data[i * X.cols + j];
            (*Y_left)[l] = Y[i];
            l++;
        } else {
            // Copy row to right
            for (int j = 0; j < X.cols; j++) 
                X_right->data[r * X.cols + j] = X.data[i * X.cols + j];
            (*Y_right)[r] = Y[i];
            r++;
        }
    }   
}

Node* build_tree(Matrix X, int *Y, int n, int depth, int max_depth) {
    // base case
    int all_same = 1;
    for (int i = 0; i < n; i++) if (Y[i] != Y[0]) all_same = 0;

    Node *node = (Node*)malloc(sizeof(Node));

    if (all_same || depth >= max_depth || n == 0) {
        node->is_leaf = 1;
        node->prediction = Y[0];
        return node;
    }

    float parent_gini = gini_impurity(Y, n);
    float best_gain = -1.0;
    int best_feature = -1;
    float best_threshold = 0.0;

    for (int f = 0; f < X.cols; f++) {
        for (int i = 0; i < n; i++) {
            float threshold = X.data[i * X.cols + f];
        
            Matrix Xl, Xr; int *Yl, *Yr; int nl, nr;
            split_data(X, Y, n, f, threshold, &Xl, &Yl, &nl, &Xr, &Yr, &nr);
            
            float w_gini = ((float)nl / n) * gini_impurity(Yl, nl) + 
                           ((float)nr / n) * gini_impurity(Yr, nr);
            float gain = parent_gini - w_gini;

            if (gain > best_gain) {
                best_gain = gain;
                best_feature = f;
                best_threshold = threshold;
            }
        }
    }

    node->is_leaf = 0;
    node->feature_index = best_feature;
    node->threshold = best_threshold;

    Matrix Xl, Xr; int *Yl, *Yr; int nl, nr;
    split_data(X, Y, n, best_feature, best_threshold, &Xl, &Yl, &nl, &Xr, &Yr, &nr);

    node->left = build_tree(Xl, Yl, nl, depth + 1, max_depth);
    node->right = build_tree(Xr, Yr, nr, depth + 1, max_depth);

    return node;
}

int predict(Node *root, float *sample, int num_features) {
    Node *curr = root;
    while (!curr->is_leaf) {
        if (sample[curr->feature_index] <= curr->threshold) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }
    return curr->prediction;
}