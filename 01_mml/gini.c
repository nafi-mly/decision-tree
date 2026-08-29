#include <stdio.h>

int main() {
    int dog   = 4;
    int cat   = 6;
    int total = dog + cat;

    float p_dog = (float)dog / total;
    float p_cat = (float)cat / total;

    float gini  = 1.0 - (p_dog*p_dog + p_cat*p_cat);

    printf("P(Dog) = %.2f\n", p_dog);
    printf("P(Cat) = %.2f\n", p_cat);
    printf("Gini Impurity = %.2f\n", gini);

    return 0;
}