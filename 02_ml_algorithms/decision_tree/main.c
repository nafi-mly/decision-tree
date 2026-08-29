#include "dt.h"

int main() {
    // Features: [Weight (kg), Has_Fur (0/1)]
    // Labels: [Dog (1), Cat (0)]
    // Row-major layout (cache optimization)
    float data[] = {
        10.0, 1.0,  // Dog
        5.0,  1.0,  // Dog
        3.0,  0.0,  // Cat
        4.0,  0.0,  // Cat
        12.0, 1.0,  // Dog
        2.0,  0.0   // Cat
    };
    int labels[] = {1, 1, 0, 0, 1, 0};
    
    Matrix X = { data, 6, 2 }; 

    Node *root = build_tree(X, labels, 6, 0, 3);

    float new_sample[] = {8.0, 1.0}; 
    int prediction = predict(root, new_sample, 2);
    
    printf("Prediction for (8kg, furry): %s\n", prediction == 1 ? "Dog" : "Cat");

    float new_sample2[] = {1.5, 0.0}; 
    prediction = predict(root, new_sample2, 2);
    printf("Prediction for (1.5kg, hairless): %s\n", prediction == 1 ? "Dog" : "Cat");

    // (We are skipping free() for brevity in this academic example)
    return 0;
}